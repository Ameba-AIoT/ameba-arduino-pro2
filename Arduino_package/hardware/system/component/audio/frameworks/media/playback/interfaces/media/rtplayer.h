/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Media
 * @{
 *
 * @brief Declares APIs for media framework.
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file rtplayer.h
 *
 * @brief Provides the APIs to implement operations related to manage playback.
 * These player interfaces can be used to control playback of audio files and streams(via https or rtsp),
 * register observer functions, and control the feature status.
 * Playback control includs start, stop, pause, resume, rewind and so on.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_MEDIA_RTPLAYER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_MEDIA_RTPLAYER_H

#include "osal_c/osal_types.h"

__BEGIN_DECLS

/**
 * @brief Defines all the player status.
 *
 * @since 1.0
 * @version 1.0
 */
enum RTPlayerStates {
	/** Used to indicate an idle state */
	RTPLAYER_IDLE = 0,
	/** Used to indicate player is preparing */
	RTPLAYER_PREPARING = 1,
	/** Used to indicate player prepared */
	RTPLAYER_PREPARED = 2,
	/** Used to indicate player started */
	RTPLAYER_STARTED = 3,
	/** Used to indicate player paused */
	RTPLAYER_PAUSED = 4,
	/** Used to indicate player stopped */
	RTPLAYER_STOPPED = 5,
	/** Used to indicate player completed */
	RTPLAYER_PLAYBACK_COMPLETE = 6,
	/** Used to indicate rewind player completed */
	RTPLAYER_REWIND_COMPLETE = 7,
	/** Used to indicate player error */
	RTPLAYER_ERROR = 8,
};

/**
 * @brief Defines the player errors.
 *
 * @since 1.0
 * @version 1.0
 */
enum RTPlayerErrors {
	/** Used to indicate a player error */
	RTPLAYER_ERROR_UNKNOWN = 0,
};

/**
 * @brief Defines the extra informations of a player.
 *
 * @since 1.0
 * @version 1.0
 */
enum RTPlayerInfos {
	/** Player is temporarily pausing playback internally in order to buffer more data. */
	RTPLAYER_INFO_BUFFERING_START = 0,
	/** Player is resuming playback after filling buffers. */
	RTPLAYER_INFO_BUFFERING_END = 1,
	/** Player buffered data percentage update. */
	RTPLAYER_INFO_BUFFERING_INFO_UPDATE = 2,
	/** The media is not rewindable (e.g live stream). */
	RTPLAYER_INFO_NOT_REWINDABLE = 3,
};

typedef struct RTPlayer RTPlayer;
typedef struct RTPlayerCallback RTPlayerCallback;

/**
 * @brief Provides calback interfaces.
 */
struct RTPlayerCallback {
	/**
	 * @brief Called when player status is changed.
	 *
	 * @param listener The RTPlayerCallback object pointer.
	 * @param player The RTPlayer object pointer.
	 * @param state The player status, one of {@link RTPlayerStates}.
	 * @since 1.0
	 * @version 1.0
	 */
	void (*OnRTPlayerStateChanged)(const struct RTPlayerCallback *listener, const struct RTPlayer *player, int state);

	/**
	 * @brief Called when player information is received.
	 *
	 * @param listener The RTPlayerCallback object pointer.
	 * @param player The RTPlayer object pointer.
	 * @param info Indicates the information type. For details, see {@link RTPlayerInfos}.
	 * @param extra Indicates the information code.
	 * @since 1.0
	 * @version 1.0
	 */
	void (*OnRTPlayerInfo)(const struct RTPlayerCallback *listener, const struct RTPlayer *player, int info, int extra);

	/**
	 * @brief Called when a player error occurs.
	 *
	 * @param listener The RTPlayerCallback object pointer.
	 * @param player The RTPlayer object pointer.
	 * @param error Indicates the error type. For details, see {@link RTPlayerErrors}.
	 * @param extra Indicates the error code.
	 * @since 1.0
	 * @version 1.0
	 */
	void (*OnRTPlayerError)(const struct RTPlayerCallback *listener, const struct RTPlayer *player, int error, int extra);
};

/**
 * @brief Creates RTPlayer.
 *
 * @return a new RTPlayer object pointer.
 * @since 1.0
 * @version 1.0
 */
struct RTPlayer *RTPlayer_Create(void);

/**
 * @brief Destory RTPlayer.
 *
 * @param player The RTPlayer object pointer.
 * @since 1.0
 * @version 1.0
 */
void	RTPlayer_Destory(struct RTPlayer *player);

/**
 * @brief Sets the source(url) to use.
 *
 * @param player The RTPlayer object pointer.
 * @param url The url of the file you want to play.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_SetSource(struct RTPlayer *player, const char *url);

/**
 * @brief Prepares the player for playback, synchronously.
 *
 * @param player The RTPlayer object pointer.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_Prepare(struct RTPlayer *player);

/**
 * @brief Prepares the player for playback, asynchronously.
 * A call to {@link RTPlayer_PrepareAsync()} (asynchronous) will first transfers
 * the playbackt to the RTPLAYER_PREPARING state after the call returns
 * (which occurs almost right away) while the internal player engine continues
 * working on the rest of preparation work until the preparation work completes.
 * When the preparation completes, the internal player engine then calls a user
 * supplied callback method OnRTPlayerStateChanged(..., RTPLAYER_PREPARED)
 * of the RTPlayerCallbacks interface, if an RTPlayerCallbacks object is registered
 * beforehand via {@link RTPlayer_SetCallbacks()}.
 *
 * @param player The RTPlayer object pointer.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_PrepareAsync(struct RTPlayer *player);

/**
* @brief Starts or resumes playback. If playback had previously been paused,
* playback will continue from where it was paused. If playback had
* been stopped, or never started before, playback will start at the
* beginning.
*
* @param player The RTPlayer object pointer.
* @return Returns a value listed below: \n
* rt_status_t | Description
* ----------------------| -----------------------
* OSAL_OK | the operation is successful.
* OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
* OSAL_ERR_UNKNOWN_ERROR | operation is failed.
* @since 1.0
* @version 1.0
*/
rt_status_t RTPlayer_Start(struct RTPlayer *player);

/**
 * @brief Stops playback after playback has been started or paused.
 *
 * @param player The RTPlayer object pointer.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_Stop(struct RTPlayer *player);

/**
 * @brief Pauses playback. Call RTPlayer_Start() to resume.
 *
 * @param player The RTPlayer object pointer.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_Pause(struct RTPlayer *player);

/**
 * @brief Moves the media to specified time position.
 *
 * @param player The RTPlayer object pointer.
 * @param msec The offset in milliseconds from the start to rewind to.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_Rewind(struct RTPlayer *player, int64_t msec);

/**
 * @brief Resets the Player to its uninitialized state. After calling
 * this method, you will have to initialize it again by setting the
 * source and calling RTPlayer_Prepare() or RTPlayer_PrepareAsync().
 *
 * @param player The RTPlayer object pointer.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_Reset(struct RTPlayer *player);

/**
 * @brief Gets the current playback position.
 *
 * @param player The RTPlayer object pointer.
 * @param msec The current time updated during this function.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_GetCurrentTime(struct RTPlayer *player, int64_t *msec);

/**
 * @brief Gets the duration of the file.
 *
 * @param player The RTPlayer object pointer.
 * @param msec The duration in milliseconds, if no duration is available
 *         (for example, if streaming live content), -1 is updated.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_GetDuration(struct RTPlayer *player, int64_t *msec);

/**
 * @brief Checks whether the player is playing.
 *
 * @param player The RTPlayer object pointer.
 * @return 1 if currently playing, 0 otherwise.
 * @since 1.0
 * @version 1.0
 */
int RTPlayer_IsPlaying(struct RTPlayer *player);

/**
 * @brief Sets player callbacks.
 *
 * @param player The RTPlayer object pointer.
 * @param callbacks The {@link RTPlayerCallbacks} instance used to receive player messages.
 * @since 1.0
 * @version 1.0
 */
void RTPlayer_SetCallback(struct RTPlayer *player, struct RTPlayerCallback *callbacks);

/**
 * @brief Sets player volume when play started.
 *
 * @param player The RTPlayer object pointer.
 * @param left The volume of left channel.
 * @param right The volume of right channel.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_SetVolume(struct RTPlayer *player, float left, float right);

/**
 * @brief Sets player speed when play started.
 *
 * @param player The RTPlayer object pointer.
 * @param speed The speed of player.
 * @param speed The pitch of player.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | playback is not in idle state.
 * OSAL_ERR_UNKNOWN_ERROR | operation is failed.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTPlayer_SetSpeed(struct RTPlayer *player, float speed, float pitch);

__END_DECLS

#endif // AMEBA_FWK_MEDIA_PLAYBACK_MEDIA_RTPLAYER_H
/** @} */
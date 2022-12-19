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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_H

#include <vector>
#include <stdint.h>

#include "media/utils/rstate_machine.h"
#include "media/common/media_defs.h"

#include "media/codec/codec_base.h"
#include "media/codec/omx/omx.h"
#include "media/codec/omx/omx_node.h"

#include <OMX_Audio.h>

namespace ameba::media
{

class CodecBufferTunnel;
class CodecBufferInfo;
class DataConverter;

class Codec : public RStateMachine, public CodecBase
{
public:
	Codec();

	virtual std::shared_ptr<BufferTunnelBase> GetBufferTunnel() override;

	virtual void AllocateComponent(const sptr<Message> &msg);
	virtual void ConfigureComponent(const sptr<Message> &msg);
	virtual void Start();
	virtual void StartShutdown(bool reserve_component = false);

	virtual void Flush();
	virtual void Resume();

	// AHierarchicalStateMachine implements the message handling
	virtual void OnMessage(const sptr<Message> &msg)
	{
		HandleMessage(msg);
	}

protected:
	virtual ~Codec();

private:
	class BaseState;
	class UninitializedState;
	class LoadedState;
	class LoadedToIdleState;
	class IdleToExecutingState;
	class ExecutingState;
	class OutputPortSettingsChangedState;
	class ExecutingToIdleState;
	class IdleToLoadedState;
	class FlushingState;

	enum {
		kMsgCreateOMXNode       = 0x320100,//'allo',
		kMsgConfigureNode    = 0x320101,//'conf',
		kMsgSetParameters    = 0x320102,//'setP',

		kMsgStart                   = 0x320201,//'star',
		kMsgShutdown           = 0x320202,//'shut',
		kMsgReleaseCodec     = 0x320203,//'relC',
		kMsgFlush                  = 0x320204,//'flus',
		kMsgResume              = 0x320206,//'resm',

		kMsgInputBufferFilled       = 0x320300,//'inpF',
		kMsgOutputBufferExhausted     = 0x320310,//'outD',

		kMsgOMXMessage              = 0x320400,//'omx ',
		// same as kMsgOMXMessage - but only used with
		// handleMessage during OMX message-list handling
		kMsgOMXEvent          = 0x320401,//'omxI',
		kMsgOMXEventList          = 0x320402,//'omxL',

		kMsgStartStateTransition    = 0x320600,//'fstt',
	};

	enum {
		kPortInput  = 0,
		kPortOutput = 1
	};

	class BufferInfo
	{
	public:
		enum Status {
			STATUS_POSSESSED_BY_US,
			STATUS_POSSESSED_BY_COMPONENT,
			STATUS_POSSESSED_BY_UPSTREAM,
			STATUS_POSSESSED_BY_DOWNSTREAM,
			STATUS_UNRECOGNIZED,            // not a tracked buffer
		};

		static inline Status GetStatus(BufferInfo *info)
		{
			return info == NULL ? STATUS_UNRECOGNIZED : info->status_;
		}

		OMX::buffer_id buffer_id_;
		Status status_;
		unsigned dequeued_at_;

		sptr<CodecBufferInfo> data_;  // the client's buffer; if not using data conversion, this is
		// the codec buffer; otherwise, it is allocated separately
		sptr<CodecBufferInfo> codec_data_;  // the codec's buffer
	};

	sptr<UninitializedState> uninitialized_state_;
	sptr<LoadedState> loaded_state_;
	sptr<LoadedToIdleState> loaded_to_idle_state_;
	sptr<IdleToExecutingState> idle_to_executing_state_;
	sptr<ExecutingState> executing_state_;
	sptr<OutputPortSettingsChangedState> output_port_settings_changed_state_;
	sptr<ExecutingToIdleState> executing_to_idle_state_;
	sptr<IdleToLoadedState> idle_to_loaded_state_;
	sptr<FlushingState> flushing_state_;

	RString component_name_;
	uint32_t flags_;
	sptr<OMX> omx_;
	sptr<OMXNode> omx_node_;
	int32_t node_count_;

	sptr<Message> config_format_;
	sptr<Message> input_format_;
	sptr<Message> output_format_;

	// Initial output format + configuration params that is reused as the base for all subsequent
	// format updates. This will equal to output_format_ until the first actual frame is received.
	sptr<Message> base_output_format_;
	sptr<Message> final_output_format_;

	bool channel_mask_present_;
	int32_t channel_mask_;
	int32_t sample_rate_;
	unsigned dequeue_counter_;

	List<sptr<Message> > pending_messages_;

	std::vector<BufferInfo> buffers_[2];
	bool port_eos_[2];
	res_t input_eos_result_;

	bool fatal_error_;
	bool shutdowning_;
	bool explicit_shutdown_;
	// If "reserve_component_" we only transition back to Loaded state
	// and do not release the component instance.
	bool reserve_component_;

	// 0 for input encoder, 1 for output decode
	sptr<DataConverter> converter_[2];

	int32_t state_count_;

	std::shared_ptr<CodecBufferTunnel> buffer_tunnel_;

	res_t AllocateBuffers(OMX_U32 port_idx);
	res_t FreeBuffers(OMX_U32 port_idx);
	res_t FreeOutputBuffersNotPossessedByComponent();
	res_t FreeBuffer(OMX_U32 port_idx, size_t i);

	static const char *GetStatusStr(BufferInfo::Status s);
	void DumpBuffers(OMX_U32 port_idx);

	BufferInfo *FindBufferByID(
		uint32_t port_idx, OMX::buffer_id id,
		ssize_t *index = NULL);

	res_t FillThisBuffer(BufferInfo *info);

	res_t SetComponent(const char *mime);
	res_t ConfigureCodec(const char *mime, const sptr<Message> &msg);

	res_t SetParameters(const sptr<Message> &params);

	// Returns true if all buffers on the given port have status
	// STATUS_POSSESSED_BY_US
	bool AllBuffersArePossessedByUs(OMX_U32 port_idx);
	bool AllBuffersArePossessedByUs();
	size_t GetNumBuffersPossessedByComponent(OMX_U32 port_idx) const;

	void PendingMessage(const sptr<Message> &msg);
	void ProcessPendingMessages();

	void NotifyError(
		OMX_ERRORTYPE error = OMX_ErrorUndefined,
		res_t internal_error = UNKNOWN_ERROR);

	res_t SetupAACCodec(
		int32_t num_channels, int32_t sample_rate, int32_t bit_rate,
		int32_t aac_profile, bool is_adts, int32_t sbr_mode,
		int32_t max_output_channel_count,
		int32_t pcm_limiter_enable);

	res_t SetupRawAudioEncoding(
		OMX_U32 port_idx, int32_t sample_rate, int32_t num_channels,
		AudioEncoding encoding = kAudioEncodingPcm16bit);

	static res_t GetOMXAudioChannelType(size_t num_channels, OMX_AUDIO_CHANNELTYPE map[]);

	// Pass |expectedFormat| to print a warning if the format differs from it.
	// Using sptr<> instead of const sptr<>& because expectedFormat is likely the current output_format_
	// which will get updated inside.
	void OnOutputFormatChanged(sptr<const Message> expectedFormat = NULL);

	res_t GetPortFormat(OMX_U32 port_idx, sptr<Message> &notify);

	res_t SetMinBufferSize(OMX_U32 port_idx, size_t size);

	// Force EXEC->IDLE->LOADED shutdown sequence if not stale.
	void EnterStateShutdownTransition(int count);

	DISALLOW_COPY_AND_MOVE(Codec);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_H
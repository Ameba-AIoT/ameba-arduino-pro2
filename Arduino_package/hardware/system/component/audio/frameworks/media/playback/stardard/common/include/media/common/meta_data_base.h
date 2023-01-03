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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_META_DATA_BASE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_META_DATA_BASE_H

#include <sys/types.h>
#include <stdint.h>
#include <string>

namespace ameba::media
{

// The following keys map to int32_t data unless indicated otherwise.
enum {
	kKeyMIMEType          = 'mime',  // cstring
	kKeyRotation          = 'rotA',  // int32_t (angle in degrees)
	kKeyChannelCount      = '#chn',  // int32_t
	kKeyChannelMask       = 'chnm',  // int32_t
	kKeySampleRate        = 'srte',  // int32_t (audio sampling rate Hz)
	kKeyPcmEncoding       = 'PCMe',  // int32_t (audio encoding enum)
	kKeyFrameRate         = 'frmR',  // int32_t (video frame rate fps)
	kKeyBitRate           = 'brte',  // int32_t (bps)
	kKeyMaxBitRate        = 'mxBr',  // int32_t (bps)
	kKeyBitsPerSample     = 'bits',  // int32_t (bits per sample)
	kKeyESDS              = 'esds',  // raw data
	kKeyAACProfile        = 'aacp',  // int32_t
	kKeyAVCC              = 'avcc',  // raw data
	kKeyHVCC              = 'hvcc',  // raw data
	kKeyVorbisInfo        = 'vinf',  // raw data
	kKeyVorbisBooks       = 'vboo',  // raw data
	kKeyOpusHeader        = 'ohdr',  // raw data
	kKeyOpusCodecDelay    = 'ocod',  // uint64_t (codec delay in ns)
	kKeyOpusRewindPreRoll   = 'ospr',  // uint64_t (rewind preroll in ns)
	kKeyFlacMetadata      = 'flMd',  // raw data
	kKeyIsSyncFrame       = 'sync',  // int32_t (bool)
	kKeyTime              = 'time',  // int64_t (usecs)
	kKeyTargetTime        = 'tarT',  // int64_t (usecs)
	kKeyDuration          = 'dura',  // int64_t (usecs)

	kKeyMaxInputSize      = 'inpS',
	kKeyMaxWidth          = 'maxW',
	kKeyMaxHeight         = 'maxH',
	kKeyTrackID           = 'trID',
	kKeyEncoderDelay      = 'encd',  // int32_t (frames)
	kKeyEncoderPadding    = 'encp',  // int32_t (frames)

	kKeyDate              = 'date',  // cstring
	kKeyWriter            = 'writ',  // cstring
	// Ogg files can be tagged to be automatically looping...
	kKeyAutoLoop          = 'autL',  // bool (int32_t)

	kKeyAlbum             = 'albu',  // cstring
	kKeyArtist            = 'arti',  // cstring
	kKeyAlbumArtist       = 'aart',  // cstring
	kKeyComposer          = 'comp',  // cstring
	kKeyGenre             = 'genr',  // cstring
	kKeyTitle             = 'titl',  // cstring
	kKeyYear              = 'year',  // cstring
	kKeyAlbumArt          = 'albA',  // compressed image data
	kKeyAlbumArtMIME      = 'alAM',  // cstring
	kKeyAuthor            = 'auth',  // cstring
	kKeyCDTrackNumber     = 'cdtr',  // cstring
	kKeyDiscNumber        = 'dnum',  // cstring
	kKeyCompilation       = 'cpil',  // cstring

	kKeyValidSamples      = 'valD',  // int32_t

	// The language code for this media
	kKeyMediaLanguage     = 'lang',  // cstring

	kKeyIsADTS            = 'adts',  // bool (int32_t)
	kKeyAACAOT            = 'aaot',  // int32_t

	// If a MediaBuffer's data represents (at least partially) encrypted
	// data, the following fields aid in decryption.
	// The data can be thought of as pairs of plain and encrypted data
	// fragments, i.e. plain and encrypted data alternate.
	// The first fragment is by convention plain data (if that's not the
	// case, simply specify plain fragment size of 0).
	// kKeyEncryptedSizes and kKeyPlainSizes each map to an array of
	// size_t values. The sum total of all size_t values of both arrays
	// must equal the amount of data (i.e. MediaBuffer's RangeLength()).
	// If both arrays are present, they must be of the same size.
	// If only encrypted sizes are present it is assumed that all
	// plain sizes are 0, i.e. all fragments are encrypted.
	// To programmatically set these array, use the MetaDataBase::setData API, i.e.
	// const size_t encSizes[];
	// meta->SetData(
	//  kKeyEncryptedSizes, 0 /* type */, encSizes, sizeof(encSizes));
	// A plain sizes array by itself makes no sense.
	kKeyEncryptedSizes    = 'encr',  // size_t[]
	kKeyPlainSizes        = 'plai',  // size_t[]

	// H264 supplemental enhancement information offsets/sizes
	kKeySEI               = 'sei ', // raw data

	// MPEG user data offsets
	kKeyMpegUserData      = 'mpud', // size_t[]
};

enum {
	kTypeESDS        = 'esds',
	kTypeAVCC        = 'avcc',
	kTypeHVCC        = 'hvcc',
	kTypeD263        = 'd263',
};

class MetaDataBase
{
public:
	MetaDataBase();
	MetaDataBase(const MetaDataBase &from);
	MetaDataBase &operator = (const MetaDataBase &);

	virtual ~MetaDataBase();

	enum Type {
		TYPE_NONE     = 'none',
		TYPE_C_STRING = 'cstr',
		TYPE_INT32    = 'in32',
		TYPE_INT64    = 'in64',
		TYPE_FLOAT    = 'floa',
		TYPE_POINTER  = 'ptr ',
	};

	void Clear();
	bool Remove(uint32_t key); //no use

	bool SetCString(uint32_t key, const char *value);
	bool SetInt32(uint32_t key, int32_t value);
	bool SetInt64(uint32_t key, int64_t value);
	bool SetFloat(uint32_t key, float value);
	bool SetPointer(uint32_t key, void *value);

	bool FindCString(uint32_t key, const char **value) const;
	bool FindInt32(uint32_t key, int32_t *value) const;
	bool FindInt64(uint32_t key, int64_t *value) const;
	bool FindFloat(uint32_t key, float *value) const;
	bool FindPointer(uint32_t key, void **value) const;

	bool SetData(uint32_t key, uint32_t type, const void *data, size_t size);

	bool FindData(uint32_t key, uint32_t *type,
				  const void **data, size_t *size) const;

	bool HasData(uint32_t key) const;

	std::string ToString() const;
	void DumpToLog() const;

private:
	friend class MetaData;

	class TypedData;
	struct MetaDataInternal;
	MetaDataInternal *meta_data_internal_;
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_META_DATA_BASE_H
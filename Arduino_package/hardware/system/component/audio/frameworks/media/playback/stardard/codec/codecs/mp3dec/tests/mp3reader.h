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

#ifndef MP3READER_H_
#define MP3READER_H_

class Mp3Reader
{
public:
	Mp3Reader();
	bool init(const char *file);
	bool getFrame(void *buffer, uint32_t *size);
	uint32_t getSampleRate()
	{
		return mSampleRate;
	}
	uint32_t getNumChannels()
	{
		return mNumChannels;
	}
	void close();
	~Mp3Reader();
private:
	FILE    *mFp;
	uint32_t mFixedHeader;
	off64_t  mCurrentPos;
	uint32_t mSampleRate;
	uint32_t mNumChannels;
	uint32_t mBitrate;
};


#endif /* MP3READER_H_ */

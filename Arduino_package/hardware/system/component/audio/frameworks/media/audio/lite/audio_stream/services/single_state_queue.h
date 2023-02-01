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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_SINGLE_STATE_QUEUE_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_SINGLE_STATE_QUEUE_H

#include <stdint.h>
//#include <atomic.h>
#include "osal_c/osal_atomic.h"

namespace ameba::audio
{

template<typename T> class SingleStateQueue
{

public:

	class Mutator;
	class Observer;

	enum SSQ_STATUS {
		SSQ_PENDING,
		SSQ_READ,
		SSQ_DONE,
	};

	struct Shared {

		friend class Mutator;
		friend class Observer;

	private:
		void                init()
		{
			ack_ = 0;
			sequence_ = 0;
		}

		volatile uint32_t    ack_;
		volatile uint32_t    sequence_;
		//volatile int32_t    ack_;
		//volatile int32_t    sequence_;
		T                   value_;
	};

	class Mutator
	{
	public:
		Mutator(Shared *shared)
			: sequence_(0), shared_(shared)
		{
		}

		int32_t push(const T &value)
		{
			Shared *shared = shared_;
			int32_t sequence = sequence_;
			sequence++;
			OsalAtomicAcquireStore(sequence, &shared->sequence_);
			//ameba_atomic_acquire_store(sequence, &shared->sequence_);
			shared->value_ = value;
			sequence++;
			OsalAtomicReleaseStore(sequence, &shared->sequence_);
			//ameba_atomic_release_store(sequence, &shared->sequence_);
			sequence_ = sequence;
			return sequence;
		}

		enum SSQ_STATUS ack() const
		{
			const uint32_t ack = OsalAtomicAcquireLoad(&shared_->ack_);
			//const int32_t ack = ameba_atomic_acquire_load(&shared_->ack_);
			return (ack - sequence_) & ~1 ? SSQ_PENDING /* seq differ */ :
				   ack & 1 ? SSQ_DONE : SSQ_READ;
		}

		bool ack(int32_t sequence) const
		{
			return shared_->ack_ - sequence >= 0;
		}

	private:
		int32_t     sequence_;
		Shared *const shared_;
	};

	class Observer
	{
	public:
		Observer(Shared *shared)
			: sequence_(0), seed_(1), shared_(shared)
		{
			shared->init();
		}

		bool poll(T &value)
		{
			Shared *shared = shared_;
			uint32_t before = shared->sequence_;
			if (before == sequence_) {
				return false;
			}
			for (int tries = 0; ;) {
				const int MAX_TRIES = 5;
				if (before & 1) {
					if (++tries >= MAX_TRIES) {
						return false;
					}
					before = shared->sequence_;
				} else {
					//ameba_memory_barrier();
					OsalMemoryBarrier();
					T temp = shared->value_;
					//int32_t after = ameba_atomic_release_load(&shared->sequence_);
					uint32_t after = OsalAtomicReleaseLoad(&shared->sequence_);
					if (after == before) {
						value = temp;
						shared->ack_ = before;
						sequence_ = before;
						return true;
					}
					if (++tries >= MAX_TRIES) {
						return false;
					}
					before = after;
				}
			}
		}

		void done()
		{
			const uint32_t ack = shared_->ack_ + 1;
			OsalAtomicReleaseStore(ack, &shared_->ack_);
			//const int32_t ack = shared_->ack_ + 1;
			//ameba_atomic_release_store(ack, &shared_->ack_);
		}

	private:
		uint32_t     sequence_;
		int         seed_;
		Shared *const shared_;
	};

#if 0
	SingleStateQueue(void /*Shared*/ *shared);
	/*virtual*/ ~SingleStateQueue() { }

	static size_t size()
	{
		return sizeof(Shared);
	}
#endif

};

}

#endif

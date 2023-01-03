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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_H

#include <map>

#include "osal_cxx/refptr.h"
#include "utils/nocopyable.h"

#include "media/utils/message_looper.h"

namespace ameba::media
{

class RBuffer;
class RString;
class MessageHandler;

class ReplyMessage : public RefPtr
{
public:
	explicit ReplyMessage(const sptr<MessageLooper> &looper)
		: looper_(looper),
		  replied_(false)
	{
	}

private:
	friend class Message;
	friend class MessageLooper;

	sptr<MessageLooper> GetLooper() const
	{
		return looper_.promote();
	}

	bool RetrieveReply(sptr<Message> *reply)
	{
		if (replied_) {
			*reply = reply_;
			reply_.clear();
		}
		return replied_;
	}

	res_t SetReply(const sptr<Message> &reply);

	wptr<MessageLooper> looper_;
	sptr<Message> reply_;
	bool replied_;
};

class Message : public RefPtr
{
public:
	Message();
	Message(uint32_t what, const sptr<const MessageHandler> &handler);

	void SetWhat(uint32_t what);
	uint32_t What() const;

	void SetTargetHandler(const sptr<const MessageHandler> &handler);

	void Clear();

	void SetInt32(const char *name, int32_t value);
	void SetInt64(const char *name, int64_t value);
	void SetSize(const char *name, size_t value);
	void SetFloat(const char *name, float value);
	void SetDouble(const char *name, double value);
	void SetPointer(const char *name, void *value);
	void SetString(const char *name, const char *s, ssize_t len = -1);
	void SetString(const char *name, const RString &s);
	void SetObject(const char *name, const sptr<RefPtr> &obj);
	void SetBuffer(const char *name, const sptr<RBuffer> &buffer);
	void SetMessage(const char *name, const sptr<Message> &obj);

	bool FindInt32(const char *name, int32_t *value) const;
	bool FindInt64(const char *name, int64_t *value) const;
	bool FindSize(const char *name, size_t *value) const;
	bool FindFloat(const char *name, float *value) const;
	bool FindDouble(const char *name, double *value) const;
	bool FindPointer(const char *name, void **value) const;
	bool FindString(const char *name, RString *value) const;
	bool FindObject(const char *name, sptr<RefPtr> *obj) const;
	bool FindBuffer(const char *name, sptr<RBuffer> *buffer) const;
	bool FindMessage(const char *name, sptr<Message> *obj) const;

	res_t Post(int64_t delay_us = 0);
	res_t PostAndWaitResponse(sptr<Message> *response);
	bool  SenderWaitResponse(sptr<ReplyMessage> *reply_id);
	res_t PostReply(const sptr<ReplyMessage> &reply_id);

	sptr<Message> Duplicate() const;

	sptr<Message> ChangesFrom(const sptr<const Message> &other, bool deep = false) const;

	RString DebugString(int32_t indent = 0) const;

	enum Type {
		kTypeInt32,
		kTypeInt64,
		kTypeSize,
		kTypeFloat,
		kTypeDouble,
		kTypePointer,
		kTypeString,
		kTypeObject,
		kTypeMessage,
		kTypeBuffer,
	};

	size_t CountEntries() const;
	const char *GetEntryNameAt(size_t index, Type *type) const;

	size_t FindEntryByName(const char *name) const;
	res_t SetEntryNameAt(size_t index, const char *name);
	res_t RemoveEntryAt(size_t index);

public:
	virtual ~Message();

private:
	friend class MessageLooper;

	uint32_t what_;

	// used only for debugging
	MessageLooper::HandlerID target_;

	wptr<MessageHandler> handler_;
	wptr<MessageLooper> looper_;

	class Item
	{
	public:
		union {
			int32_t int32_value_;
			int64_t int64_value_;
			size_t size_value_;
			float float_value_;
			double double_value_;
			void *ptr_value_;
			RefPtr *ref_value_;
			RString *string_value_;
		} u;
		const char *name_;
		size_t name_length_;
		Type type_;
		void SetName(const char *name, size_t len);
	};

	enum {
		kMaxNumItems = 64
	};
	Item items_[kMaxNumItems];
	size_t item_num_;

	Item *AllocateItem(const char *name);
	void FreeItemValue(Item *item);
	const Item *FindItem(const char *name, Type type) const;

	void SetObjectInternal(
		const char *name, const sptr<RefPtr> &obj, Type type);

	size_t FindItemIndex(const char *name, size_t len) const;

	void Deliver();

	DISALLOW_COPY_AND_MOVE(Message);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_H
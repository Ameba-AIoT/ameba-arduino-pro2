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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_STRING_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_STRING_H

#include <sys/types.h>
#include <string>

#include "osal_cxx/errors.h"

namespace ameba::media
{

class RString
{
public:
	RString();
	RString(const char *s);  // NOLINT, implicit conversion
	RString(const char *s, size_t size);
	RString(const std::string &from);  // NOLINT, implicit conversion
	RString(const RString &from);
	RString(const RString &from, size_t offset, size_t n);
	~RString();

	RString &operator=(const RString &from);
	void SetTo(const char *s);
	void SetTo(const char *s, size_t size);
	void SetTo(const RString &from, size_t offset, size_t n);

	size_t Size() const;
	const char *Str() const;

	bool Empty() const;

	void Clear();
	void Trim();
	void Erase(size_t start, size_t n);

	void Append(char c)
	{
		Append(&c, 1);
	}
	void Append(const char *s);
	void Append(const char *s, size_t size);
	void Append(const RString &from);
	void Append(const RString &from, size_t offset, size_t n);
	void Append(int x);
	void Append(unsigned x);
	void Append(long x);
	void Append(unsigned long x);
	void Append(long long x);
	void Append(unsigned long long x);
	void Append(float x);
	void Append(double x);
	void Append(void *x);

	void Insert(const RString &from, size_t insertion_pos);
	void Insert(const char *from, size_t size, size_t insertion_pos);

	ssize_t Find(const char *sub_string, size_t start = 0) const;

	bool operator==(const RString &other) const;
	bool operator!=(const RString &other) const
	{
		return !operator==(other);
	}
	bool operator<(const RString &other) const;
	bool operator>(const RString &other) const;

	int Compare(const RString &other) const;
	int CompareIgnoreCase(const RString &other) const;

	bool StartsWith(const char *prefix) const;

	void Tolower();

private:
	static const char *g_empty_string_;

	char *data_;
	size_t size_;
	size_t alloc_size_;

	void MakeMutable();
};

RString RStringPrintf(const char *format, ...);

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_STRING_H

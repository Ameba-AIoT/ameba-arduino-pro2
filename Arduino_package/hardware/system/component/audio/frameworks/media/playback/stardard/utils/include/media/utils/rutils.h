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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_UTILS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_UTILS_H

#include <string>
#include <memory>
#include <codecvt>
#include <locale>

/* ============================ math templates ============================ */

/* T must be integer type, den must not be 0 */
template<class T>
inline static const T DivRound(const T &num, const T &den)
{
	if ((num >= 0) ^ (den >= 0)) {
		return (num - den / 2) / den;
	} else {
		return (num + den / 2) / den;
	}
}

/* == ceil(num / den). T must be integer type, den must not be 0 */
template<class T>
inline static const T DivUp(const T &num, const T &den)
{
	if (den < 0) {
		return (num < 0 ? num + den + 1 : num) / den;
	} else {
		return (num < 0 ? num : num + den - 1) / den;
	}
}

/* == ceil(num / den) * den. T must be integer type, alignment must be positive power of 2 */
template<class T, class U>
inline static const T Align(const T &num, const U &den)
{
	return (num + (T)(den - 1)) & (T)~(den - 1);
}

template<class T>
inline static const T &min(const T &a, const T &b)
{
	return a < b ? a : b;
}

template<class T>
inline static const T &max(const T &a, const T &b)
{
	return a > b ? a : b;
}

inline std::u16string ToUTF16(std::string str)
{
	return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t > {}.from_bytes(str);
}

inline std::string ToUTF8(std::u16string str16)
{
	return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t > {}.to_bytes(str16);
}

inline std::u32string ToUTF32(std::string str)
{
	return std::wstring_convert< std::codecvt_utf8<char32_t>, char32_t > {}.from_bytes(str);
}

inline std::string ToUTF8(std::u32string str32)
{
	return std::wstring_convert< std::codecvt_utf8<char32_t>, char32_t > {}.to_bytes(str32);
}

inline std::wstring ToWcharT(std::string str)
{
	return std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t > {}.from_bytes(str);
}

inline std::string ToUTF8(std::wstring wstr)
{
	return std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t > {}.to_bytes(wstr);
}

template<typename ... Args>
inline std::string FormatString(const std::string &format, Args ... args)
{
	auto size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template<class T>
inline static T abs(const T &a)
{
	return a < 0 ? -a : a;
}

// needle is in range [hayStart, hayStart + haySize)
template<class T, class U>
inline static bool IsInRange(const T &hayStart, const U &haySize, const T &needle)
{
	return (T)(hayStart + haySize) >= hayStart && needle >= hayStart && (U)(needle - hayStart) < haySize;
}

// [needleStart, needleStart + needleSize) is in range [hayStart, hayStart + haySize)
template<class T, class U>
inline static bool IsInRange(
	const T &hayStart, const U &haySize, const T &needleStart, const U &needleSize)
{
	return IsInRange(hayStart, haySize, needleStart)
		   && (T)(needleStart + needleSize) >= needleStart
		   && (U)(needleStart + needleSize - hayStart) <= haySize;
}

template<typename ... Args>
inline void AppendFormat(std::string &dst, const std::string &format, Args ... args)
{
	dst += FormatString(format, args ...);
}

inline void Append(std::string &dst, const char *other)
{
	std::string str = other;
	dst += str;
}

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_UTILS_H

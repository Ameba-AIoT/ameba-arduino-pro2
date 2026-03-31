#pragma once

#include <cstring>
#include <stdlib.h>

namespace ministd {
	class string {
		protected:
			char *m_s;

		char * _strdup(const char *src) {
			char *str = NULL;
			char *p = NULL;
			int len = 0;

			while (src[len])
				len++;
			str = (char*) malloc(len + 1);
			p = str;
			while (*src)
				*p++ = *src++;
			*p = '\0';
			return str;
		}

		public:
			string() { m_s = NULL; }
			string(const string &src) {
				if (src.m_s) {
					m_s = _strdup(src.m_s);
				} else {
					m_s = NULL;
				}
			}
			string(const char *src, size_t size) {
				if (src) {
					m_s = (char *)malloc(size + 1);
					memcpy(m_s, src, size);
					m_s[size] = '\0';
				} else {
					m_s = NULL;
				}
			}
			string(const char *src) { m_s = _strdup(src); }
			~string() { if (m_s) free(m_s); }
			string &operator=(const string &src) {
				if (m_s) free(m_s);
				if (src.m_s) {
					m_s = _strdup(src.m_s);
				} else {
					m_s = NULL;
				}
				return *this;
			}

			bool operator==(const string &src) {
				if (m_s && src.m_s) {
					return strcmp(m_s, src.m_s) == 0;
				} else {
					return m_s == src.m_s;
				}
			}
			bool operator<(const string &src) {
				return (m_s && src.m_s) ? (strcmp(m_s, src.m_s) < 0) : (m_s < src.m_s);
			}
			bool operator>(const string &src) {
				return (m_s && src.m_s) ? (strcmp(m_s, src.m_s) > 0) : (m_s > src.m_s);
			}
		public:
			const char *c_str() const { return m_s ? m_s : ""; }
			size_t size() const { return m_s ? strlen(m_s) : 0; }

	};
}
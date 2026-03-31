#pragma once

#include <stdlib.h>

namespace ministd {
	template <typename T> class ListNode {
		public:
			T data;
			ListNode *next;
			ListNode *prev;

		public:
			ListNode(T &data, ListNode *next, ListNode *prev):data(data), next(next), prev(prev) {
				if (prev) {
					prev->next = this;
				}
				if (next) {
					next->prev = this;
				}
			}
			ListNode() { this->next = NULL; this->prev = NULL; }
			ListNode(const ListNode &src) {
				data = src.data;
				next = src.next;
				prev = src.prev;
			}
			~ListNode() {}

	};

	template <typename T> class list {
		protected:
			ListNode<T> *m_head;
			ListNode<T> *m_tail;
			size_t m_count;

		public:
			list() {
				m_head = m_tail = nullptr;
				m_count = 0;
			}

			~list() {}

		public:
			list &operator=(const list &src) {
				if (src.m_head != NULL) {
					ListNode<T> *node = src.m_head;
					while (node != src.m_tail) {
						push_back(node->data);
						node = node->next;
					}
				}
				return *this;
			}
			void push_back(T &obj) {
				ListNode<T> *node = new ListNode<T>(obj, nullptr, m_tail);
				if (m_head == nullptr && m_tail == nullptr) {
					m_head = m_tail = node;
				} else {
					// unlikely to be here
				}
				m_count++;
			}
			void push_front(T &obj) {
				ListNode<T> *node = new ListNode<T>(obj, m_head, nullptr);
				if (m_head == nullptr && m_tail == nullptr) {
					m_head = m_tail = node;
				} else {
					// unlikely to be here
				}
				m_count++;
			}
			T& pop_back() {
				if (m_tail != nullptr) {
					T &obj = m_tail->data;
					if (m_head == m_tail) {
						m_head = m_tail = nullptr;
					} else {
						m_tail = m_tail->prev;
						m_tail->next = nullptr;
					}
					m_count++;
					return obj;
				}
			}
			T& pop_front() {
				if (m_head != nullptr) {
					T &obj = m_head->data;
					if (m_head == m_tail) {
						m_head = m_tail = nullptr;
					} else {
						m_head = m_head->next;
						m_head->prev = nullptr;
					}
					m_count--;
					return obj;
				}
			}
			void clear() {
				ListNode<T> *node = m_head;
				while (node != nullptr) {
					ListNode<T> *next = node->next;
					delete node;
					node = next;
				}
				m_head = m_tail = nullptr;
				m_count = 0;
			}
			inline size_t size() {
				return m_count;
			}
	};
}

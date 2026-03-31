#pragma once

extern "C" {
#include "avl_bf.h"
};

#include "mypair.hpp"

namespace ministd {

template <typename TK, typename TV> class map {
    protected:
        avltree *m_avl;

    public:
        map() {
            create();
        }
        ~map() {
            avl_destroy(m_avl);
        }

        void create() {
            if ((m_avl = avl_create(map::nodeCompare, map::nodeDestroy)) == nullptr) {
                //printf("create avl tree failed\n");
            }
        }
        size_t size() { return m_avl->count; }
        static int nodeCompare(const void *d1, const void *d2) {
            pair<TK, TV> *p1 = (pair<TK, TV> *)d1;
            pair<TK, TV> *p2 = (pair<TK, TV> *)d2;

            if (p1->first == p2->first) {
                return 0;
            }

            if (p1->first < p2->first) {
                return -1;
            }

            return 1;
        }
        static void nodeDestroy(void *d) {
            pair<TK, TV> *p = (pair<TK, TV> *)d;
            delete p;
        }

        TV& operator[](TK &key) {
            iterator it = find(key);
            if (it == end()) { // if not found, the create a map entry
                TV value;
                insert({key, value});
                it = find(key);
            }
            return it->second;
        }

        class iterator {
            public:
                avltree *m_avl;
                avlnode *m_node;

            public:
                iterator():m_avl(nullptr), m_node(nullptr) {}
                iterator(avltree *avl):m_avl(avl), m_node(nullptr) {}
                iterator(avltree *avl, avlnode *node):m_avl(avl), m_node(node) {}
                iterator(const iterator &i) { m_avl = i.m_avl; m_node = i.m_node; }
                ~iterator() {}

            public:
                iterator &operator=(const iterator& rhs) { m_avl = rhs.m_avl; m_node = rhs.m_node; return *this; }
                bool operator==(const iterator& rhs) const { return (m_avl == rhs.m_avl && m_node == rhs.m_node); }
                bool operator!=(const iterator& rhs) const { return (m_avl != rhs.m_avl || m_node != rhs.m_node); }
                pair<TK,TV> &operator*() const { 
                    pair<TK, TV> *p = (pair<TK, TV> *)m_node->data;
                    return *p;
                }
                pair<TK,TV> *operator->() {
                    pair<TK, TV> *p = (pair<TK, TV> *)m_node->data;
                    return p;
                }
                iterator operator++(int) {
                    iterator v(*this);
                    m_node = avl_successor_end(m_avl, m_node);
                    return v;
                }
                iterator &operator++() {
                    m_node = avl_successor_end(m_avl, m_node);
                    return *this;
                }
        };

        iterator begin() const {
            return iterator(m_avl, m_avl->min);
        }

        iterator end() const {
            return iterator(m_avl, nullptr);
        }

        void insert(const pair<TK, TV> &p) {
            avl_insert(m_avl, new pair<TK, TV>(p.first, p.second));
        }

        void erase(const TK &key) {
            iterator it = find(key);
            if (it != end())
                erase(it);
        }

        void erase(const iterator &it) {
            avl_delete(it.m_avl, it.m_node, 0); // 0 --> not keeping
        }

        void clear() {
            avl_destroy(m_avl);
            create();
        }

        iterator find(TK key) const {
            pair<TK, TV> p = {key, TV()};
            avlnode *node = avl_find(m_avl, (void *)&p);
            return iterator(m_avl, node);
        }

        iterator &operator=(iterator& i) { }
};

}
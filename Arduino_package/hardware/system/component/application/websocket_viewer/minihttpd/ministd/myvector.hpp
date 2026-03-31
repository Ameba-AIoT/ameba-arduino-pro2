#pragma once

namespace ministd {
    template <typename T> class vector {
        private:
            T** arr;
            int capacity;
            int length;
        
        public:
            vector(int n = 16) {
                capacity = n;
                arr = (T** )calloc(sizeof(T *), n);
                length = 0;
            }

            ~vector() {
                for (int i=0; i<length; i++) {
                    delete arr[i];
                }
                free(arr);
            }
        
            int push_back(T& data) {
                if (length == capacity) {
                    capacity *= 2;
                    arr = (T **) realloc(arr, sizeof(T *) * capacity);
                }
                arr[length++] = new T(data);
                return length;
            }

            int size() const { return length; }

            void clear() {
                for (int i=0; i<length; i++) {
                    delete arr[i];
                    arr[i] = 0;
                }
                length = 0;
            }

            T& operator[](const int index) {
                return *(arr[index]);
            }
        
            class iterator {
                private:
                    T** arr;
                    int idx;
            
                public:
                    iterator() : arr(nullptr), idx(0) {}
                    iterator(T** a, int i) : arr(a), idx(i) {}
                    iterator(const iterator &i) { arr = i.arr; idx = i.idx; }
                    iterator &operator=(iterator& i) { arr = i.arr; idx = i.idx; }
                    bool operator==(const iterator& rhs) const { return (arr == rhs.arr && idx == rhs.idx); }
                    bool operator!=(const iterator& rhs) const { return (arr != rhs.arr || idx != rhs.idx); }
                    T &operator*() const { return *arr[idx]; }
                    T *operator->() { return arr[idx]; }
                    iterator& operator++() { idx++; return *this; }
                    iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }
                    iterator& operator-(int i) { idx -= i; return *this; }
                    iterator& operator+(int i) { idx += i; return *this; }
            };
            
            iterator begin() const {
                return iterator(this->arr, 0);
            }
            iterator end() const {
                return iterator(this->arr, length);
            }
    };
}
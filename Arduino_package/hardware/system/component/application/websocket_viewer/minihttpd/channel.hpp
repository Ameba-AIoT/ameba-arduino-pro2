#include <pthread.h>

template <typename T> class Channel {
    protected:
        T* m_arr;
        int m_front;
        int m_back;
        int m_size;
        int m_capacity;
        pthread_cond_t m_condPush;
        pthread_cond_t m_condPop;
        pthread_mutex_t m_mutex;

    public:
        Channel(int capacity=8) : m_front(0), m_back(0), m_size(0), m_capacity(capacity) {
            pthread_cond_init(&m_condPush, NULL);
            pthread_cond_init(&m_condPop, NULL);
            pthread_mutex_init(&m_mutex, NULL);
            m_arr = new T[capacity];
        }

        ~Channel() {
            pthread_cond_destroy(&m_condPush);
            pthread_cond_destroy(&m_condPop);
            pthread_mutex_destroy(&m_mutex);
            delete[] m_arr;
        }

    public:
        void push_back(const T& data) {
            pthread_mutex_lock(&m_mutex);
            while (full()) {
                pthread_cond_wait(&m_condPush, &m_mutex);
            }
            enqueue(data);
            pthread_mutex_unlock(&m_mutex);
            pthread_cond_signal(&m_condPop);
        }

        T pop_front() {
            pthread_mutex_lock(&m_mutex);
            while (empty()) {
                pthread_cond_wait(&m_condPop, &m_mutex);
            }
            T t = dequeue();
            pthread_mutex_unlock(&m_mutex);
            pthread_cond_signal(&m_condPush);

            return t;
        }

    protected:
        void enqueue(const T& data) {
            m_arr[m_back] = data;
            m_back = (m_back + 1) % m_capacity;
            m_size++;
        }

        T dequeue() {
            T data = m_arr[m_front];
            m_front = (m_front + 1) % m_capacity;
            m_size--;

            return data;
        }

        bool full() const {
            return (m_size == m_capacity);
        }

        bool empty() const {
            return (m_size == 0);
        }
};

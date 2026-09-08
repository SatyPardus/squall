#ifndef STORM_QUEUE_TS_HEAP_HPP
#define STORM_QUEUE_TS_HEAP_HPP

#include "storm/memblock/CMemBlock.hpp"
#include <cstdint>
#include <cstring>

template <class T>
class TSHeap : public CMemBlock {
    public:
    // Member variables
    uint32_t m_chunk = 0;
    uint32_t m_capacity = 0;
    uint32_t m_count = 0;

    // Member functions
    TSHeap(uint32_t initial, uint32_t chunk);
    T* Ptr();
    uint32_t Count() const;
    void Insert(const T& entry);
    void Pop(T* out);
    bool Erase(uint32_t index, uint32_t count);
};

// OFFSET: 0x7F0D40
template <class T>
TSHeap<T>::TSHeap(uint32_t initial, uint32_t chunk) {
    this->Resize(sizeof(T) * initial, false);

    this->m_chunk = chunk;
    this->m_capacity = initial;
    this->m_count = 0;

    if (initial >= 1) {
        ++this->m_count;
        return;
    }

    if (chunk) {
        uint32_t grow = chunk;

        if (grow <= 1 - initial) {
            grow = 1 - initial;
        }

        if (this->Resize(sizeof(T) * (grow + initial), true)) {
            this->m_capacity += grow;
            ++this->m_count;
        }
    }
}

template <class T>
T* TSHeap<T>::Ptr() {
    return static_cast<T*>(this->m_data);
}

template <class T>
uint32_t TSHeap<T>::Count() const {
    return this->m_count;
}

// OFFSET: 0x7A0F50 (particles), 0x7F0DC0 (lights)
template <class T>
void TSHeap<T>::Insert(const T& entry) {
    if (this->m_count + 1 > this->m_capacity) {
        if (this->m_chunk) {
            uint32_t grow = this->m_chunk;
            const uint32_t needed = this->m_count - this->m_capacity + 1;

            if (grow <= needed) {
                grow = needed;
            }

            if (this->Resize(sizeof(T) * (grow + this->m_capacity), true)) {
                this->m_capacity += grow;
                ++this->m_count;
            }
        }
    } else {
        ++this->m_count;
    }

    T* data = this->Ptr();
    uint32_t index = this->m_count - 1;

    if (this->m_count != 1 && index != 1) {
        uint32_t parent;

        do {
            parent = index >> 1;

            if (!T::HasHigherPriority(entry, data[parent])) {
                break;
            }

            data[index] = data[parent];
            index >>= 1;
        } while (parent > 1);
    }

    data[index] = entry;
}

// OFFSET: 0x97E080 (particles), 0x7F1280 (lights)
template <class T>
void TSHeap<T>::Pop(T* out) {
    T* data = this->Ptr();

    *out = data[1];

    const uint32_t count = this->m_count;
    const T last = data[count - 1];

    if (count) {
        this->Erase(count - 1, 1);
    }

    if (this->m_count < 2) {
        return;
    }

    data = this->Ptr();

    const uint32_t limit = this->m_count - 1;
    const uint32_t half = limit >> 1;

    uint32_t index = 1;

    if (half) {
        while (1) {
            uint32_t child = 2 * index;

            if (child < limit && T::HasHigherPriority(data[child + 1], data[child])) {
                ++child;
            }

            if (T::HasHigherPriority(last, data[child])) {
                break;
            }

            const bool more = child <= half;
            data[index] = data[child];
            index = child;

            if (!more) {
                break;
            }
        }
    }

    data[index] = last;
}

// OFFSET: 0x7A0C70
template <class T>
bool TSHeap<T>::Erase(uint32_t index, uint32_t count) {
    if (index >= this->m_count) {
        return false;
    }

    uint32_t n = count;

    if (index + count > this->m_count) {
        n = this->m_count - index;
    }

    const uint32_t tail = this->m_count - index - n;

    if (tail) {
        T* data = this->Ptr();
        memmove(&data[index], &data[index + n], sizeof(T) * tail);
    }

    this->m_count -= n;

    return true;
}

#endif

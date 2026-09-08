#include "storm/memblock/CMemBlock.hpp"
#include <bc/memory/Storm.hpp>
#include <cstring>

// OFFSET: 0x984670
CMemBlock::~CMemBlock() {
    if (this->m_alloc) {
        if (this->m_alloc != reinterpret_cast<void*>(-1)) {
            SMemFree(this->m_alloc, ".\\cmemblock.cpp", 364, 0);
        }

        this->m_dataBytes = 0;
        this->m_allocBytes = 0;
        this->m_data = nullptr;
        this->m_alloc = nullptr;
    }
}

// OFFSET: 0x9847D0
bool CMemBlock::Resize(uint32_t bytes, bool noClear) {
    if (bytes != this->m_dataBytes) {
        const uint32_t lead = this->m_allocBytes - this->m_dataBytes;
        const uint32_t total = lead + bytes;

        void* raw = this->m_alloc == reinterpret_cast<void*>(-1)
                        ? SMemAlloc(total, ".\\cmemblock.cpp", 364, 0)
                        : SMemReAlloc(this->m_alloc, total, ".\\cmemblock.cpp", 364, 0);

        this->m_alloc = raw;
        this->m_data = static_cast<char*>(raw) + lead;

        if (bytes > this->m_dataBytes) {
            memset(static_cast<char*>(this->m_data) + this->m_dataBytes, 0, bytes - this->m_dataBytes);
        }

        this->m_allocBytes = total;
        this->m_dataBytes = bytes;
    }

    if (!noClear) {
        memset(this->m_data, 0, this->m_dataBytes);
    }

    return true;
}

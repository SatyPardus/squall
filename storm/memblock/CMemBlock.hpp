#ifndef STORM_MEMBLOCK_C_MEM_BLOCK_HPP
#define STORM_MEMBLOCK_C_MEM_BLOCK_HPP

#include <cstdint>

class CMemBlock {
    public:
    // Member variables
    void* m_alloc = reinterpret_cast<void*>(-1);
    uint32_t m_allocBytes = 0;
    void* m_data = nullptr;
    uint32_t m_dataBytes = 0;

    // Member functions
    CMemBlock() = default;
    virtual ~CMemBlock();
    bool Resize(uint32_t bytes, bool noClear);
};

#endif

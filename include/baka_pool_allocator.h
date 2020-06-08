#ifndef _BAKA_POOL_ALLOCATOR_H_
#define _BAKA_POOL_ALLOCATOR_H_

#include <cstdint>
#include <cstddef>

namespace baka
{
    
class PoolAllocator
{
public:
    PoolAllocator() : pData(nullptr), sizeOfBlock(0) {}
    PoolAllocator(size_t blockSize, uint32_t blockCount);
    ~PoolAllocator();

private:
    uint8_t *pData;
    size_t sizeOfBlock;
    uint32_t blockCount;
};

} // namespace baka

#endif
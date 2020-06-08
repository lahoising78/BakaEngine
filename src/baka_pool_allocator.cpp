#include <baka_logger.h>
#include <baka_pool_allocator.h>

namespace baka
{
    
PoolAllocator::PoolAllocator(size_t blockSize, uint32_t blockCount)
{
    BAKA_ASSERT(blockSize);
    BAKA_ASSERT(blockCount);

    this->pData = (uint8_t*)malloc(blockSize * blockCount);
    BAKA_ASSERT((this->pData));

    this->blockCount = blockCount;
    this->sizeOfBlock = blockSize;

    bakalog("allocated pool of %lu blocks, with %lu bytes per block", this->blockCount, this->sizeOfBlock);
}

PoolAllocator::~PoolAllocator()
{
    if(this->pData)
    {
        free(this->pData);
        this->pData = nullptr;
        bakalog("pool allocator has been freed");
    }
}


} // namespace baka
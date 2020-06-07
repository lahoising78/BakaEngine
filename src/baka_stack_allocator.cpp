#include <baka_logger.h>
#include <cstdlib>
#include <cstring>
#include "baka_stack_allocator.h"

namespace baka
{
    
StackAllocator::StackAllocator(size_t stackSize)
{
    this->stack = (uint8_t*)malloc(stackSize);
    BAKA_ASSERT(this->stack);
    
    this->stackEnd = this->stack + stackSize;
    this->stackTopOffset = this->stack;
    bakalog("stack allocator initialized with %lu bytes. Stack head at %lu", stackSize, this->stack);
}

StackAllocator::~StackAllocator()
{
    BAKA_ASSERT(this->stack);
    free(this->stack);
    bakalog("stack allocator of size %lu was freed", (this->stackEnd - this->stack));
}

StackAllocatorMarker StackAllocator::Allocate(size_t size)
{
    BAKA_ASSERT(size);
    BAKA_ASSERT( this->stackEnd - (this->stackTopOffset + size) > 0 );

    StackAllocatorMarker marker = {};

    marker.allocatedSize = size;
    marker.pData = this->stackTopOffset;

    this->stackTopOffset += size;

    return marker;
}
void StackAllocator::FreeStackUntil(StackAllocatorMarker &marker)
{
    this->stackTopOffset = (uint8_t*)marker.pData;

    marker = {};
}

} // namespace baka

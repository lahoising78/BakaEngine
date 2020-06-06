#ifndef _BAKA_STACK_ALLOCATOR_H_
#define _BAKA_STACK_ALLOCATOR_H_

#include <cstdint>

namespace baka
{
    struct StackAllocatorMarker
    {
        size_t allocatedSize;
        void *pData;
    };

    class StackAllocator
    {
    public:
        StackAllocator() : stack(nullptr), stackTopOffset(nullptr), stackEnd(nullptr) {  }
        StackAllocator(size_t stackSize);
        ~StackAllocator();
        StackAllocatorMarker Allocate(size_t size);
        void FreeStackUntil(StackAllocatorMarker &marker);

    private:
        uint8_t *stack;
        uint8_t *stackTopOffset;
        uint8_t *stackEnd;

    };
} // namespace baka

#endif
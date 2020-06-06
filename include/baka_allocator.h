#ifndef _BAKA_ALLOCATOR_H_
#define _BAKA_ALLOCATOR_H_

#include <cstdlib>

namespace baka
{
    class AlignedAllocator
    {
    private:
        void *AllocateAligned(size_t size, size_t alignment);
        virtual void *AllocateUnaligned(size_t size) = 0;
        void DeleteAlignedAllocation(void *p);
    };
} // namespace baka

#endif
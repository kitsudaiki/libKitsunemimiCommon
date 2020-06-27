/**
 *  @file       memory_counter.cpp
 *
 *  @brief      Counter for allocated and freed bytes to identify memory-leaks
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/memory_counter.h>

#include <stdio.h>

Kitsunemimi::MemoryCounter Kitsunemimi::MemoryCounter::globalMemoryCounter;

//==================================================================================================
// Overrides for new and delete
//==================================================================================================

/**
 * Info: I do not override "void operator delete(void* ptr, size_t size)", which is also available
 *       since c++14, because it not every time used, for example std::map use only the variant
 *       without the size-parameter. So I don't have the size-value in each delete, which is the
 *       reason, why I write this additonally in my allocated memory.
 */

void*
operator new(size_t size)
{
    void* ptr = malloc(sizeof(size_t) + size);
    //*((size_t*)ptr) = size;
    Kitsunemimi::increaseGlobalMemoryCounter(0);
    //return (void*) ((size_t *)ptr + 1);
    return ptr;
}

void*
operator new[](size_t size)
{
    void* ptr = malloc(sizeof(size_t) + size);
    //*((size_t*)ptr) = size;
    Kitsunemimi::increaseGlobalMemoryCounter(0);
    //return (void*) ((size_t *)ptr + 1);
    return ptr;
}

void
operator delete(void* ptr)
{
    //ptr = (size_t*)ptr - 1;
    //const size_t size = *((size_t*)ptr);
    Kitsunemimi::decreaseGlobalMemoryCounter(0);
    free(ptr);
}

void
operator delete[](void* ptr)
{
    //ptr = (size_t*)ptr - 1;
    //const size_t size = *((size_t*)ptr);
    Kitsunemimi::decreaseGlobalMemoryCounter(0);
    free(ptr);
}

//==================================================================================================

namespace Kitsunemimi
{

using Kitsunemimi::MemoryCounter;

/**
 * @brief increase global memory-counter
 * @param size amount of bytes to increase the counter
 */
void
increaseGlobalMemoryCounter(const size_t size)
{
    while(MemoryCounter::globalMemoryCounter.lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    MemoryCounter::globalMemoryCounter.actualAllocatedSize += size;
    MemoryCounter::globalMemoryCounter.numberOfActiveAllocations++;
    MemoryCounter::globalMemoryCounter.lock.clear(std::memory_order_release);
}

/**
 * @brief decrease global memory-counter
 * @param size amount of bytes to decrease the counter
 */
void
decreaseGlobalMemoryCounter(const size_t size)
{

    while(MemoryCounter::globalMemoryCounter.lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    MemoryCounter::globalMemoryCounter.actualAllocatedSize -= size;
    MemoryCounter::globalMemoryCounter.numberOfActiveAllocations--;
    MemoryCounter::globalMemoryCounter.lock.clear(std::memory_order_release);
}

}

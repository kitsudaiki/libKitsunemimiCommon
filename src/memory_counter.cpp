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


void*
operator new(size_t size)
{
    void* ptr = malloc(sizeof(size_t) + size);
    *((size_t*)ptr) = size;
    Kitsunemimi::increaseGlobalMemoryCounter(size);
    return (void*) ((size_t *)ptr + 1);
}

void*
operator new[](size_t size)
{
    void* ptr = malloc(sizeof(size_t) + size);
    *((size_t*)ptr) = size;
    Kitsunemimi::increaseGlobalMemoryCounter(size);
    return (void*) ((size_t *)ptr + 1);
}

void
operator delete(void* ptr)
{
    ptr = (size_t*)ptr - 1;
    const size_t size = *((size_t*)ptr);
     Kitsunemimi::decreaseGlobalMemoryCounter(size);
    free(ptr);
}

void
operator delete[](void* ptr)
{
    ptr = (size_t*)ptr - 1;
    const size_t size = *((size_t*)ptr);
     Kitsunemimi::decreaseGlobalMemoryCounter(size);
    free(ptr);
}


namespace Kitsunemimi
{

    /**
 * @brief increaseGlobalMemoryCounter
 * @param size
 */
void
increaseGlobalMemoryCounter(size_t size)
{
    while(Kitsunemimi::MemoryCounter::globalMemoryCounter.lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    Kitsunemimi::MemoryCounter::globalMemoryCounter.actualAllocatedSize += size;
    Kitsunemimi::MemoryCounter::globalMemoryCounter.lock.clear(std::memory_order_release);
}

/**
 * @brief decreaseGlobalMemoryCounter
 * @param size
 */
void
decreaseGlobalMemoryCounter(size_t size)
{

    while(Kitsunemimi::MemoryCounter::globalMemoryCounter.lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    MemoryCounter::globalMemoryCounter.actualAllocatedSize -= size;
    Kitsunemimi::MemoryCounter::globalMemoryCounter.lock.clear(std::memory_order_release);
}

}

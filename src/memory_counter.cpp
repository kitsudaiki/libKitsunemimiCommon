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

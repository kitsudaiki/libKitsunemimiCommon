/**
 *  @file       memory_counter.h
 *
 *  @brief      Counter for allocated and freed bytes to identify memory-leaks
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef MEMORY_COUNTER_H
#define MEMORY_COUNTER_H

#include <stdlib.h>
#include <atomic>
#include <stdio.h>

void* operator new(size_t size);
void* operator new[](size_t size);
void  operator delete(void* ptr);
void  operator delete[](void* ptr);


namespace Kitsunemimi
{

struct MemoryCounter
{
    int64_t actualAllocatedSize = 0;
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    uint8_t padding[7];

    static Kitsunemimi::MemoryCounter globalMemoryCounter;

    MemoryCounter() {}
};


void increaseGlobalMemoryCounter(const size_t size);
void decreaseGlobalMemoryCounter(const size_t size);

}

#endif // MEMORY_COUNTER_H

/**
 *  @file       memory_leak_test_helper.h
 *
 *  @brief      Helper class for memory-leak-tests
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef MEMORY_LEAK_TEST_HELPER_H
#define MEMORY_LEAK_TEST_HELPER_H

#include <string>
#include <iostream>

#include <libKitsunemimiCommon/memory_counter.h>

namespace Kitsunemimi
{
using Kitsunemimi::MemoryCounter;

class MemoryLeakTestHelpter
{
#define REINIT_TEST() \
    m_currentAllocations = MemoryCounter::globalMemoryCounter.numberOfActiveAllocations; \

#define CHECK_MEMORY() \
    if(MemoryCounter::globalMemoryCounter.numberOfActiveAllocations - m_currentAllocations != 0) \
    {  \
        int64_t ndiff = MemoryCounter::globalMemoryCounter.numberOfActiveAllocations \
                        - m_currentAllocations; \
        std::cout << std::endl; \
        std::cout << "Memory-leak detected" << std::endl; \
        std::cout << "   File: " << __FILE__ << std::endl; \
        std::cout << "   Method: " << __PRETTY_FUNCTION__ << std::endl; \
        std::cout << "   Line: " << __LINE__ << std::endl; \
        std::cout << "   Number of missing deallocations: " << (ndiff) << std::endl; \
        std::cout << std::endl; \
        m_failedTests++; \
    } \
    else \
    { \
        m_successfulTests++; \
    }

public:
    MemoryLeakTestHelpter(const std::string &testName);
    ~MemoryLeakTestHelpter();

protected:
    int64_t m_currentAllocations = 0;

    uint32_t m_failedTests = 0;
    uint32_t m_successfulTests = 0;
};

} // namespace Kitsunemimi

#endif // MEMORY_LEAK_TEST_HELPER_H

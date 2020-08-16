/**
 *  @file       memory_leak_test_helper.cpp
 *
 *  @brief      Helper class for memory-leak-tests
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/test_helper/memory_leak_test_helper.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 *
 * @param testName name for output to identify the test within the output
 */
MemoryLeakTestHelpter::MemoryLeakTestHelpter(const std::string &testName)
{
    m_currentAllocations = MemoryCounter::globalMemoryCounter.numberOfActiveAllocations;
    m_currentSize = MemoryCounter::globalMemoryCounter.actualAllocatedSize;

    std::cout << "------------------------------" << std::endl;
    std::cout << "start " << testName << std::endl << std::endl;
}

/**
 * @brief destructor
 */
MemoryLeakTestHelpter::~MemoryLeakTestHelpter()
{
    std::cout << "tests succeeded: " << m_successfulTests <<std::endl;
    std::cout << "tests failed: " << m_failedTests << std::endl;
    std::cout << "------------------------------" << std::endl << std::endl;

    if(m_failedTests > 0) {
        exit(1);
    }
}

} // namespace Kitsunemimi

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
    void* ptr = malloc(size);
    Kitsunemimi::increaseGlobalMemoryCounter(0);
    return ptr;
}

void*
operator new[](size_t size)
{
    void* ptr = malloc(size);
    Kitsunemimi::increaseGlobalMemoryCounter(0);
    return ptr;
}

void
operator delete(void* ptr) noexcept
{
    free(ptr);
    Kitsunemimi::decreaseGlobalMemoryCounter(0);
}

void
operator delete[](void* ptr) noexcept
{
    free(ptr);
    Kitsunemimi::decreaseGlobalMemoryCounter(0);
}

//==================================================================================================

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

/**
 *  @file       compare_test_helper.h
 *
 *  @brief      Helper class for compare-tests like unit-tests
 *
 *  @details    It counts all successful and failed calls of the TEST_EQUAL and TEST_NOT_EQUAL
 *              macro. In case of a failed macro-call, it shows the file-name, linenumer and
 *              method-name of the failed test.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef COMPARE_TEST_HELPER_H
#define COMPARE_TEST_HELPER_H

#include <string>
#include <iostream>

namespace Kitsunemimi
{

class CompareTestHelper
{
#define TEST_EQUAL(IS_VAL, SHOULD_VAL) \
    if(IS_VAL != SHOULD_VAL) \
    {  \
        m_failedTests++; \
        std::cout << std::endl; \
        std::cout << "Error in Test" << std::endl; \
        std::cout << "   File: " << __FILE__ << std::endl; \
        std::cout << "   Method: " << __PRETTY_FUNCTION__ << std::endl; \
        std::cout << "   Line: " << __LINE__ << std::endl; \
        std::cout << "   Variable: " << #IS_VAL << std::endl; \
        std::cout << "   Should-Value: " << SHOULD_VAL << std::endl; \
        std::cout << "   Is-Value: " << IS_VAL << std::endl; \
        std::cout << std::endl; \
    } \
    else \
    { \
        m_successfulTests++; \
    }

#define TEST_NOT_EQUAL(IS_VAL, SHOULD_NOT_VAL) \
    if(IS_VAL == SHOULD_NOT_VAL) \
    {  \
        m_failedTests++; \
        std::cout << std::endl; \
        std::cout << "Error in Test" << std::endl; \
        std::cout << "   File: " << __FILE__ << std::endl; \
        std::cout << "   Method: " << __PRETTY_FUNCTION__ << std::endl; \
        std::cout << "   Line: " << __LINE__ << std::endl; \
        std::cout << "   Variable: " << #IS_VAL << std::endl; \
        std::cout << "   Should-NOT-Value: " << SHOULD_NOT_VAL << std::endl; \
        std::cout << "   Is-Value: " << IS_VAL << std::endl; \
        std::cout << std::endl; \
    } \
    else \
    { \
        m_successfulTests++; \
    }

public:
    CompareTestHelper(const std::string &testName);
    ~CompareTestHelper();

protected:
    uint32_t m_successfulTests = 0;
    uint32_t m_failedTests = 0;
};

} // namespace Kitsunemimi

#endif // COMPARE_TEST_HELPER_H

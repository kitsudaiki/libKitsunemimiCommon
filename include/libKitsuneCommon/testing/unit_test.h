/**
 *  @file    unit_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief helper-class for unit-tests
 *
 *  @detail This is in all my projects used for unit-tests. It counts all successful and failed
 *          calls of the UNITTEST and UNITTEST_NEG macro. In case of a failed macro-call, it
 *          shows the file-name, linenumer and method-name of the failed test.
 */

#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>

namespace Kitsune
{
namespace Common
{

class UnitTest
{
#define UNITTEST(IS_VAL, SHOULD_VAL) if(IS_VAL != SHOULD_VAL) \
{  \
    m_failedTests++; \
    std::cout << std::endl; \
    std::cout << "Error in Unit-Test" << std::endl; \
    std::cout << "   File: " << __FILE__ << std::endl; \
    std::cout << "   Method: " << __PRETTY_FUNCTION__ << std::endl; \
    std::cout << "   Line: " << __LINE__ << std::endl; \
    std::cout << "   Variable: " << #IS_VAL << std::endl; \
    std::cout << "   Should-Value: " << SHOULD_VAL << std::endl; \
    std::cout << "   Is-Value: " << IS_VAL << std::endl; \
    std::cout << std::endl; \
    } else { \
    m_successfulTests++; \
    }

#define UNITTEST_NEG(IS_VAL, SHOULD_NOT_VAL) if(IS_VAL == SHOULD_NOT_VAL) \
{  \
    m_failedTests++; \
    std::cout << std::endl; \
    std::cout << "Error in negative Unit-Test" << std::endl; \
    std::cout << "   File: " << __FILE__ << std::endl; \
    std::cout << "   Method: " << __PRETTY_FUNCTION__ << std::endl; \
    std::cout << "   Line: " << __LINE__ << std::endl; \
    std::cout << "   Variable: " << #IS_VAL << std::endl; \
    std::cout << "   Is-Value: " << IS_VAL << std::endl; \
    std::cout << std::endl; \
    } else { \
    m_successfulTests++; \
    }

public:
    UnitTest(const std::string testName);
    ~UnitTest();

protected:
    uint32_t m_successfulTests = 0;
    uint32_t m_failedTests = 0;
};

} // namespace Common
} // namespace Kitsune

#endif // TEST_H

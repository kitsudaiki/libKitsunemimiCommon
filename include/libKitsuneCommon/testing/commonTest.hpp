/**
 *  @file    commonTest.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONTEST_HPP
#define COMMONTEST_HPP

#include <string>
#include <iostream>

namespace Kitsune
{

class CommonTest
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
    CommonTest(std::string testName);
    ~CommonTest();

protected:
    uint32_t m_successfulTests = 0;
    uint32_t m_failedTests = 0;
};

} // namespace Kitsune

#endif // COMMONTEST_HPP

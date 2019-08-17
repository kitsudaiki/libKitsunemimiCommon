/**
 *  @file    test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <testing/test.h>

namespace Kitsune
{
namespace Common
{

Test::Test(const std::string testName)
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "start " << testName << std::endl << std::endl;
}

Test::~Test()
{
    std::cout << "tests succeeded: " << m_successfulTests <<std::endl;
    std::cout << "tests failed: " << m_failedTests << std::endl;
    std::cout << "------------------------------" << std::endl << std::endl;

    if(m_failedTests > 0) {
        exit(1);
    }
}

} // namespace Common
} // namespace Kitsune

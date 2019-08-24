/**
 *  @file    unit_test.cpp
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

#include <testing/unit_test.h>

namespace Kitsune
{
namespace Common
{

UnitTest::UnitTest(const std::string testName)
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "start " << testName << std::endl << std::endl;
}

UnitTest::~UnitTest()
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

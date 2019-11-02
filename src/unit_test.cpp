/**
 *  @file       unit_test.cpp
 *
 *  @brief      This is in all my projects used for unit-tests.
 *
 *  @details    It counts all successful and failed
 *              calls of the TEST_EQUAL and TEST_NOT_EQUAL macro. In case of a failed macro-call, it
 *              shows the file-name, linenumer and method-name of the failed test.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsuneCommon/test.h>

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

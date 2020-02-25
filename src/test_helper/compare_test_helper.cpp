/**
 *  @file       compare_test_helper.cpp
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

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

CompareTestHelper::CompareTestHelper(const std::string testName)
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "start " << testName << std::endl << std::endl;
}

CompareTestHelper::~CompareTestHelper()
{
    std::cout << "tests succeeded: " << m_successfulTests <<std::endl;
    std::cout << "tests failed: " << m_failedTests << std::endl;
    std::cout << "------------------------------" << std::endl << std::endl;

    if(m_failedTests > 0) {
        exit(1);
    }
}

} // namespace Kitsunemimi

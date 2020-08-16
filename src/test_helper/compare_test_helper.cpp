/**
 *  @file       compare_test_helper.cpp
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

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 *
 * @param testName name for output to identify the test within the output
 */
CompareTestHelper::CompareTestHelper(const std::string &testName)
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "start " << testName << std::endl << std::endl;
}

/**
 * @brief destructor
 */
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

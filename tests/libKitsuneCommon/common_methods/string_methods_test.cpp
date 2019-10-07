/**
 *  @file    string_methods_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "string_methods_test.h"

#include <libKitsuneCommon/common_methods/string_methods.h>

namespace Kitsune
{
namespace Common
{

StringMethods_Test::StringMethods_Test()
    : Kitsune::Common::UnitTest("StringMethods_Test")
{
    splitStringByDelimiter_test();
    splitStringByLength_test();
}

/**
 * splitStringByDelimiter_test
 */
void
StringMethods_Test::splitStringByDelimiter_test()
{
    // init
    std::string testString = "this is a test-string";

    // run task
    std::vector<std::string> result = splitStringByDelimiter(testString, ' ');

    // check result
    UNITTEST(result.size(), 4);
    UNITTEST(result[0], "this");
    UNITTEST(result[1], "is");
    UNITTEST(result[2], "a");
    UNITTEST(result[3], "test-string");

    // make negative checks
    std::string testStringNeg = "";
    std::vector<std::string> resultNeg = splitStringByDelimiter(testStringNeg, ' ');
    UNITTEST(resultNeg.size(), 0);
}

/**
 * splitStringByLength_test
 */
void
StringMethods_Test::splitStringByLength_test()
{
    // init
    std::string testString = "this is a test-string";

    // run task
    std::vector<std::string> result = splitStringByLength(testString, 5);

    // check result
    UNITTEST(result.size(), 5);
    UNITTEST(result[0], "this ");
    UNITTEST(result[1], "is a ");
    UNITTEST(result[2], "test-");
    UNITTEST(result[3], "strin");
    UNITTEST(result[4], "g");
}

} // namespace Common
} // namespace Kitsune

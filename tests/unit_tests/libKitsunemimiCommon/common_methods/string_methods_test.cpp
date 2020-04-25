/**
 *  @file    string_methods_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "string_methods_test.h"

#include <libKitsunemimiCommon/common_methods/string_methods.h>

namespace Kitsunemimi
{

StringMethods_Test::StringMethods_Test()
    : Kitsunemimi::CompareTestHelper("StringMethods_Test")
{
    splitStringByDelimiter_test();
    splitStringByLength_test();
    replaceSubstring_test();
    removeWhitespaces_test();
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
    std::vector<std::string> result;
    splitStringByDelimiter(result, testString, ' ');

    // check result
    TEST_EQUAL(result.size(), 4);
    TEST_EQUAL(result[0], "this");
    TEST_EQUAL(result[1], "is");
    TEST_EQUAL(result[2], "a");
    TEST_EQUAL(result[3], "test-string");

    // make negative checks
    std::string testStringNeg = "";
    std::vector<std::string> resultNeg;
    splitStringByDelimiter(resultNeg, testStringNeg, ' ');

    TEST_EQUAL(resultNeg.size(), 0);
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
    std::vector<std::string> result;
    splitStringByLength(result, testString, 5);

    // check result
    TEST_EQUAL(result.size(), 5);
    TEST_EQUAL(result[0], "this ");
    TEST_EQUAL(result[1], "is a ");
    TEST_EQUAL(result[2], "test-");
    TEST_EQUAL(result[3], "strin");
    TEST_EQUAL(result[4], "g");
}

/**
 * replaceSubstring_test
 */
void
StringMethods_Test::replaceSubstring_test()
{
    // init
    std::string testString = "this is a test-string";

    // run task
    replaceSubstring(testString, "test", "bogus");

    // check result
    TEST_EQUAL(testString, "this is a bogus-string");
}

/**
 * removeWhitespaces_test
 */
void
StringMethods_Test::removeWhitespaces_test()
{
    // init
    std::string testString = "this is a test-string";

    // run task
    removeWhitespaces(testString);

    // check result
    TEST_EQUAL(testString, "thisisatest-string");
}

} // namespace Kitsunemimi

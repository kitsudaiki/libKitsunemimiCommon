/**
 *  @file    string_methods_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "string_methods_test.h"

#include <common_methods/string_methods.h>

namespace Kitsune
{
namespace Common
{

StringMethods_Test::StringMethods_Test()
    : Kitsune::Common::Test("StringMethods_Test")
{
    splitString_test();
}

/**
 * splitString_test
 */
void
StringMethods_Test::splitString_test()
{
    // init
    std::string testString = "this is a test-string";

    // run task
    std::vector<std::string> result = splitString(testString, ' ');

    // check result
    UNITTEST(result.size(), 4);
    UNITTEST(result[0], "this");
    UNITTEST(result[1], "is");
    UNITTEST(result[2], "a");
    UNITTEST(result[3], "test-string");

    // make negative checks
    std::string testStringNeg = "";
    std::vector<std::string> resultNeg = splitString(testStringNeg, ' ');
    UNITTEST(resultNeg.size(), 0);
}

} // namespace Common
} // namespace Kitsune

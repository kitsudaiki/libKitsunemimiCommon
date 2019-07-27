/**
 *  @file    stringMethodsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "stringMethodsTest.hpp"

#include <commonMethods/stringMethods.hpp>

namespace Kitsune
{

StringMethodsTest::StringMethodsTest()
    : Kitsune::CommonTest("StringMethodsTest")
{
    testSplitString();
}

void StringMethodsTest::testSplitString()
{
    std::string testString = "this is a test-string";
    std::vector<std::string> result = splitString(testString, ' ');
    UNITTEST(result.size(), 4);
    UNITTEST(result[0], "this");
    UNITTEST(result[1], "is");
    UNITTEST(result[2], "a");
    UNITTEST(result[3], "test-string");

    std::string testStringNeg = "";
    std::vector<std::string> resultNeg = splitString(testStringNeg, ' ');
    UNITTEST(resultNeg.size(), 0);
}

} // namespace Kitsune

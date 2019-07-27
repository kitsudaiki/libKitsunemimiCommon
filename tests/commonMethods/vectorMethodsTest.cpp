/**
 *  @file    vectorMethodsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "vectorMethodsTest.hpp"

#include <commonMethods/vectorMethods.hpp>

namespace Kitsune
{

VectorMethodsTest::VectorMethodsTest()
    : Kitsune::CommonTest("VectorMethodsTest")
{
    testRemoveEmptyStrings();
}

void VectorMethodsTest::testRemoveEmptyStrings()
{
    std::vector<std::string> testVector{"x","","y","z",""};
    UNITTEST(removeEmptyStrings(&testVector), true);
    UNITTEST(testVector.size(), 3);
    UNITTEST(testVector[0], "x");
    UNITTEST(testVector[1], "y");
    UNITTEST(testVector[2], "z");

    std::vector<std::string> emptyVector;
    UNITTEST(removeEmptyStrings(&emptyVector), false);
    UNITTEST(removeEmptyStrings(nullptr), false);
}

} // namespace Kitsune

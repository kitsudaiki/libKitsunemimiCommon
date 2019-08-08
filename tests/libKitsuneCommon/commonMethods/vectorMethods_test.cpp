/**
 *  @file    vectorMethods_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "vectorMethods_test.hpp"

#include <commonMethods/vectorMethods.hpp>

namespace Kitsune
{
namespace Common
{

TextFile_Test::TextFile_Test()
    : Kitsune::Common::Test("VectorMethods_Test")
{
    removeEmptyStrings_test();
}

/**
 * removeEmptyStrings_test
 */
void
TextFile_Test::removeEmptyStrings_test()
{
    // init
    std::vector<std::string> testVector{"x","","y","z",""};

    // run task
    UNITTEST(removeEmptyStrings(&testVector), true);

    // check result
    UNITTEST(testVector.size(), 3);
    UNITTEST(testVector[0], "x");
    UNITTEST(testVector[1], "y");
    UNITTEST(testVector[2], "z");

    // make negative checks
    std::vector<std::string> emptyVector;
    UNITTEST(removeEmptyStrings(&emptyVector), false);
    UNITTEST(removeEmptyStrings(nullptr), false);
}

} // namespace Common
} // namespace Kitsune

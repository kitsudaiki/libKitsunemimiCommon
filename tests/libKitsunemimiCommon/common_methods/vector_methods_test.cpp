/**
 *  @file    vector_methods_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "vector_methods_test.h"

#include <libKitsunemimiCommon/common_methods/vector_methods.h>

namespace Kitsunemimi
{
namespace Common
{

TextFile_Test::TextFile_Test()
    : Kitsunemimi::Common::Test("VectorMethods_Test")
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
    TEST_EQUAL(removeEmptyStrings(&testVector), true);

    // check result
    TEST_EQUAL(testVector.size(), 3);
    TEST_EQUAL(testVector[0], "x");
    TEST_EQUAL(testVector[1], "y");
    TEST_EQUAL(testVector[2], "z");

    // make negative checks
    std::vector<std::string> emptyVector;
    TEST_EQUAL(removeEmptyStrings(&emptyVector), false);
    TEST_EQUAL(removeEmptyStrings(nullptr), false);
}

} // namespace Common
} // namespace Kitsunemimi

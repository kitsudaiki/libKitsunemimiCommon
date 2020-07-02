/**
 *  @file    object_methods_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "object_methods_test.h"

#include <libKitsunemimiCommon/common_methods/object_methods.h>

namespace Kitsunemimi
{

ObjectMethods_Test::ObjectMethods_Test()
    : Kitsunemimi::CompareTestHelper("ObjectMethods_Test")
{
    hexlify_test();
}

/**
 * hexlify_test
 */
void
ObjectMethods_Test::hexlify_test()
{
    struct testStruct {
        int a = 2343466;
        uint32_t b = 246;
        uint64_t x = 124;
    };

    // init
    testStruct testObject;
    std::string output = "";

    // run task
    hexlify(output, &testObject);

    // check result
    TEST_EQUAL(output, "000000000000007c000000f60023c22a");
}

} // namespace Kitsunemimi

/**
 *  @file    object_methods_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "object_methods_test.h"

#include <libKitsunemimiCommon/common_methods/object_methods.h>
#include <libKitsunemimiCommon/buffer/data_buffer.h>

namespace Kitsunemimi
{

ObjectMethods_Test::ObjectMethods_Test()
    : Kitsunemimi::CompareTestHelper("ObjectMethods_Test")
{
    //hexlify_test();

    encodeBase64_test();
    decodeBase64_test();
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

/**
 * encodeBase64_test
 */
void
ObjectMethods_Test::encodeBase64_test()
{
    std::string output = "";
    std::string input = "asdfasdfasdf123a";

    output = "";
    input = "asdfasdfasdf123a";
    encodeBase64(output, input.c_str(), input.size());
    TEST_EQUAL(output, "YXNkZmFzZGZhc2RmMTIzYQ==");

    output = "";
    input = "3256zu";
    encodeBase64(output, input.c_str(), input.size());
    TEST_EQUAL(output, "MzI1Nnp1");

    output = "";
    input = "5i";
    encodeBase64(output, input.c_str(), input.size());
    TEST_EQUAL(output, "NWk=");
}

/**
 * decodeBase64_test
 */
void
ObjectMethods_Test::decodeBase64_test()
{
    std::string decode = "";
    DataBuffer result;

    decodeBase64(result, "YXNkZmFzZGZhc2RmMTIzYQ==");
    decode = std::string(static_cast<char*>(result.data), result.bufferPosition);
    TEST_EQUAL(decode, "asdfasdfasdf123a");

    reset_DataBuffer(result, 1);

    decodeBase64(result, "MzI1Nnp1");
    decode = std::string(static_cast<char*>(result.data), result.bufferPosition);
    TEST_EQUAL(decode, "3256zu");

    reset_DataBuffer(result, 1);

    decodeBase64(result, "NWk=");
    decode = std::string(static_cast<char*>(result.data), result.bufferPosition);
    TEST_EQUAL(decode, "5i");
}

} // namespace Kitsunemimi

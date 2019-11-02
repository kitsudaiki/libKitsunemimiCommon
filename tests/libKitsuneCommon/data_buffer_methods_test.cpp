/**
 *  @file    data_buffer_methods_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_buffer_methods_test.h"

#include <libKitsuneCommon/data_buffer.h>
#include <libKitsuneCommon/data_buffer_methods.h>

namespace Kitsune
{
namespace Common
{

struct TestStruct
{
    uint8_t a = 0;
    uint8_t b = 0;
    uint64_t c = 0;
} __attribute__((packed));

DataBufferMethods_Test::DataBufferMethods_Test()
    : Kitsune::Common::Test("DataBufferMethods_Test")
{
    addDataToBuffer_test();
    allocateBlocks_test();
    resetBuffer_test();
}

/**
 * addDataToBuffer_test
 */
void
DataBufferMethods_Test::addDataToBuffer_test()
{
    // init
    DataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // check metadata of the buffer
    TEST_EQUAL(testBuffer.bufferPosition, 0);

    // add data to buffer
    void* testStructPtr = static_cast<void*>(&testStruct);
    TEST_EQUAL(addDataToBuffer(&testBuffer, testStructPtr, sizeof(TestStruct)), true);

    // check metadata of the buffer
    TEST_EQUAL(testBuffer.numberOfBlocks, 10);
    TEST_EQUAL(testBuffer.bufferPosition, 10);
    TEST_EQUAL(testBuffer.totalBufferSize, 10*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    TEST_EQUAL(static_cast<int>(dataByte[1]), 42);
}

/**
 * allocateBlocks_test
 */
void
DataBufferMethods_Test::allocateBlocks_test()
{
    // init
    DataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // write data to buffer
    TEST_EQUAL(testBuffer.addData(&testStruct), true);

    // check metadata of the buffer
    TEST_EQUAL(testBuffer.numberOfBlocks, 10);
    TEST_EQUAL(testBuffer.bufferPosition, 10);
    TEST_EQUAL(testBuffer.totalBufferSize, 10*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    TEST_EQUAL(static_cast<int>(dataByte[1]), 42);

    // resize
    TEST_EQUAL(allocateBlocks(&testBuffer, 1), true);

    // check metadata of the buffer
    TEST_EQUAL(testBuffer.numberOfBlocks, 11);
    TEST_EQUAL(testBuffer.bufferPosition, 10);
    TEST_EQUAL(testBuffer.totalBufferSize, 11*testBuffer.blockSize);

    // check content of the buffer
    dataByte = static_cast<uint8_t*>(testBuffer.data);
    TEST_EQUAL(static_cast<int>(dataByte[1]), 42);
}

/**
 * resetBuffer_test
 */
void
DataBufferMethods_Test::resetBuffer_test()
{
    // init
    DataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // write data to buffer
    TEST_EQUAL(testBuffer.addData(&testStruct), true);

    // reset buffer
    TEST_EQUAL(resetBuffer(&testBuffer, 2), true);

    // check metadata of the buffer
    TEST_EQUAL(testBuffer.numberOfBlocks, 2);
    TEST_EQUAL(testBuffer.bufferPosition, 0);
    TEST_EQUAL(testBuffer.totalBufferSize, 2*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    TEST_EQUAL(static_cast<int>(dataByte[1]), 0);
}

} // namespace Common
} // namespace Kitsune

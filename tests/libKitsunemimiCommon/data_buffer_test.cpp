/**
 *  @file    data_buffer_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_buffer_test.h"

#include <libKitsunemimiCommon/data_buffer.h>

namespace Kitsunemimi
{
namespace Common
{

struct TestStruct
{
    uint8_t a = 0;
    uint8_t b = 0;
    uint64_t c = 0;
} __attribute__((packed));

DataBuffer_Test::DataBuffer_Test()
    : Kitsunemimi::Common::Test("DataBuffer_Test")
{
    structSize_test();
    constructor_test();
    copyConstructor_test();
    addData_test();
    getBlock_test();
    reset_test();
}

/**
 * structSize_test
 */
void
DataBuffer_Test::structSize_test()
{
    DataBuffer testBuffer(10);
    TEST_EQUAL(sizeof(DataBuffer) % 8, 0);
}

/**
 * constructor_test
 */
void
DataBuffer_Test::constructor_test()
{
    DataBuffer testBuffer(10);

    // check metadata of the buffer
    bool isNullptr = testBuffer.data == nullptr;
    TEST_EQUAL(isNullptr, false);
    TEST_EQUAL(testBuffer.numberOfBlocks, 10);
    TEST_EQUAL(testBuffer.bufferPosition, 0);
    TEST_EQUAL(testBuffer.totalBufferSize, 10*testBuffer.blockSize);
}

/**
 * copyConstructor_test
 */
void
DataBuffer_Test::copyConstructor_test()
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

    // use copy contstructor
    DataBuffer bufferCopy(testBuffer);

    // check metadata of the new buffer
    TEST_EQUAL(bufferCopy.numberOfBlocks, 10);
    TEST_EQUAL(bufferCopy.bufferPosition, 10);
    TEST_EQUAL(bufferCopy.totalBufferSize, 10*bufferCopy.blockSize);

    // check content of the new buffer
    uint8_t* dataByte = static_cast<uint8_t*>(bufferCopy.data);
    TEST_EQUAL(static_cast<int>(dataByte[1]), 42);
}

/**
 * addData_test
 */
void
DataBuffer_Test::addData_test()
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
}

/**
 * getBlock_test
 */
void
DataBuffer_Test::getBlock_test()
{
    // init
    DataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    memcpy(&dataByte[4096], &testStruct, sizeof(TestStruct));

    // check content of the buffer with getBlock-method
    TEST_EQUAL(static_cast<int>(testBuffer.getBlock(1)[1]), 42);
}

/**
 * reset_test
 */
void
DataBuffer_Test::reset_test()
{
    // init
    DataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // write data to buffer
    TEST_EQUAL(testBuffer.addData(&testStruct), true);

    // reset buffer
    TEST_EQUAL(testBuffer.reset(), true);

    // check metadata of the buffer
    TEST_EQUAL(testBuffer.numberOfBlocks, 1);
    TEST_EQUAL(testBuffer.bufferPosition, 0);
    TEST_EQUAL(testBuffer.totalBufferSize, 1*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    TEST_EQUAL(static_cast<int>(dataByte[1]), 0);
}

} // namespace Common
} // namespace Kitsunemimi

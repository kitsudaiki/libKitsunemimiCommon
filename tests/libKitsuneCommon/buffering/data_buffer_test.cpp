/**
 *  @file    data_buffer_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_buffer_test.h"

#include <buffering/data_buffer.h>

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

DataBuffer_Test::DataBuffer_Test()
    : Kitsune::Common::Test("DataBuffer_Test")
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
    UNITTEST(sizeof(DataBuffer) % 8, 0);
}

/**
 * constructor_test
 */
void
DataBuffer_Test::constructor_test()
{
    DataBuffer testBuffer(10);

    // check metadata of the buffer
    UNITTEST_NEG(testBuffer.data, nullptr);
    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 0);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);
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
    UNITTEST(testBuffer.addData(&testStruct), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);

    // use copy contstructor
    DataBuffer bufferCopy(testBuffer);

    // check metadata of the new buffer
    UNITTEST(bufferCopy.numberOfBlocks, 10);
    UNITTEST(bufferCopy.bufferPosition, 10);
    UNITTEST(bufferCopy.totalBufferSize, 10*bufferCopy.blockSize);

    // check content of the new buffer
    uint8_t* dataByte = static_cast<uint8_t*>(bufferCopy.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
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
    UNITTEST(testBuffer.addData(&testStruct), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
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
    UNITTEST(static_cast<int>(testBuffer.getBlock(1)[1]), 42);
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
    UNITTEST(testBuffer.addData(&testStruct), true);

    // reset buffer
    UNITTEST(testBuffer.reset(), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 1);
    UNITTEST(testBuffer.bufferPosition, 0);
    UNITTEST(testBuffer.totalBufferSize, 1*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 0);
}

} // namespace Common
} // namespace Kitsune

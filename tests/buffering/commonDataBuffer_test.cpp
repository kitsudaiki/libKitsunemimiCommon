/**
 *  @file    commonDataBuffer_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "commonDataBuffer_test.hpp"

#include <buffering/commonDataBuffer.hpp>

namespace Kitsune
{

struct TestStruct
{
    uint8_t a = 0;
    uint8_t b = 0;
    uint64_t c = 0;
} __attribute__((packed));

CommonDataBuffer_Test::CommonDataBuffer_Test()
    : Kitsune::CommonTest("CommonDataBuffer_Test")
{
    structSize_test();
    constructor_test();
    copyConstructor_test();
    addData_test();
    getBlock_test();
    reset_test();
}


void CommonDataBuffer_Test::structSize_test()
{
    CommonDataBuffer testBuffer(10);
    UNITTEST(sizeof(CommonDataBuffer) % 8, 0);
}

void CommonDataBuffer_Test::constructor_test()
{
    CommonDataBuffer testBuffer(10);

    // check metadata of the buffer
    UNITTEST_NEG(testBuffer.data, nullptr);
    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 0);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);
}

void CommonDataBuffer_Test::copyConstructor_test()
{
    // init
    CommonDataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // write data to buffer
    UNITTEST(testBuffer.addData(&testStruct), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);

    // use copy contstructor
    CommonDataBuffer bufferCopy(testBuffer);

    // check metadata of the new buffer
    UNITTEST(bufferCopy.numberOfBlocks, 10);
    UNITTEST(bufferCopy.bufferPosition, 10);
    UNITTEST(bufferCopy.totalBufferSize, 10*bufferCopy.blockSize);

    // check content of the new buffer
    uint8_t* dataByte = static_cast<uint8_t*>(bufferCopy.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
}

void CommonDataBuffer_Test::addData_test()
{
    // init
    CommonDataBuffer testBuffer(10);
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

void CommonDataBuffer_Test::getBlock_test()
{
    // init
    CommonDataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    memcpy(&dataByte[4096], &testStruct, sizeof(TestStruct));

    // check content of the buffer with getBlock-method
    UNITTEST(static_cast<int>(testBuffer.getBlock(1)[1]), 42);
}

void CommonDataBuffer_Test::reset_test()
{
    // init
    CommonDataBuffer testBuffer(10);
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

} // namespace Kitsune

/**
 *  @file    commonDataBufferMethods_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "commonDataBufferMethods_test.hpp"

#include <buffering/commonDataBuffer.hpp>
#include <buffering/commonDataBufferMethods.hpp>

namespace Kitsune
{

struct TestStruct
{
    uint8_t a = 0;
    uint8_t b = 0;
    uint64_t c = 0;
} __attribute__((packed));

CommonDataBufferMethods_Test::CommonDataBufferMethods_Test()
    : Kitsune::CommonTest("CommonDataBufferMethods_Test")
{
    addDataToBuffer_test();
    allocateBlocks_test();
    resetBuffer_test();
}

void CommonDataBufferMethods_Test::addDataToBuffer_test()
{
    // init
    CommonDataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // check metadata of the buffer
    UNITTEST(testBuffer.bufferPosition, 0);

    // add data to buffer
    void* testStructPtr = static_cast<void*>(&testStruct);
    UNITTEST(addDataToBuffer(&testBuffer, testStructPtr, sizeof(TestStruct)), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
}

void CommonDataBufferMethods_Test::allocateBlocks_test()
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

    // resize
    UNITTEST(allocateBlocks(&testBuffer, 1), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 11);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 11*testBuffer.blockSize);

    // check content of the buffer
    dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
}

void CommonDataBufferMethods_Test::resetBuffer_test()
{
    // init
    CommonDataBuffer testBuffer(10);
    TestStruct testStruct;
    testStruct.b = 42;

    // write data to buffer
    UNITTEST(testBuffer.addData(&testStruct), true);

    // reset buffer
    UNITTEST(resetBuffer(&testBuffer, 2), true);

    // check metadata of the buffer
    UNITTEST(testBuffer.numberOfBlocks, 2);
    UNITTEST(testBuffer.bufferPosition, 0);
    UNITTEST(testBuffer.totalBufferSize, 2*testBuffer.blockSize);

    // check content of the buffer
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 0);
}

} // namespace Kitsune

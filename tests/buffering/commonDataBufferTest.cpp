/**
 *  @file    commonDataBufferTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "commonDataBufferTest.hpp"

#include <buffering/commonDataBuffer.hpp>

namespace Kitsune
{

struct TestStruct
{
    uint8_t a = 0;
    uint8_t b = 0;
    uint64_t c = 0;
} __attribute__((packed));

CommonDataBufferTest::CommonDataBufferTest() : Kitsune::CommonTest("CommonDataBufferTest")
{
    testConstructor();
    testCopyConstructor();
    testAddDataToBuffer();
    testAddData();
    testGetBlock();
    testAllocateBlocks();
    testResetBuffer();
}

void CommonDataBufferTest::testConstructor()
{
    CommonDataBuffer testBuffer(10);

    UNITTEST_NEG(testBuffer.data, nullptr);

    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);
    UNITTEST(testBuffer.numberOfBlocks, 10);
}

void CommonDataBufferTest::testCopyConstructor()
{
    // TODO
}

void CommonDataBufferTest::testAddDataToBuffer()
{
    CommonDataBuffer testBuffer(10);

    TestStruct testStruct;
    testStruct.b = 42;

    UNITTEST(testBuffer.bufferPosition, 0);

    UNITTEST(addDataToBuffer(&testBuffer, static_cast<void*>(&testStruct), sizeof(TestStruct)), true);

    UNITTEST(testBuffer.bufferPosition, 10);
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
}

void CommonDataBufferTest::testAddData()
{
    CommonDataBuffer testBuffer(10);

    TestStruct testStruct;
    testStruct.b = 42;

    UNITTEST(testBuffer.addData(&testStruct), true);

    UNITTEST(testBuffer.bufferPosition, 10);
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
}

void CommonDataBufferTest::testGetBlock()
{
    CommonDataBuffer testBuffer(10);

    TestStruct testStruct;
    testStruct.b = 42;

    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    memcpy(&dataByte[4096], &testStruct, sizeof(TestStruct));

    UNITTEST(static_cast<int>(testBuffer.getBlock(1)[1]), 42);
}

void CommonDataBufferTest::testAllocateBlocks()
{
    CommonDataBuffer testBuffer(10);

    TestStruct testStruct;
    testStruct.b = 42;

    UNITTEST(testBuffer.addData(&testStruct), true);

    UNITTEST(testBuffer.numberOfBlocks, 10);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 10*testBuffer.blockSize);
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);

    UNITTEST(allocateBlocks(&testBuffer, 1), true);

    UNITTEST(testBuffer.numberOfBlocks, 11);
    UNITTEST(testBuffer.bufferPosition, 10);
    UNITTEST(testBuffer.totalBufferSize, 11*testBuffer.blockSize);
    dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 42);
}

void CommonDataBufferTest::testResetBuffer()
{
    CommonDataBuffer testBuffer(10);

    TestStruct testStruct;
    testStruct.b = 42;

    UNITTEST(testBuffer.addData(&testStruct), true);

    resetBuffer(&testBuffer, 2);

    UNITTEST(testBuffer.numberOfBlocks, 2);
    UNITTEST(testBuffer.bufferPosition, 0);
    UNITTEST(testBuffer.totalBufferSize, 2*testBuffer.blockSize);
    uint8_t* dataByte = static_cast<uint8_t*>(testBuffer.data);
    UNITTEST(static_cast<int>(dataByte[1]), 0);
}

}

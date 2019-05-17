/**
 *  @file    commonDataBufferTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "commonDataBufferTest.h"

#include <buffering/commonDataBuffer.h>

namespace Kitsune
{

CommonDataBufferTest::CommonDataBufferTest() : Kitsune::CommonTest("CommonDataBufferTest")
{
    testConstructor();
    testCopyConstructor();
    testAddData();
    testAddDataToBuffer();
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

}

void CommonDataBufferTest::testAddData()
{
    CommonDataBuffer testBuffer;
}

void CommonDataBufferTest::testAddDataToBuffer()
{
    CommonDataBuffer testBuffer;
}

void CommonDataBufferTest::testGetBlock()
{
    CommonDataBuffer testBuffer;
}

void CommonDataBufferTest::testAllocateBlocks()
{
    CommonDataBuffer testBuffer;
}

void CommonDataBufferTest::testResetBuffer()
{
    CommonDataBuffer testBuffer;
}

}

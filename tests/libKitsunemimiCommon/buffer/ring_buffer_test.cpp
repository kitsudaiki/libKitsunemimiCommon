#include "ring_buffer_test.h"

#include <libKitsunemimiCommon/buffer/ring_buffer.h>

namespace Kitsunemimi
{

RingBuffer_Test::RingBuffer_Test()
    : Kitsunemimi::CompareTestHelper("RingBuffer_Test")
{
    addDataToBuffer_test();
    getWritePosition_test();
    getSpaceToEnd_test();
    getDataPointer_test();
    moveBufferForward_test();
    getObjectFromBuffer_test();
}

/**
 * @brief addDataToBuffer_test
 */
void
RingBuffer_Test::addDataToBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = nullptr;

    // negative test
    data = alignedMalloc(4096, ringBuffer.totalBufferSize+4096);
    TEST_EQUAL(addDataToBuffer(ringBuffer, data, ringBuffer.totalBufferSize+4096), false);
    alignedFree(data);

    // normal test
    data = alignedMalloc(4096, 4096);
    TEST_EQUAL(addDataToBuffer(ringBuffer, data, 4096), true);
    TEST_EQUAL(ringBuffer.readPosition, 0);
    TEST_EQUAL(ringBuffer.usedSize, 4096);
    alignedFree(data);

    // second negative test
    data = alignedMalloc(4096, ringBuffer.totalBufferSize);
    TEST_EQUAL(addDataToBuffer(ringBuffer, data, ringBuffer.totalBufferSize), false);
    TEST_EQUAL(ringBuffer.usedSize, 4096);
    alignedFree(data);
}

/**
 * @brief getWritePosition_test
 */
void
RingBuffer_Test::getWritePosition_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = nullptr;

    data = alignedMalloc(4096, 4096);
    TEST_EQUAL(getWritePosition(ringBuffer), 0);
    addDataToBuffer(ringBuffer, data, 4096);
    TEST_EQUAL(getWritePosition(ringBuffer), 4096);
    alignedFree(data);
}

/**
 * @brief getSpaceToEnd_test
 */
void
RingBuffer_Test::getSpaceToEnd_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = alignedMalloc(4096, 4096);

    // first test
    TEST_EQUAL(getSpaceToEnd(ringBuffer), ringBuffer.totalBufferSize);

    // second test
    addDataToBuffer(ringBuffer, data, 4096);
    TEST_EQUAL(getSpaceToEnd(ringBuffer), ringBuffer.totalBufferSize-4096);

    alignedFree(data);
}

/**
 * @brief getDataPointer_test
 */
void
RingBuffer_Test::getDataPointer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = alignedMalloc(4096, 4096);
    bool isNullptr = false;
    addDataToBuffer(ringBuffer, data, 4096);

    // negative test
    isNullptr = getDataPointer(ringBuffer, 5000) == nullptr;
    TEST_EQUAL(isNullptr, true);

    // normal test
    isNullptr = getDataPointer(ringBuffer, 1000) == nullptr;
    TEST_EQUAL(isNullptr, false);

    alignedFree(data);
}

/**
 * @brief moveBufferForward_test
 */
void
RingBuffer_Test::moveBufferForward_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = alignedMalloc(4096, 8192);
    addDataToBuffer(ringBuffer, data, 8192);

    // prepare tests
    TEST_EQUAL(ringBuffer.readPosition, 0);
    TEST_EQUAL(ringBuffer.usedSize, 8192);
    TEST_EQUAL(getWritePosition(ringBuffer), 8192);

    // run task
    moveBufferForward(ringBuffer, 4096);

    // check result
    TEST_EQUAL(ringBuffer.readPosition, 4096);
    TEST_EQUAL(ringBuffer.usedSize, 4096);
    TEST_EQUAL(getWritePosition(ringBuffer), 8192);

    alignedFree(data);
}

/**
 * @brief getObjectFromBuffer_test
 */
void
RingBuffer_Test::getObjectFromBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    uint64_t testValue = 1234567;

    // run task
    addDataToBuffer(ringBuffer, static_cast<void*>(&testValue), sizeof(testValue));

    // check result
    const uint64_t* returnVal = getObjectFromBuffer<uint64_t>(ringBuffer);
    TEST_EQUAL(*returnVal, testValue);
}

} // namespace Kitsunemimi

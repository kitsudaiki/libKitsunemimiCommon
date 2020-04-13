#include "ring_buffer_test.h"

#include <libKitsunemimiCommon/buffer/ring_buffer.h>

namespace Kitsunemimi
{

RingBuffer_Test::RingBuffer_Test()
    : Kitsunemimi::CompareTestHelper("RingBuffer_Test")
{
    addData_RingBuffer_test();
    addObject_RingBuffer_test();
    getWritePosition_RingBuffer_test();
    getSpaceToEnd_RingBuffer_test();
    getDataPointer_RingBuffer_test();
    moveForward_RingBuffer_test();
    getObject_RingBuffer_test();
}

/**
 * @brief addData_RingBuffer_test
 */
void
RingBuffer_Test::addData_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = nullptr;

    // negative test
    data = alignedMalloc(4096, ringBuffer.totalBufferSize+4096);
    TEST_EQUAL(addData_RingBuffer(ringBuffer, data, ringBuffer.totalBufferSize+4096), false);
    alignedFree(data);

    // normal test
    data = alignedMalloc(4096, 4096);
    TEST_EQUAL(addData_RingBuffer(ringBuffer, data, 4096), true);
    TEST_EQUAL(ringBuffer.readPosition, 0);
    TEST_EQUAL(ringBuffer.usedSize, 4096);
    alignedFree(data);

    // second negative test
    data = alignedMalloc(4096, ringBuffer.totalBufferSize);
    TEST_EQUAL(addData_RingBuffer(ringBuffer, data, ringBuffer.totalBufferSize), false);
    TEST_EQUAL(ringBuffer.usedSize, 4096);
    alignedFree(data);
}

/**
 * @brief addObject_RingBuffer_test
 */
void
RingBuffer_Test::addObject_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    uint64_t testValue = 42;

    // run test
    TEST_EQUAL(addObject_RingBuffer(ringBuffer, &testValue), true);
    TEST_EQUAL(ringBuffer.readPosition, 0);
    TEST_EQUAL(ringBuffer.usedSize, sizeof(testValue));
}

/**
 * @brief getWritePosition_RingBuffer_test
 */
void
RingBuffer_Test::getWritePosition_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = nullptr;

    data = alignedMalloc(4096, 4096);
    TEST_EQUAL(getWritePosition_RingBuffer(ringBuffer), 0);
    addData_RingBuffer(ringBuffer, data, 4096);
    TEST_EQUAL(getWritePosition_RingBuffer(ringBuffer), 4096);
    alignedFree(data);
}

/**
 * @brief getSpaceToEnd_RingBuffer_test
 */
void
RingBuffer_Test::getSpaceToEnd_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = alignedMalloc(4096, 4096);

    // first test
    TEST_EQUAL(getSpaceToEnd_RingBuffer(ringBuffer), ringBuffer.totalBufferSize);

    // second test
    addData_RingBuffer(ringBuffer, data, 4096);
    TEST_EQUAL(getSpaceToEnd_RingBuffer(ringBuffer), ringBuffer.totalBufferSize-4096);

    alignedFree(data);
}

/**
 * @brief getDataPointer_RingBuffer_test
 */
void
RingBuffer_Test::getDataPointer_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = alignedMalloc(4096, 4096);
    bool isNullptr = false;
    addData_RingBuffer(ringBuffer, data, 4096);

    // negative test
    isNullptr = getDataPointer_RingBuffer(ringBuffer, 5000) == nullptr;
    TEST_EQUAL(isNullptr, true);

    // normal test
    isNullptr = getDataPointer_RingBuffer(ringBuffer, 1000) == nullptr;
    TEST_EQUAL(isNullptr, false);

    alignedFree(data);
}

/**
 * @brief moveForward_RingBuffer_test
 */
void
RingBuffer_Test::moveForward_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    void* data = alignedMalloc(4096, 8192);
    addData_RingBuffer(ringBuffer, data, 8192);

    // prepare tests
    TEST_EQUAL(ringBuffer.readPosition, 0);
    TEST_EQUAL(ringBuffer.usedSize, 8192);
    TEST_EQUAL(getWritePosition_RingBuffer(ringBuffer), 8192);

    // run task
    moveForward_RingBuffer(ringBuffer, 4096);

    // check result
    TEST_EQUAL(ringBuffer.readPosition, 4096);
    TEST_EQUAL(ringBuffer.usedSize, 4096);
    TEST_EQUAL(getWritePosition_RingBuffer(ringBuffer), 8192);

    alignedFree(data);
}

/**
 * @brief getObject_RingBuffer_test
 */
void
RingBuffer_Test::getObject_RingBuffer_test()
{
    // init
    RingBuffer ringBuffer;
    uint64_t testValue = 1234567;

    // run task
    addData_RingBuffer(ringBuffer, static_cast<void*>(&testValue), sizeof(testValue));

    // check result
    const uint64_t* returnVal = getObject_RingBuffer<uint64_t>(ringBuffer);
    TEST_EQUAL(*returnVal, testValue);
}

} // namespace Kitsunemimi

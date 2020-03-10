#include "stack_buffer_test.h"
#include <libKitsunemimiCommon/buffer/stack_buffer.h>

namespace Kitsunemimi
{

StackBuffer_Test::StackBuffer_Test()
    : Kitsunemimi::CompareTestHelper("StackBuffer_Test")
{
    constructor_test();
    addNewToStack_test();
    writeDataIntoBuffer_test();
    addObjectToBuffer_test();
    getFirstElement_test();
    removeLastFromStack_test();
}

/**
 * @brief constructor_test
 */
void
StackBuffer_Test::constructor_test()
{
    // init
    bool isNullptr = false;

    // test if m_stackBufferReserve is correctly set
    isNullptr = Kitsunemimi::m_stackBufferReserve == nullptr;
    TEST_EQUAL(isNullptr, true);

    // test constructor
    StackBuffer stackBuffer(10, 20);
    TEST_EQUAL(stackBuffer.preOffset, 10);
    TEST_EQUAL(stackBuffer.postOffset, 20);
    TEST_EQUAL(stackBuffer.effectiveBlockSize, STACK_BUFFER_BLOCK_SIZE-30);
    TEST_EQUAL(stackBuffer.blockSize, STACK_BUFFER_BLOCK_SIZE);

    // test if m_stackBufferReserve is correctly set after first buffer-creation
    isNullptr = Kitsunemimi::m_stackBufferReserve == nullptr;
    TEST_EQUAL(isNullptr, false);
}

/**
 * @brief addNewToStack_test
 */
void
StackBuffer_Test::addNewToStack_test()
{
    // init
    StackBuffer stackBuffer;

    // run test
    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    addNewToStack(stackBuffer);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
}

/**
 * @brief writeDataIntoBuffer
 */
void
StackBuffer_Test::writeDataIntoBuffer_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);

    // negative test
    TEST_EQUAL(writeDataIntoBuffer(stackBuffer, buffer.data, buffer.totalBufferSize+10), false);
    TEST_EQUAL(stackBuffer.blocks.size(), 0);

    // run test
    TEST_EQUAL(writeDataIntoBuffer(stackBuffer, buffer.data, 1000), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    TEST_EQUAL(writeDataIntoBuffer(stackBuffer, buffer.data, 1000), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    TEST_EQUAL(writeDataIntoBuffer(stackBuffer, buffer.data, buffer.totalBufferSize), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 2);
}

/**
 * @brief addObjectToBuffer_test
 */
void
StackBuffer_Test::addObjectToBuffer_test()
{
    // init
    StackBuffer stackBuffer;
    uint64_t testValue = 42;

    // run test
    TEST_EQUAL(addObjectToBuffer(stackBuffer, &testValue), true);
    TEST_EQUAL(stackBuffer.blocks.at(0)->bufferPosition, sizeof(testValue));
}

/**
 * @brief getFirstElement_test
 */
void
StackBuffer_Test::getFirstElement_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);
    bool isNullptr = false;
    DataBuffer* result = nullptr;

    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    result = getFirstElement(stackBuffer);
    isNullptr = result == nullptr;
    TEST_EQUAL(isNullptr, true);
    TEST_EQUAL(stackBuffer.blocks.size(), 0);

    // prepare test-buffer
    uint64_t testValue = 42;
    addObjectToBuffer(buffer, &testValue);
    writeDataIntoBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);

    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    result = getFirstElement(stackBuffer);
    isNullptr = result == nullptr;
    TEST_EQUAL(isNullptr, false);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);

    uint64_t ret = *static_cast<uint64_t*>(result->data);
    TEST_EQUAL(ret, testValue);
}

/**
 * @brief removeLastFromStack_test
 */
void
StackBuffer_Test::removeLastFromStack_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);

    // prepare test-buffer
    writeDataIntoBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);
    writeDataIntoBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);

    // run test
    TEST_EQUAL(stackBuffer.blocks.size(), 2);
    TEST_EQUAL(removeLastFromStack(stackBuffer), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    TEST_EQUAL(removeLastFromStack(stackBuffer), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    TEST_EQUAL(removeLastFromStack(stackBuffer), false);
}

} // namespace Kitsunemimi

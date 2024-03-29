/**
 *  @file    item_buffer_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "item_buffer_test.h"

#include <libKitsunemimiCommon/buffer/item_buffer.h>

namespace Kitsunemimi
{

struct TestStruct
{
    uint8_t itemStatus = ItemBuffer::ACTIVE_SECTION;
    uint8_t a = 0;
    uint8_t b = 0;
    uint64_t c = 0;
} __attribute__((packed));

ItemBuffer_Test::ItemBuffer_Test()
    : Kitsunemimi::CompareTestHelper("ItemBuffer_Test")
{
    initBuffer_test();
    deleteItem_test();
    deleteAll_test();
    addNewItem_test();
    backup_restore_test();
}

/**
 * initBuffer_test
 */
void
ItemBuffer_Test::initBuffer_test()
{
    ItemBuffer testBuffer;

    // init buffer
    TEST_EQUAL(testBuffer.initBuffer<TestStruct>(42000, 10000), true);
    TEST_EQUAL(testBuffer.metaData->itemSize, sizeof(TestStruct));
    TEST_EQUAL(testBuffer.metaData->itemCapacity, 42000);
    TEST_EQUAL(testBuffer.metaData->numberOfItems, 42000);

    // test override of an already initialized buffer
    TEST_EQUAL(testBuffer.initBuffer<TestStruct>(43000, 10000), true);
    TEST_EQUAL(testBuffer.metaData->itemSize, sizeof(TestStruct));
    TEST_EQUAL(testBuffer.metaData->itemCapacity, 43000);
    TEST_EQUAL(testBuffer.metaData->numberOfItems, 43000);
}

/**
 * deleteItem_test
 */
void
ItemBuffer_Test::deleteItem_test()
{
    // prepare item-buffer
    ItemBuffer testBuffer;

    // check failing delete in not initialized buffer
    TEST_EQUAL(testBuffer.deleteItem(42), false);

    // init test-buffer
    testBuffer.initBuffer<TestStruct>(42000, 10000);

    // delete items from test-buffer
    TEST_EQUAL(testBuffer.deleteItem(42), true);
    TEST_EQUAL(testBuffer.deleteItem(43), true);
    TEST_EQUAL(testBuffer.deleteItem(44), true);
    TEST_EQUAL(testBuffer.metaData->numberOfItems, 41997);
    TEST_EQUAL(testBuffer.deleteItem(42), false);
}

/**
 * deleteAll_test
 */
void
ItemBuffer_Test::deleteAll_test()
{
    // prepare item-buffer
    ItemBuffer testBuffer;
    testBuffer.initBuffer<TestStruct>(42000, 10000);

    // delete all items and check buffer-values
    testBuffer.deleteAll();
    TEST_EQUAL(testBuffer.metaData->numberOfItems, 0);
    TEST_EQUAL(testBuffer.metaData->itemSize, sizeof(TestStruct));
    TEST_EQUAL(testBuffer.metaData->itemCapacity, 42000);
}

/**
 * addNewItem_test
 */
void
ItemBuffer_Test::addNewItem_test()
{
    // prepare item-buffer
    ItemBuffer testBuffer;
    testBuffer.initBuffer<TestStruct>(42000, 10000);
    testBuffer.deleteItem(42);
    testBuffer.deleteItem(43);
    testBuffer.deleteItem(44);

    // prepare test-struct
    TestStruct testStruct;
    testStruct.a = 42;
    testStruct.b = 42;
    testStruct.c = 1337;

    // add items and check buffer-values
    TEST_EQUAL(testBuffer.addNewItem(testStruct), 42);
    TEST_EQUAL(testBuffer.metaData->numberOfItems, 41998);
    TEST_EQUAL(testBuffer.metaData->itemSize, sizeof(TestStruct));
    TEST_EQUAL(testBuffer.metaData->itemCapacity, 42000);
    TEST_EQUAL(testBuffer.addNewItem(testStruct), 43);
    TEST_EQUAL(testBuffer.addNewItem(testStruct), 44);
    TEST_EQUAL(testBuffer.addNewItem(testStruct), 0xFFFFFFFFFFFFFFFF);

    // check if delete and reuse still works, after the complete buffer was filled
    TEST_EQUAL(testBuffer.deleteItem(42), true);
    TEST_EQUAL(testBuffer.addNewItem(testStruct), 42);

    // check content of the added items
    TestStruct* structs = getItemData<TestStruct>(testBuffer);
    TEST_EQUAL(structs[42].c, 1337);
    TEST_EQUAL(structs[43].c, 1337);
    TEST_EQUAL(structs[44].c, 1337);
}

/**
 * @brief backup_restore_test
 */
void
ItemBuffer_Test::backup_restore_test()
{
    // prepare item-buffer
    ItemBuffer testBufferBase;
    testBufferBase.initBuffer<TestStruct>(42000, 10000);
    testBufferBase.deleteItem(42);
    testBufferBase.deleteItem(43);
    testBufferBase.deleteItem(44);

    // prepare test-struct
    TestStruct testStruct;
    testStruct.a = 42;
    testStruct.b = 42;
    testStruct.c = 1337;

    // add items and check buffer-values
    testBufferBase.addNewItem(testStruct);
    testBufferBase.addNewItem(testStruct);
    testStruct.c = 1111;
    testBufferBase.addNewItem(testStruct);

    ItemBuffer restoredBuffer;
    TEST_EQUAL(restoredBuffer.initBuffer(testBufferBase.buffer.data,
                                         testBufferBase.buffer.usedBufferSize), true);

    // test metadata of restored buffer
    TEST_EQUAL(testBufferBase.metaData->itemSize, restoredBuffer.metaData->itemSize);
    TEST_EQUAL(testBufferBase.metaData->itemCapacity, restoredBuffer.metaData->itemCapacity);
    TEST_EQUAL(testBufferBase.metaData->staticSize, restoredBuffer.metaData->staticSize);
    TEST_EQUAL(testBufferBase.metaData->numberOfItems, restoredBuffer.metaData->numberOfItems);
    TEST_EQUAL(testBufferBase.metaData->bytePositionOfFirstEmptyBlock,
               restoredBuffer.metaData->bytePositionOfFirstEmptyBlock);
    TEST_EQUAL(testBufferBase.metaData->bytePositionOfLastEmptyBlock,
               restoredBuffer.metaData->bytePositionOfLastEmptyBlock);

    // check content of restored buffer
    TestStruct* structs = getItemData<TestStruct>(restoredBuffer);
    TEST_EQUAL(structs[42].c, 1337);
    TEST_EQUAL(structs[43].c, 1337);
    TEST_EQUAL(structs[44].c, 1111);
}

}

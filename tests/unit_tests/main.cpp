/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <iostream>

#include <libKitsunemimiCommon/buffer/data_buffer_test.h>
#include <libKitsunemimiCommon/buffer/ring_buffer_test.h>
#include <libKitsunemimiCommon/buffer/stack_buffer_reserve_test.h>
#include <libKitsunemimiCommon/buffer/stack_buffer_test.h>

#include <libKitsunemimiCommon/common_methods/string_methods_test.h>
#include <libKitsunemimiCommon/common_methods/vector_methods_test.h>
#include <libKitsunemimiCommon/common_methods/object_methods_test.h>

#include <libKitsunemimiCommon/state_test.h>
#include <libKitsunemimiCommon/statemachine_test.h>

#include <libKitsunemimiCommon/common_items/data_items_DataArray_test.h>
#include <libKitsunemimiCommon/common_items/data_items_DataMap_test.h>
#include <libKitsunemimiCommon/common_items/data_items_DataValue_test.h>
#include <libKitsunemimiCommon/common_items/table_item_test.h>

int main()
{
    Kitsunemimi::DataBuffer_Test();
    Kitsunemimi::RingBuffer_Test();
    Kitsunemimi::StackBufferReserve_Test();
    Kitsunemimi::StackBuffer_Test();

    Kitsunemimi::StringMethods_Test();
    Kitsunemimi::VectorMethods_Test();
    Kitsunemimi::ObjectMethods_Test();

    Kitsunemimi::State_Test();
    Kitsunemimi::Statemachine_Test();

    Kitsunemimi::DataItems_DataValue_Test();
    Kitsunemimi::DataItems_DataArray_Test();
    Kitsunemimi::DataItems_DataMap_Test();

    Kitsunemimi::TableItem_test();
}

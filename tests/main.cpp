/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <iostream>

#include <libKitsunemimiCommon/data_buffer_test.h>
#include <libKitsunemimiCommon/data_buffer_methods_test.h>

#include <libKitsunemimiCommon/common_methods/string_methods_test.h>
#include <libKitsunemimiCommon/common_methods/vector_methods_test.h>

#include <libKitsunemimiCommon/state_test.h>
#include <libKitsunemimiCommon/statemachine_test.h>

#include <libKitsunemimiCommon/common_items/data_items_DataArray_test.h>
#include <libKitsunemimiCommon/common_items/data_items_DataMap_test.h>
#include <libKitsunemimiCommon/common_items/data_items_DataValue_test.h>
#include <libKitsunemimiCommon/common_items/table_item_test.h>

int main()
{
    Kitsunemimi::Common::DataBufferMethods_Test();
    Kitsunemimi::Common::DataBuffer_Test();

    Kitsunemimi::Common::StringMethods_Test();
    Kitsunemimi::Common::TextFile_Test();

    Kitsunemimi::Common::State_Test();
    Kitsunemimi::Common::Statemachine_Test();

    Kitsunemimi::Common::DataItems_DataValue_Test();
    Kitsunemimi::Common::DataItems_DataArray_Test();
    Kitsunemimi::Common::DataItems_DataMap_Test();

    Kitsunemimi::Common::TableItem_test();
}

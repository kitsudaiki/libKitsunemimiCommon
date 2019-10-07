/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <iostream>

#include <libKitsuneCommon/data_buffer_test.h>
#include <libKitsuneCommon/data_buffer_methods_test.h>

#include <libKitsuneCommon/common_methods/string_methods_test.h>
#include <libKitsuneCommon/common_methods/vector_methods_test.h>

#include <libKitsuneCommon/state_test.h>
#include <libKitsuneCommon/statemachine_test.h>

#include <libKitsuneCommon/common_items/data_items_DataArray_test.h>
#include <libKitsuneCommon/common_items/data_items_DataMap_test.h>
#include <libKitsuneCommon/common_items/data_items_DataValue_test.h>
#include <libKitsuneCommon/common_items/table_item_test.h>

int main()
{
    Kitsune::Common::DataBufferMethods_Test();
    Kitsune::Common::DataBuffer_Test();

    Kitsune::Common::StringMethods_Test();
    Kitsune::Common::TextFile_Test();

    Kitsune::Common::State_Test();
    Kitsune::Common::Statemachine_Test();

    Kitsune::Common::DataItems_DataValue_Test();
    Kitsune::Common::DataItems_DataArray_Test();
    Kitsune::Common::DataItems_DataMap_Test();

    Kitsune::Common::TableItem_test();
}

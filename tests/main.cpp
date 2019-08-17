/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>

#include <libKitsuneCommon/buffering/data_buffer_test.h>
#include <libKitsuneCommon/buffering/data_buffer_methods_test.h>

#include <libKitsuneCommon/commonMethods/string_methods_test.h>
#include <libKitsuneCommon/commonMethods/vector_methods_test.h>

#include <libKitsuneCommon/statemachine/state_test.h>
#include <libKitsuneCommon/statemachine/statemachine_test.h>

#include <libKitsuneCommon/data_structure/data_items_DataArray_test.h>
#include <libKitsuneCommon/data_structure/data_items_DataObject_test.h>
#include <libKitsuneCommon/data_structure/data_items_DataValue_test.h>

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
    Kitsune::Common::DataItems_DataObject_Test();
}

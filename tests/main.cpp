/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>

#include <libKitsuneCommon/buffering/dataBuffer_test.hpp>
#include <libKitsuneCommon/buffering/dataBufferMethods_test.hpp>

#include <libKitsuneCommon/commonMethods/stringMethods_test.hpp>
#include <libKitsuneCommon/commonMethods/vectorMethods_test.hpp>

#include <libKitsuneCommon/statemachine/state_test.hpp>
#include <libKitsuneCommon/statemachine/statemachine_test.hpp>

#include <libKitsuneCommon/data_structure/dataItems_dataArray_test.hpp>
#include <libKitsuneCommon/data_structure/dataItems_dataObject_test.hpp>
#include <libKitsuneCommon/data_structure/dataItems_dataValue_test.hpp>

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

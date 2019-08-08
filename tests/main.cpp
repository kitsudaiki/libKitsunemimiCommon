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

int main()
{
    Kitsune::Common::DataBufferMethods_Test();
    Kitsune::Common::DataBuffer_Test();

    Kitsune::Common::StringMethods_Test();
    Kitsune::Common::TextFile_Test();
}

/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>

#include <libKitsuneCommon/buffering/commonDataBuffer_test.hpp>
#include <libKitsuneCommon/buffering/commonDataBufferMethods_test.hpp>

#include <libKitsuneCommon/commonMethods/stringMethods_test.hpp>
#include <libKitsuneCommon/commonMethods/vectorMethods_test.hpp>

int main()
{
    Kitsune::CommonDataBufferMethods_Test();
    Kitsune::CommonDataBuffer_Test();

    Kitsune::StringMethods_Test();
    Kitsune::TextFile_Test();
}

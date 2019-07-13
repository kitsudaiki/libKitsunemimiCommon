/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>

#include <buffering/commonDataBufferTest.h>
#include <commonMethods/stringMethodsTest.h>
#include <commonMethods/vectorMethodsTest.h>

int main()
{
    Kitsune::CommonDataBufferTest();
    Kitsune::StringMethodsTest();
    Kitsune::VectorMethodsTest();
}

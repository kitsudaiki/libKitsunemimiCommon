/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>

#include <buffering/commonDataBufferTest.hpp>
#include <commonMethods/stringMethodsTest.hpp>
#include <commonMethods/vectorMethodsTest.hpp>

int main()
{
    Kitsune::CommonDataBufferTest();
    Kitsune::StringMethodsTest();
    Kitsune::VectorMethodsTest();
}

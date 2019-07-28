/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>

#include <buffering/commonDataBuffer_test.hpp>
#include <buffering/commonDataBufferMethods_test.hpp>

#include <commonMethods/stringMethods_test.hpp>
#include <commonMethods/vectorMethods_test.hpp>

int main()
{
    Kitsune::CommonDataBufferMethods_Test();
    Kitsune::CommonDataBuffer_Test();

    Kitsune::StringMethods_Test();
    Kitsune::VectorMethods_Test();
}

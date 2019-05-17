/**
 *  @file    commonDataBufferTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONDATABUFFERTEST_H
#define COMMONDATABUFFERTEST_H

#include <testing/commonTest.h>

namespace Kitsune
{

class CommonDataBufferTest : public Kitsune::CommonTest
{
public:
    CommonDataBufferTest();

private:
    void initTestCase();
    void parserPositiveTest();
    void parserNegativeTest();
    void cleanupTestCase();
};

}

#endif // COMMONDATABUFFERTEST_H

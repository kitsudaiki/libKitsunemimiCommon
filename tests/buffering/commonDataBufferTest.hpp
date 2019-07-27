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

#include <testing/commonTest.hpp>

namespace Kitsune
{

class CommonDataBufferTest : public Kitsune::CommonTest
{
public:
    CommonDataBufferTest();

private:
    void testConstructor();
    void testCopyConstructor();
    void testAddData();
    void testAddDataToBuffer();
    void testGetBlock();
    void testAllocateBlocks();
    void testResetBuffer();
};

}

#endif // COMMONDATABUFFERTEST_H

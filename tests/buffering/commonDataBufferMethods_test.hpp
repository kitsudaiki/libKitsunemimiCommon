/**
 *  @file    commonDataBufferMethods_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONDATABUFFERMETHODS_TEST_HPP
#define COMMONDATABUFFERMETHODS_TEST_HPP

#include <testing/commonTest.hpp>

namespace Kitsune
{

class CommonDataBufferMethods_Test
        : public Kitsune::CommonTest
{
public:
    CommonDataBufferMethods_Test();

private:
    void testConstructor();
    void testStructSize();
    void testCopyConstructor();
    void testAddData();
    void testAddDataToBuffer();
    void testGetBlock();
    void testAllocateBlocks();
    void testResetBuffer();
};

} // namespace Kitsune

#endif // COMMONDATABUFFERMETHODS_TEST_HPP

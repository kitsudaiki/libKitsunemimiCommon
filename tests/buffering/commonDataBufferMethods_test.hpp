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
    void addDataToBuffer_test();
    void allocateBlocks_test();
    void resetBuffer_test();
};

} // namespace Kitsune

#endif // COMMONDATABUFFERMETHODS_TEST_HPP

/**
 *  @file    commonDataBuffer_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONDATABUFFERTEST_HPP
#define COMMONDATABUFFERTEST_HPP

#include <testing/commonTest.hpp>

namespace Kitsune
{

class CommonDataBuffer_Test
        : public Kitsune::CommonTest
{
public:
    CommonDataBuffer_Test();

private:
    void constructor_test();
    void structSize_test();
    void copyConstructor_test();
    void addData_test();
    void getBlock_test();
    void reset_test();
};

} // namespace Kitsune

#endif // COMMONDATABUFFERTEST_HPP

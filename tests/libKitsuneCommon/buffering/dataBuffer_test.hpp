/**
 *  @file    dataBuffer_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATABUFFER_TEST_HPP
#define DATABUFFER_TEST_HPP

#include <testing/test.hpp>

namespace Kitsune
{
namespace Common
{

class DataBuffer_Test
        : public Kitsune::Common::Test
{
public:
    DataBuffer_Test();

private:
    void constructor_test();
    void structSize_test();
    void copyConstructor_test();
    void addData_test();
    void getBlock_test();
    void reset_test();
};

} // namespace Common
} // namespace Kitsune

#endif // DATABUFFER_TEST_HPP

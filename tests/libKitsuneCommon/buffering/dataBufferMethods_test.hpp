/**
 *  @file    dataBufferMethods_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATABUFFERMETHODS_TEST_HPP
#define DATABUFFERMETHODS_TEST_HPP

#include <testing/test.hpp>

namespace Kitsune
{
namespace Common
{

class DataBufferMethods_Test
        : public Kitsune::Common::Test
{
public:
    DataBufferMethods_Test();

private:
    void addDataToBuffer_test();
    void allocateBlocks_test();
    void resetBuffer_test();
};

} // namespace Common
} // namespace Kitsune

#endif // DATABUFFERMETHODS_TEST_HPP

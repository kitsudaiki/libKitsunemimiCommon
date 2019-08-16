/**
 *  @file    dataBufferMethods_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATA_BUFFER_METHODS_TEST_H
#define DATA_BUFFER_METHODS_TEST_H

#include <testing/test.h>

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

#endif // DATABUFFERMETHODS_TEST_H

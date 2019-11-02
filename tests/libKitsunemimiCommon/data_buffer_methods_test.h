/**
 *  @file    data_buffer_methods_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATA_BUFFER_METHODS_TEST_H
#define DATA_BUFFER_METHODS_TEST_H

#include <libKitsunemimiCommon/test.h>

namespace Kitsunemimi
{
namespace Common
{

class DataBufferMethods_Test
        : public Kitsunemimi::Common::Test
{
public:
    DataBufferMethods_Test();

private:
    void addDataToBuffer_test();
    void allocateBlocks_test();
    void resetBuffer_test();
};

} // namespace Common
} // namespace Kitsunemimi

#endif // DATABUFFERMETHODS_TEST_H

/**
 *  @file    data_buffer_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATA_BUFFER_TEST_H
#define DATA_BUFFER_TEST_H

#include <libKitsunemimiCommon/test.h>

namespace Kitsunemimi
{
namespace Common
{

class DataBuffer_Test
        : public Kitsunemimi::Common::Test
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
} // namespace Kitsunemimi

#endif // DATABUFFER_TEST_H

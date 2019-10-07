/**
 *  @file    data_buffer_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATA_BUFFER_TEST_H
#define DATA_BUFFER_TEST_H

#include <libKitsuneCommon/unit_test.h>

namespace Kitsune
{
namespace Common
{

class DataBuffer_Test
        : public Kitsune::Common::UnitTest
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

#endif // DATABUFFER_TEST_H

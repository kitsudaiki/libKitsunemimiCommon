/**
 *  @file    dataItems_DataValue_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATAITEMS_DATAVALUE_TEST_HPP
#define DATAITEMS_DATAVALUE_TEST_HPP

#include <testing/test.hpp>

namespace Kitsune
{
namespace Common
{
class DataValue;

class DataItems_DataValue_Test : public Kitsune::Common::Test
{
public:
    DataItems_DataValue_Test();

private:
    void operator_test();
    void get_test();
    void getSize_test();
    void remove_test();
    void copy_test();
    void print_test();
    void getType_test();
    void isValue_isObject_isArray_test();
    void toValue_toObject_toArray_test();
    void toString_toInt_toFloat_test();

    void getValueType_test();
    void setValue_test();
};

}  // namespace Common
}  // namespace Kitsune

#endif // DATAITEMS_DATAVALUE_TEST_HPP

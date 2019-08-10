/**
 *  @file    dataItems_DataArray_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "dataItems_dataArray_test.hpp"
#include <data_structure/dataItems.hpp>

namespace Kitsune
{
namespace Common
{

DataItems_DataArray_Test::DataItems_DataArray_Test()
    : Kitsune::Common::Test("DataItems_DataArray_Test")
{
    operator_test();
    get_test();
    getSize_test();
    remove_test();
    copy_test();
    print_test();
    getType_test();
    isValue_isObject_isArray_test();
    toValue_toObject_toArray_test();
    toString_toInt_toFloat_test();

    // array-exclusive
    append_test();
}

/**
 * append_test
 */
void
DataItems_DataArray_Test::append_test()
{
    DataArray array;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    UNITTEST(array.append(defaultValue.copy()), true);
    UNITTEST(array.append(stringValue.copy()), true);
    UNITTEST(array.append(intValue.copy()), true);
    UNITTEST(array.append(floatValue.copy()), true);

    UNITTEST(array.append(nullptr), false);
}

/**
 * operator_test
 */
void
DataItems_DataArray_Test::operator_test()
{
    DataArray array = initTestArray();

    UNITTEST(array[1]->toString(), "test");

    // negative tests
    bool isNullptr = array[10] == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = array["2"] == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * get_test
 */
void
DataItems_DataArray_Test::get_test()
{
    DataArray array = initTestArray();

    UNITTEST(array.get(1)->toString(), "test");

    // negative tests
    bool isNullptr = array.get(10) == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = array.get("2") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataArray_Test::getSize_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.getSize(), 4);
}

/**
 * remove_test
 */
void
DataItems_DataArray_Test::remove_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.remove(1), true);
    UNITTEST(array.remove("2"), true);

    UNITTEST(array.get(1)->toInt(), 42);
    UNITTEST(array.getSize(), 2);

    // negative tests
    UNITTEST(array.remove(10), false);
}

/**
 * copy_test
 */
void
DataItems_DataArray_Test::copy_test()
{
    DataArray array = initTestArray();

    DataArray* arrayCopy = dynamic_cast<DataArray*>(array.copy());

    bool isNullptr = arrayCopy == nullptr;
    UNITTEST(isNullptr, false);

    UNITTEST(array.print(), arrayCopy->print());

    delete arrayCopy;
}

/**
 * print_test
 */
void
DataItems_DataArray_Test::print_test()
{
    DataArray array = initTestArray();

    std::string compare = "[\"\",\"test\",42,42.500000]";
    UNITTEST(array.print(), compare);

    compare = "[\n"
              "    \"\",\n"
              "    \"test\",\n"
              "    42,\n"
              "    42.500000\n"
              "]";
    UNITTEST(array.print(nullptr, true), compare);
}

/**
 * getType_test
 */
void
DataItems_DataArray_Test::getType_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.getType(), DataItem::ARRAY_TYPE);
}

/**
 * isValue_isObject_isArray_test
 */
void
DataItems_DataArray_Test::isValue_isObject_isArray_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.isValue(), false);
    UNITTEST(array.isObject(), false);
    UNITTEST(array.isArray(), true);
}

/**
 * toValue_toObject_toArray_test
 */
void
DataItems_DataArray_Test::toValue_toObject_toArray_test()
{
    DataArray array = initTestArray();

    bool isNullptr = array.toObject() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = array.toArray() == nullptr;
    UNITTEST(isNullptr, false);

    isNullptr = array.toValue() == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * toString_toInt_toFloat_test
 */
void
DataItems_DataArray_Test::toString_toInt_toFloat_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.toString(), "");
    UNITTEST(array.toInt(), 0);
    UNITTEST(array.toFloat(), 0.0f);
}

/**
 * create test data-array
 *
 * @return data-array for tests
 */
DataArray
DataItems_DataArray_Test::initTestArray()
{
    DataArray array;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    array.append(defaultValue.copy());
    array.append(stringValue.copy());
    array.append(intValue.copy());
    array.append(floatValue.copy());

    return array;
}

}  // namespace Common
}  // namespace Kitsune

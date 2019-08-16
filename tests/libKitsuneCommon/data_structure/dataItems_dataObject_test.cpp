/**
 *  @file    dataItems_DataObject_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "dataItems_dataObject_test.h"
#include <data_structure/data_items.h>

namespace Kitsune
{
namespace Common
{

DataItems_DataObject_Test::DataItems_DataObject_Test()
    : Kitsune::Common::Test("DataItems_DataObject_Test")
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

    // object-exclusive
    insert_test();
    getString_getInt_getFloat_test();
    getKeys_test();
    getValues_test();
    contains_test();
}

/**
 * operator_test
 */
void
DataItems_DataObject_Test::operator_test()
{
    DataObject object = initTestObject();

    UNITTEST(object[0]->toString(), "test");
    UNITTEST(object["hmm"]->toInt(), 42);

    // negative tests
    bool isNullptr = object[10] == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = object["k"] == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * get_test
 */
void
DataItems_DataObject_Test::get_test()
{
    DataObject object = initTestObject();

    UNITTEST(object.get(0)->toString(), "test");
    UNITTEST(object.get("hmm")->toInt(), 42);

    // negative tests
    bool isNullptr = object.get(10) == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = object.get("k") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataObject_Test::getSize_test()
{
    DataObject object = initTestObject();
    UNITTEST(object.getSize(), 4);
}

/**
 * remove_test
 */
void
DataItems_DataObject_Test::remove_test()
{
    DataObject object = initTestObject();
    UNITTEST(object.remove(0), true);
    UNITTEST(object.remove("hmm"), true);

    UNITTEST(object.get(1)->toString(), "42.500000");
    UNITTEST(object.getSize(), 2);

    // negative tests
    UNITTEST(object.remove(10), false);
}

/**
 * copy_test
 */
void
DataItems_DataObject_Test::copy_test()
{
    DataObject object = initTestObject();

    DataObject* objectCopy = dynamic_cast<DataObject*>(object.copy());

    bool isNullptr = objectCopy == nullptr;
    UNITTEST(isNullptr, false);

    UNITTEST(object.print(), objectCopy->print());

    delete objectCopy;
}

/**
 * print_test
 */
void
DataItems_DataObject_Test::print_test()
{
    DataObject object = initTestObject();

    std::string compare = "{\"asdf\":\"test\",\"hmm\":42,\"poi\":\"\",\"xyz\":42.500000}";
    UNITTEST(object.print(), compare);

    compare = "{\n"
              "    \"asdf\": \"test\",\n"
              "    \"hmm\": 42,\n"
              "    \"poi\": \"\",\n"
              "    \"xyz\": 42.500000\n"
              "}";
    UNITTEST(object.print(nullptr, true), compare);
}

/**
 * getType_test
 */
void
DataItems_DataObject_Test::getType_test()
{
    DataObject object = initTestObject();
    UNITTEST(object.getType(), DataItem::OBJECT_TYPE);
}

/**
 * isValue_isObject_isArray_test
 */
void
DataItems_DataObject_Test::isValue_isObject_isArray_test()
{
    DataObject object = initTestObject();
    UNITTEST(object.isValue(), false);
    UNITTEST(object.isObject(), true);
    UNITTEST(object.isArray(), false);
}

/**
 * toValue_toObject_toArray_test
 */
void
DataItems_DataObject_Test::toValue_toObject_toArray_test()
{
    DataObject object = initTestObject();

    bool isNullptr = object.toObject() == nullptr;
    UNITTEST(isNullptr, false);

    isNullptr = object.toArray() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = object.toValue() == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * toString_toInt_toFloat_test
 */
void
DataItems_DataObject_Test::toString_toInt_toFloat_test()
{
    DataObject object = initTestObject();
    UNITTEST(object.toString(), "");
    UNITTEST(object.toInt(), 0);
    UNITTEST(object.toFloat(), 0.0f);
}

/**
 * insert_test
 */
void
DataItems_DataObject_Test::insert_test()
{
    DataObject object;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    UNITTEST(object.insert("poi", defaultValue.copy()), true);
    UNITTEST(object.insert("asdf", stringValue.copy()), true);
    UNITTEST(object.insert("hmm", intValue.copy()), true);
    UNITTEST(object.insert("xyz", floatValue.copy()), true);
}

/**
 * getString_getInt_getFloat_test
 */
void
DataItems_DataObject_Test::getString_getInt_getFloat_test()
{
    DataObject object = initTestObject();

    UNITTEST(object.getString("asdf"), "test");
    UNITTEST(object.getInt("hmm"), 42);
    UNITTEST(object.getFloat("xyz"), 42.5f);
}

/**
 * getKeys_test
 */
void
DataItems_DataObject_Test::getKeys_test()
{
    DataObject object = initTestObject();

    std::vector<std::string> keys = object.getKeys();
    UNITTEST(keys.size(), 4);
    UNITTEST(keys.at(0), "asdf");
    UNITTEST(keys.at(1), "hmm");
    UNITTEST(keys.at(2), "poi");
    UNITTEST(keys.at(3), "xyz");
}

/**
 * getValues_test
 */
void
DataItems_DataObject_Test::getValues_test()
{
    DataObject object = initTestObject();

    std::vector<DataItem*> values = object.getValues();
    UNITTEST(values.size(), 4);
    UNITTEST(values.at(0)->toString(), "test");
    UNITTEST(values.at(1)->toString(), "42");
    UNITTEST(values.at(2)->toString(), "");
    UNITTEST(values.at(3)->toString(), "42.500000");
}

/**
 * contains_test
 */
void
DataItems_DataObject_Test::contains_test()
{
    DataObject object = initTestObject();
    UNITTEST(object.contains("poi"), true);
    UNITTEST(object.contains("asdf"), true);
    UNITTEST(object.contains("hmm"), true);
    UNITTEST(object.contains("xyz"), true);

    UNITTEST(object.contains("fail"), false);
}

/**
 * create test data-object
 *
 * @return data-object for tests
 */
DataObject
DataItems_DataObject_Test::initTestObject()
{
    DataObject object;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    object.insert("poi", defaultValue.copy());
    object.insert("asdf", stringValue.copy());
    object.insert("hmm", intValue.copy());
    object.insert("xyz", floatValue.copy());

    return object;
}

}  // namespace Common
}  // namespace Kitsune

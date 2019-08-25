/**
 *  @file    data_items.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief data-items for universal data-structures
 *
 *  @detail These was originally created in libKitsuneJson. Thats why the strint-output of the
 *          structure has still json-format. It can handle list, maps and values and is used
 *          in all of the kitsune-parser libraries as internal data-representation.
 */

#ifndef DATAITEMS_H
#define DATAITEMS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Kitsune
{
namespace Common
{
class DataArray;
class DataObject;
class DataValue;

//===================================================================
// DataItem
//===================================================================
class DataItem
{
public:
    virtual ~DataItem();

    enum dataTypes {
        UNINIT_TYPE = 0,
        VALUE_TYPE = 1,
        OBJECT_TYPE = 2,
        ARRAY_TYPE = 3
    };

    enum dataValueTypes {
        UNINIT_VALUE_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        FLOAT_TYPE = 3,
    };

    // getter
    virtual DataItem* operator[](const std::string key) = 0;
    virtual DataItem* operator[](const uint64_t index) = 0;
    virtual DataItem* get(const std::string key) = 0;
    virtual DataItem* get(const uint64_t index) = 0;
    virtual uint64_t size() = 0;

    // delete
    virtual bool remove(const std::string &key) = 0;
    virtual bool remove(const uint64_t index) = 0;

    // output
    virtual DataItem* copy() = 0;
    virtual std::string print(bool indent=false,
                              std::string *output=nullptr,
                              uint32_t step=0) = 0;

    dataTypes getType() const;
    bool isValue() const;
    bool isObject() const;
    bool isArray() const;

    DataArray* toArray();
    DataObject* toObject();
    DataValue* toValue();

    const std::string toString() const;
    int toInt();
    float toFloat();

protected:
    dataTypes m_type = UNINIT_TYPE;
    dataValueTypes m_valueType = UNINIT_VALUE_TYPE;

    void addIndent(std::string* output,
                   const bool indent,
                   const uint32_t level);
};

//===================================================================
// DataValue
//===================================================================
class DataValue : public DataItem
{
public:
    DataValue();
    DataValue(const std::string &text);
    DataValue(const int value);
    DataValue(const float value);
    ~DataValue();

    // setter
    dataValueTypes getValueType();
    void setValue(const std::string &item);
    void setValue(const int &item);
    void setValue(const float &item);

    // getter
    DataItem* operator[](const std::string);
    DataItem* operator[](const uint64_t);
    DataItem* get(const std::string);
    DataItem* get(const uint64_t);
    uint64_t size();

    // delete
    bool remove(const std::string&);
    bool remove(const uint64_t);

    // output
    DataItem* copy();
    std::string print(const bool=false,
                      std::string* output=nullptr,
                      const uint32_t=0);

    // content
    std::string m_stringValue = "";
    int m_intValue = 0;
    float m_floatValue = 0.0f;
};

//===================================================================
// DataObject
//===================================================================
class DataObject : public DataItem
{
public:
    DataObject();
    ~DataObject();

    // add
    bool insert(const std::string &key,
                DataItem* value,
                bool force = false);

    // getter
    DataItem* operator[](const std::string key);
    DataItem* operator[](const uint64_t index);
    DataItem* get(const std::string key);
    DataItem* get(const uint64_t index);
    uint64_t size();

    std::vector<std::string> getKeys();
    std::vector<DataItem*> getValues();
    bool contains(const std::string &key);

    std::string getString(const std::string &key);
    int getInt(const std::string &key);
    float getFloat(const std::string &key);

    // delete
    bool remove(const std::string &key);
    bool remove(const uint64_t index);

    // output
    DataItem* copy();
    std::string print(const bool=false,
                      std::string* output=nullptr,
                      const uint32_t level=0);

    // content
    std::map<std::string, DataItem*> m_objects;
};

//===================================================================
// DataArray
//===================================================================
class DataArray : public DataItem
{
public:
    DataArray();
    ~DataArray();

    // add
    bool append(DataItem* item);

    // getter
    DataItem* operator[](const std::string key);
    DataItem* operator[](const uint64_t index);
    DataItem* get(const std::string);
    DataItem* get(const uint64_t index);
    uint64_t size();

    // delete
    bool remove(const std::string &key);
    bool remove(const uint64_t index);

    // output
    DataItem* copy();
    std::string print(const bool indent=false,
                      std::string* output=nullptr,
                      const uint32_t level=0);

    // content
    std::vector<DataItem*> m_array;
};


}  // namespace Common
}  // namespace Kitsune

#endif // DATAITEMS_H

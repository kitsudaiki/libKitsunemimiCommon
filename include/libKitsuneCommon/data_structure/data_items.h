/**
 *  @file    data_items.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
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
    virtual DataItem* operator[](const uint32_t index) = 0;
    virtual DataItem* get(const std::string key) = 0;
    virtual DataItem* get(const uint32_t index) = 0;
    virtual uint32_t getSize() const = 0;

    // delete
    virtual bool remove(const std::string &key) = 0;
    virtual bool remove(const uint32_t index) = 0;

    // output
    virtual DataItem* copy() = 0;
    virtual std::string print(std::string *output=nullptr,
                              bool indent=false,
                              uint32_t step=0) = 0;

    dataTypes getType() const;
    bool isValue() const;
    bool isObject() const;
    bool isArray() const;

    DataArray* toArray();
    DataObject* toObject();
    DataValue* toValue();

    std::string toString();
    int toInt();
    float toFloat();

protected:
    dataTypes m_type = UNINIT_TYPE;
    dataValueTypes m_valueType = UNINIT_VALUE_TYPE;

    void addIndent(std::string *output,
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
    DataItem* operator[](const uint32_t);
    DataItem* get(const std::string);
    DataItem* get(const uint32_t);
    uint32_t getSize() const;

    // delete
    bool remove(const std::string&);
    bool remove(const uint32_t);

    // output
    DataItem* copy();
    std::string print(std::string *output=nullptr,
                      const bool indent=false,
                      const uint32_t level=0);

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
    DataItem* operator[](const uint32_t index);
    DataItem* get(const std::string key);
    DataItem* get(const uint32_t index);
    uint32_t getSize() const;

    std::vector<std::string> getKeys();
    std::vector<DataItem*> getValues();
    bool contains(const std::string &key);

    std::string getString(const std::string &key);
    int getInt(const std::string &key);
    float getFloat(const std::string &key);

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    DataItem* copy();
    std::string print(std::string *output=nullptr,
                      const bool indent=false,
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
    DataItem* operator[](const uint32_t index);
    DataItem* get(const std::string key);
    DataItem* get(const uint32_t index);
    uint32_t getSize() const;

    // delete
    bool remove(const std::string &key);
    bool remove(const uint32_t index);

    // output
    DataItem* copy();
    std::string print(std::string *output=nullptr,
                      const bool indent=false,
                      const uint32_t level=0);

    // content
    std::vector<DataItem*> m_array;
};


}  // namespace Common
}  // namespace Kitsune

#endif // DATAITEMS_H

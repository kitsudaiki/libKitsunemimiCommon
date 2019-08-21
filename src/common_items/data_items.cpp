/**
 *  @file    data_items.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

//===================================================================
// AbstractData
//===================================================================

DataItem::~DataItem() {}

/**
 * @brief request type, of the current data-object
 *
 * @return object-specific entry of the dataTypes-enumeration
 */
DataItem::dataTypes
DataItem::getType() const
{
    return m_type;
}

/**
 * @brief check if DataItem is a DataValue
 */
bool
DataItem::isValue() const
{
    if(m_type == VALUE_TYPE)
    {
        return true;
    }
    return false;
}

/**
 * @brief check if DataItem is a DataObject
 */
bool
DataItem::isObject() const
{
    if(m_type == OBJECT_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief check if DataItem is a DataArray
 */
bool
DataItem::isArray() const
{
    if(m_type == ARRAY_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief convert to a DataArray
 */
DataArray*
DataItem::toArray()
{
    if(m_type == ARRAY_TYPE) {
        return static_cast<DataArray*>(this);
    }
    return nullptr;
}

/**
 * @brief convert to a DataObject
 */
DataObject*
DataItem::toObject()
{
    if(m_type == OBJECT_TYPE) {
        return static_cast<DataObject*>(this);
    }
    return nullptr;
}

/**
 * @brief convert to a DataVolue
 */
DataValue*
DataItem::toValue()
{
    if(m_type == VALUE_TYPE)
    {
        return static_cast<DataValue*>(this);
    }
    return nullptr;
}

/**
 * @brief request the string of the data-value, if it is from string-type
 *
 * @return string of the data-value, if data-value is from string-type, else empty string
 */
std::string
DataItem::toString()
{
    if(m_valueType == STRING_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_stringValue;
    }
    if(m_valueType == INT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return std::to_string(value->m_intValue);;
    }
    if(m_valueType == FLOAT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return std::to_string(value->m_floatValue);;
    }
    return "";
}

/**
 * @brief request the integer of the data-value, if it is from int-type
 *
 * @return integer of the data-value, if data-value is from int-type, else empty 0
 */
int
DataItem::toInt()
{
    if(m_valueType == INT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_intValue;
    }
    return 0;
}


/**
 * @brief request the flaot of the data-value, if it is from float-type
 *
 * @return float of the data-value, if data-value is from float-type, else empty 0.0
 */
float
DataItem::toFloat()
{
    if(m_valueType == FLOAT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_floatValue;
    }
    return 0.0f;
}

/**
 * @brief add indent and linebreak to be better human-readable
 */
void
DataItem::addIndent(std::string* output,
                    const bool indent,
                    const uint32_t level)
{
    if(indent == true)
    {
        output->append("\n");
        for(uint32_t i = 0; i < level; i++)
        {
            output->append("    ");
        }
    }
}

//===================================================================
// DataValue
//===================================================================

/**
 * @brief DataValue::DataValue
 */
DataValue::DataValue()
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;
}

/**
 * @brief data-value for strings
 */
DataValue::DataValue(const std::string &text)
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;
    m_stringValue = text;
}

/**
 * @brief data-value for integers
 */
DataValue::DataValue(const int value)
{
    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;
    m_intValue = value;
}

/**
 * @brief data-value for float
 */
DataValue::DataValue(const float value)
{
    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;
    m_floatValue = value;
}

/**
 * @brief destructor
 */
DataValue::~DataValue() {}

/**
 * @brief get type inside the data-value
 *
 * @return value-type
 */
DataValue::dataValueTypes
DataValue::getValueType()
{
    return m_valueType;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::operator[](const std::string)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::operator[](const uint32_t)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::get(const std::string)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::get(const uint32_t)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime 0
 */
uint32_t
DataValue::getSize() const
{
    return 0;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime false
 */
bool
DataValue::remove(const std::string&)
{
    return false;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime false
 */
bool
DataValue::remove(const uint32_t)
{
    return false;
}

/**
 * @brief copy the data-value
 *
 * @return pointer to a copy of the value
 */
DataItem*
DataValue::copy()
{
    DataValue* tempItem = nullptr;
    if(m_valueType == STRING_TYPE) {
        tempItem = new DataValue(m_stringValue);
    }
    if(m_valueType == INT_TYPE) {
        tempItem = new DataValue(m_intValue);
    }
    if(m_valueType == FLOAT_TYPE) {
        tempItem = new DataValue(m_floatValue);
    }
    return tempItem;
}

/**
 * @brief prints the content of the object
 */
std::string
DataValue::print(std::string* output,
                 const bool indent,
                 const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    if(m_valueType == STRING_TYPE)
    {
        output->append("\"");
        output->append(m_stringValue);
        output->append("\"");
    }
    if(m_valueType == INT_TYPE) {
        output->append(std::to_string(m_intValue));
    }
    if(m_valueType == FLOAT_TYPE) {
        output->append(std::to_string(m_floatValue));
    }

    return out;
}

/**
 * @brief writes a new string into the data-value
 */
void
DataValue::setValue(const std::string &item)
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;
    m_intValue = 0;
    m_floatValue = 0.0f;
    m_stringValue = item;
}

/**
 * @brief writes a new integer into the data-value
 */
void
DataValue::setValue(const int &item)
{
    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;
    m_stringValue = "";
    m_floatValue = 0.0f;
    m_intValue = item;
}

/**
 * @brief writes a new integer into the data-value
 */
void
DataValue::setValue(const float &item)
{
    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;
    m_stringValue = "";
    m_intValue = 0;
    m_floatValue = item;
}

//===================================================================
// DataObject
//===================================================================

/**
 * @brief object for key-value-pairs
 */
DataObject::DataObject()
{
    m_type = OBJECT_TYPE;
}

/**
 * @brief delete all items in the key-value-list
 */
DataObject::~DataObject()
{
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        DataItem* tempItem = it->second;
        delete tempItem;
    }
    m_objects.clear();
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataObject::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
DataItem*
DataObject::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataObject::get(const std::string key)
{
    std::map<std::string, DataItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
DataItem*
DataObject::get(const uint32_t index)
{
    if(m_objects.size() <= index) {
        return nullptr;
    }

    uint32_t counter = 0;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_objects.begin();
        it != m_objects.end();
        it++)
    {
        if(counter == index) {
            return it->second;
        }
        counter++;
    }

    return nullptr;
}

/**
 * @brief getter for the number of elements in the key-value-list
 *
 * @return number of elements in the key-value-list
 */
uint32_t
DataObject::getSize() const
{
    return static_cast<uint32_t>(m_objects.size());
}

/**
 * @brief get list of keys of the objects-map
 *
 * @return string-list with the keys of the map
 */
std::vector<std::string>
DataObject::getKeys()
{
    std::vector<std::string> result;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        result.push_back(it->first);
    }
    return result;
}

/**
 * @brief get list of values of the objects-map
 *
 * @return DataItem-list with the keys of the map
 */
std::vector<DataItem*>
DataObject::getValues()
{
    std::vector<DataItem*> result;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        result.push_back(it->second);
    }
    return result;
}

/**
 * @brief check if a key is in the object-map
 *
 * @return false if the key doesn't exist, else true
 */
bool
DataObject::contains(const std::string &key)
{
    std::map<std::string, DataItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end())
    {
        return true;
    }
    return false;
}

/**
 * @brief get the string-value behind the key inside the data-object
 */
std::string
DataObject::getString(const std::string &key)
{
    DataItem* item = get(key);
    return item->toString();
}

/**
 * @brief get the int-value behind the key inside the data-object
 */
int
DataObject::getInt(const std::string &key)
{
    DataItem* item = get(key);
    return item->toInt();
}

/**
 * @brief get the float-value behind the key inside the data-object
 */
float
DataObject::getFloat(const std::string &key)
{
    DataItem* item = get(key);
    return item->toFloat();
}

/**
 * @brief remove an item from the key-value-list
 *
 * @return false if the key doesn't exist, else true
 */
bool
DataObject::remove(const std::string &key)
{
    std::map<std::string, DataItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end())
    {
        DataItem* tempItem = it->second;
        delete tempItem;
        m_objects.erase(it);
        return true;
    }

    return false;
}

/**
 * @brief remove an item from the object
 *
 * @return false if index is to high, else true
 */
bool
DataObject::remove(const uint32_t index)
{
    if(m_objects.size() <= index) {
        return false;
    }

    uint32_t counter = 0;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        if(counter == index)
        {
            DataItem* tempItem = it->second;
            delete tempItem;
            m_objects.erase(it);
            return true;
        }
        counter++;
    }
    return false;
}

/**
 * @brief copy the object with all elements
 *
 * @return pointer to a copy of the object
 */
DataItem*
DataObject::copy()
{
    DataObject* tempItem = new DataObject();
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_objects.begin(); it != m_objects.end(); it++)
    {
        tempItem->insert(it->first, it->second->copy());
    }
    return tempItem;
}

/**
 * @brief prints the content of the object
 */
std::string
DataObject::print(std::string* output,
                  const bool indent,
                  const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    bool firstPring = false;
    output->append("{");

    for(uint8_t typeCounter = 1; typeCounter < 6; typeCounter++)
    {
        std::map<std::string, DataItem*>::iterator it;
        for(it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if(it->second != nullptr
                    && it->second->getType() != typeCounter)
            {
                continue;
            }

            if(firstPring) {
                output->append(",");
            }
            firstPring = true;

            addIndent(output, indent, level+1);

            output->append("\"");
            output->append(it->first);
            output->append("\"");
            output->append(":");

            if(indent == true) {
                output->append(" ");
            }

            // TODO: add unit-tests for nullptr-case
            if(it->second == nullptr) {
                output->append("NULL");
            } else {
                it->second->print(output, indent, level+1);
            }
        }
    }

    addIndent(output, indent, level);
    output->append("}");

    return out;
}

/**
 * @brief add new key-value-pair to the object
 *
 * @return false if key already exist, else true
 */
bool
DataObject::insert(const std::string &key,
                   DataItem* value,
                   bool force)
{


    std::map<std::string, DataItem*>::iterator it;
    it = m_objects.find(key);

    if(it != m_objects.end()
            && force == false)
    {
        return false;
    }

    if(it != m_objects.end()) {
        it->second = value;
    } else {
        m_objects.insert(std::pair<std::string, DataItem*>(key, value));
    }
    return true;
}

//===================================================================
// DataArray
//===================================================================

/**
 * @brief array for items in data-style
 */
DataArray::DataArray()
{
    m_type = ARRAY_TYPE;
}

/**
 * @brief delete all items in the array
 */
DataArray::~DataArray()
{
    //std::cout<<"DataArray: "<<this<<std::endl;
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        DataItem* tempItem = m_array[i];
        delete tempItem;
    }
    m_array.clear();
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index in key is to high, else true
 */
DataItem*
DataArray::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index is to high, else true
 */
DataItem*
DataArray::operator[](const uint32_t index)
{
    return get(index);
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataArray::get(const std::string key)
{
    return nullptr;
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index is to high, else the object
 */
DataItem*
DataArray::get(const uint32_t index)
{
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * @brief getter for the number of elements in the array
 *
 * @return number of elements in the array
 */
uint32_t
DataArray::getSize() const
{
    return static_cast<uint32_t>(m_array.size());
}

/**
 * @brief remove an item from the array
 *
 * @return false if index in key is to high, else true
 */
bool
DataArray::remove(const std::string &key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() <= index) {
        return false;
    }
    DataItem* tempItem = m_array[index];
    delete tempItem;
    m_array.erase(m_array.begin() + index);
    return true;
}

/**
 * @brief remove an item from the array
 *
 * @return false if index is to high, else true
 */
bool
DataArray::remove(const uint32_t index)
{
    if(m_array.size() <= index) {
        return false;
    }
    DataItem* tempItem = m_array[index];
    delete tempItem;
    m_array.erase(m_array.begin() + index);
    return true;
}

/**
 * @brief copy the array with all elements
 *
 * @return pointer to a copy of the array
 */
DataItem*
DataArray::copy()
{
    DataArray* tempItem = new DataArray();
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        tempItem->append(m_array[i]->copy());
    }
    return tempItem;
}

/**
 * @brief prints the content of the object
 */
std::string
DataArray::print(std::string* output,
                 const bool indent,
                 const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    output->append("[");
    addIndent(output, indent, level+1);

    std::vector<DataItem*>::iterator it;
    for(it = m_array.begin(); it != m_array.end(); it++)
    {
        if(it != m_array.begin())
        {
            output->append(",");
            addIndent(output, indent, level+1);
        }

        if((*it) == nullptr) {
            continue;
        }

        (*it)->print(output, indent, level+1);
    }

    addIndent(output, indent, level);
    output->append("]");

    return out;
}

/**
 * @brief add a new item to the array
 *
 * @return false, if new item-pointer is nullptr, else true
 */
bool
DataArray::append(DataItem* item)
{
    if(item == nullptr) {
        return false;
    }

    m_array.push_back(item);
    return true;
}


}  // namespace Common
}  // namespace Kitsune

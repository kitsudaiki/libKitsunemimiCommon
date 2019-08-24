/**
 *  @file    table_items.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <common_items/table_item.h>
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

/**
 * @brief TableItem::TableItem
 */
TableItem::TableItem()
{
    m_header = new DataArray();
    m_body = new DataArray();
}

/**
 * @brief TableItem::TableItem
 * @param body
 * @param header
 */
TableItem::TableItem(DataArray *body,
                     DataArray *header)
{
    // init header
    if(header == nullptr) {
        m_header = new DataArray();
    } else {
        m_header = header->copy()->toArray();
    }

    // init body
    if(body == nullptr) {
        m_body = new DataArray();
    } else {
        m_body = body->copy()->toArray();
    }
}

/**
 * @brief TableItem::~TableItem
 */
TableItem::~TableItem()
{
    delete m_body;
    delete m_header;
}

/**
 * @brief TableItem::addColumn
 * @param internalName
 * @param shownName
 * @return
 */
bool
TableItem::addColumn(const std::string &internalName,
                     const std::string &shownName)
{
    DataObject* obj = new DataObject();

    obj->insert("inner", new DataValue(internalName));
    if(shownName != "") {
        obj->insert("outer", new DataValue(shownName));
    } else {
        obj->insert("outer", new DataValue(internalName));
    }

    return m_header->append(obj);
}

/**
 * @brief TableItem::renameColume
 * @param internalName
 * @param newShownName
 * @return
 */
bool
TableItem::renameColume(const std::string &internalName,
                        const std::string &newShownName)
{
    const uint64_t size = m_header->getSize();

    for(uint64_t x = 0; x < size; x++)
    {
        if(m_header->get(x)->get("inner")->toString() == internalName)
        {
            m_header->get(x)->get("outer")->toValue()->setValue(newShownName);
            return true;
        }
    }

    return false;
}

/**
 * @brief TableItem::deleteColumn
 * @param x
 * @param withBody
 * @return
 */
bool
TableItem::deleteColumn(const uint64_t x,
                        const bool withBody)
{
    // precheck
    if(x >= m_header->getSize()) {
        return false;
    }

    // get internal header-name
    const std::string name = m_header->get(x)->get("inner")->toString();

    // remove colume from header
    m_header->remove(x);

    // remove data of the column
    if(withBody)
    {
        const uint64_t size = m_body->getSize();

        for(uint64_t y = 0; y < size; y++)
        {
            m_body->get(y)->toObject()->remove(name);
        }
    }

    return true;
}

/**
 * @brief TableItem::deleteColumn
 * @param internalName
 * @param withBody
 * @return
 */
bool
TableItem::deleteColumn(const std::string &internalName,
                        const bool withBody)
{
    const uint64_t size = m_header->getSize();

    // search in header
    for(uint64_t x = 0; x < size; x++)
    {
        if(m_header->get(x)->get("inner")->toString() == internalName) {
            return deleteColumn(x, withBody);
        }
    }

    return false;
}

/**
 * @brief TableItem::addRow
 * @param rowContent
 * @return
 */
bool
TableItem::addRow(const std::vector<std::string> rowContent)
{
    DataObject* obj = new DataObject();

    uint64_t size = rowContent.size();
    if(m_header->getSize() < size) {
        size = m_header->getSize();
    }

    for(uint64_t x = 0; x < size; x++)
    {
        obj->insert(m_header->get(x)->get("inner")->toString(),
                    new DataValue(rowContent.at(x)));
    }

    return m_body->append(obj);
}

/**
 * @brief TableItem::deleteRow
 * @param y
 * @return
 */
bool
TableItem::deleteRow(const uint64_t y)
{
    // precheck
    if(y >= m_body->getSize())
    {
        return false;
    }

    m_body->remove(y);

    return true;
}

/**
 * @brief TableItem::setCell
 * @param x
 * @param y
 * @param newValue
 * @return
 */
bool
TableItem::setCell(const uint32_t x,
                   const uint32_t y,
                   const std::string &newValue)
{
    // precheck
    if(x >= m_header->getSize()
            || y >= m_body->getSize())
    {
        return false;
    }

    // get value at requested position
    const std::string columnInnerName = m_header->get(x)->get("inner")->toString();
    DataItem* value = m_body->get(y)->get(columnInnerName);

    // set new value
    if(value == nullptr) {
        m_body->get(y)->toObject()->insert(columnInnerName, new DataValue(newValue));
    } else {
        value->toValue()->setValue(newValue);
    }

    return true;
}

/**
 * @brief request the content of a specific cell of the table
 *
 * @param x x-position of the cell within the table
 * @param y y-position of the cell within the table
 *
 * @return content of the cell as string or empty-string if cell is not set or exist
 *         and also empty string, if x or y is too hight
 */
std::string
TableItem::getCell(const uint32_t x,
                   const uint32_t y)
{
    // precheck
    if(x >= m_header->getSize()
            || y >= m_body->getSize())
    {
        return "";
    }

    // get value at requested position
    const std::string columnInnerName = m_header->get(x)->get("inner")->toString();
    DataItem* value = m_body->get(y)->get(columnInnerName);

    // check value
    if(value == nullptr) {
        return "";
    }

    // return value-content as string
    return value->toString();
}

/**
 * @brief TableItem::deleteCell
 * @param x
 * @param y
 * @return
 */
bool
TableItem::deleteCell(const uint32_t x,
                      const uint32_t y)
{
    // precheck
    if(x >= m_header->getSize()
            || y >= m_body->getSize())
    {
        return false;
    }

    // get column inner name
    const std::string columnInnerName = m_header->get(x)->get("inner")->toString();

    // remove value if possible
    return m_body->get(y)->remove(columnInnerName);
}

/**
 * @brief TableItem::getNumberOfColums
 * @return
 */
uint64_t
TableItem::getNumberOfColums()
{
    return m_header->getSize();
}

/**
 * @brief TableItem::getNumberOfRows
 * @return
 */
uint64_t
TableItem::getNumberOfRows()
{
    return m_body->getSize();
}

/**
 * @brief TableItem::toString
 * @return
 */
std::string
TableItem::print()
{
    // init
    std::vector<uint64_t> xSizes(getNumberOfColums(), 0);
    std::vector<uint64_t> ySizes(getNumberOfRows(), 0);

    // collect size-values of each row and column
    for(uint64_t x = 0; x < getNumberOfColums(); x++)
    {
        const std::pair<uint64_t, uint64_t> headerCellSize = getHeaderCellSize(x);
        if(xSizes.at(x) < headerCellSize.first) {
            xSizes[x] = headerCellSize.first;
        }

        for(uint64_t y = 0; y < getNumberOfRows(); y++)
        {
            const std::pair<uint64_t, uint64_t> cellSize = getBodyCellSize(x, y);
            if(xSizes.at(x) < cellSize.first) {
                xSizes[x] = cellSize.first;
            }
            if(ySizes.at(y) < cellSize.second) {
                ySizes[y] = cellSize.second;
            }
        }
    }

    const std::string limitLine = getLimitLine(xSizes);

    std::string result = "";

    result.append(limitLine);
    result.append(printHeaderLine(xSizes));
    result.append(limitLine);

    for(uint64_t y = 0; y < getNumberOfRows(); y++)
    {
        result.append(printBodyLine(xSizes, y));
    }

    result.append(limitLine);

    return result;
}

/**
 * @brief TableItem::getLimitLine
 * @param sizes
 * @return
 */
const std::string
TableItem::getLimitLine(const std::vector<uint64_t> &sizes)
{
    std::string output = "";

    for(uint64_t i = 0; i < sizes.size(); i++)
    {
        output.append("+");
        output.append(std::string(sizes.at(i) + 2, '-'));
    }

    output.append("+\n");

    return output;
}

/**
 * @brief TableItem::printHeaderLine
 * @param sizes
 * @return
 */
const std::string
TableItem::printHeaderLine(const std::vector<uint64_t> &sizes)
{
    std::string output = "";

    for(uint64_t i = 0; i < sizes.size(); i++)
    {
        output.append("| ");
        DataValue* value = m_header->get(i)->get("outer")->toValue();
        output.append(value->toString());
        output.append(std::string(sizes.at(i) - value->getSize(), ' '));
        output.append(" ");
    }

    output.append("|\n");

    return output;
}

/**
 * @brief TableItem::printBodyLine
 * @param sizes
 * @param y
 * @return
 */
const std::string
TableItem::printBodyLine(const std::vector<uint64_t> &sizes,
                         const uint64_t y)
{
    std::string output = "";

    for(uint64_t i = 0; i < sizes.size(); i++)
    {
        output.append("| ");
        const std::string columnName = m_header->get(i)->get("inner")->toValue()->toString();
        DataItem* item = m_body->get(y)->get(columnName);

        if(item == nullptr)
        {
            output.append(std::string(sizes.at(i), ' '));
            output.append(" ");
        }
        else
        {
            DataValue* value = item->toValue();
            output.append(value->toString());
            output.append(std::string(sizes.at(i) - value->getSize(), ' '));
            output.append(" ");
        }
    }

    output.append("|\n");

    return output;
}

/**
 * @brief TableItem::getHeaderCellSize
 * @param x
 * @return
 */
const std::pair<uint64_t, uint64_t>
TableItem::getHeaderCellSize(const uint64_t x)
{
    // init
    std::pair<uint64_t, uint64_t> result;
    result.first = 0;
    result.second = 0;

    // precheck
    if(x >= m_header->getSize())
    {
        return result;
    }

    // get value at requested position
    DataItem* value = m_header->get(x)->get("outer");

    if(value == nullptr) {
        return result;
    }

    // get string-length
    result.first += value->toValue()->getSize();
    result.second = 0;

    return result;
}

/**
 * @brief TableItem::getCellSize
 * @param x
 * @param y
 * @return
 */
const std::pair<uint64_t, uint64_t>
TableItem::getBodyCellSize(const uint64_t x,
                           const uint64_t y)
{
    // init
    std::pair<uint64_t, uint64_t> result;
    result.first = 0;
    result.second = 0;

    // precheck
    if(x >= m_header->getSize()
            || y >= m_body->getSize())
    {
        return result;
    }

    // get value at requested position
    const std::string columnInnerName = m_header->get(x)->get("inner")->toString();
    DataItem* value = m_body->get(y)->get(columnInnerName);

    if(value == nullptr) {
        return result;
    }

    // get string-length
    result.first += value->toValue()->getSize();
    result.second = 0;

    return result;
}

}  // namespace Common
}  // namespace Kitsune

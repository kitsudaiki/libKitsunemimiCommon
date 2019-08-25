/**
 *  @file    table_items.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief data-handling object for tables
 *
 *  @detail This was created to print data as table on the command-line. Its primary to make
 *          data better visible for the user. Internally it uses the the data-items of this
 *          library. So its possible to easily convert json-items of libKitsuneJson
 *          into this table-output for example in REST-API responses.
 */

#include <common_items/table_item.h>
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

/**
 * @brief constructor
 */
TableItem::TableItem()
{
    m_header = new DataArray();
    m_body = new DataArray();
}

/**
 * @brief copy-constructor
 */
TableItem::TableItem(const TableItem &other)
{
    m_body = other.m_body->copy()->toArray();
    m_header = other.m_header->copy()->toArray();
}

/**
 * @brief create a table from predefined values
 *
 * @param body body-content as data-array-item
 * @param header header-content as data-array-item
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
 * @brief destructor
 */
TableItem::~TableItem()
{
    // delete all data of the table
    delete m_body;
    delete m_header;
}

/**
 * @brief assignment-constructor
 */
TableItem&
TableItem::operator=(const TableItem& other)
{
    // check for self-assignment
    if(&other == this) {
        return *this;
    }

    delete m_body;
    delete m_header;

    m_body = other.m_body->copy()->toArray();
    m_header = other.m_header->copy()->toArray();

    return *this;
}

/**
 * @brief add a new column to the header of the table
 *
 * @param internalName name for internal indentification of the columns inside the body
 * @param shownName name which is shown in the string-output of the table
 *                  if leaved blank, the name is set equal to the internal-name
 *
 * @return should return true everytime
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
 * @brief rename a column in the header of the table
 *
 * @param internalName name for internal indentification of the columns inside the body
 * @param newShownName new name for string output
 *
 * @return false if internal-name doesn't exist, else true
 */
bool
TableItem::renameColume(const std::string &internalName,
                        const std::string &newShownName)
{
    const uint64_t size = m_header->size();

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
 * @brief delelete a colume from the table
 *
 * @param x column-position
 * @param withBody true for delete all column-related data from the body of the table too,
 *                 false for delete column only from the header
 *
 * @return false if column-position is too high, else true
 */
bool
TableItem::deleteColumn(const uint64_t x,
                        const bool withBody)
{
    // precheck
    if(x >= m_header->size()) {
        return false;
    }

    // get internal header-name
    const std::string name = m_header->get(x)->get("inner")->toString();

    // remove colume from header
    m_header->remove(x);

    // remove data of the column
    if(withBody)
    {
        const uint64_t size = m_body->size();

        for(uint64_t y = 0; y < size; y++)
        {
            m_body->get(y)->toObject()->remove(name);
        }
    }

    return true;
}

/**
 * @brief delelete a colume from the table
 *
 * @param internalName internal name of the column
 * @param withBody true for delete all column-related data from the body of the table too,
 *                 false for delete column only from the header
 *
 * @return false if internal name doesn't exist, else true
 */
bool
TableItem::deleteColumn(const std::string &internalName,
                        const bool withBody)
{
    const uint64_t size = m_header->size();

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
 * @brief add a new row to the table
 *
 * @param rowContent vector of string for the content of the new row
 *
 * @return should return true everytime
 */
bool
TableItem::addRow(const std::vector<std::string> rowContent)
{
    DataObject* obj = new DataObject();

    // check and cut size
    uint64_t size = rowContent.size();
    if(m_header->size() < size) {
        size = m_header->size();
    }

    // add new row content to the table
    for(uint64_t x = 0; x < size; x++)
    {
        obj->insert(m_header->get(x)->get("inner")->toString(),
                    new DataValue(rowContent.at(x)));
    }

    return m_body->append(obj);
}

/**
 * @brief delete a row from the table
 *
 * @param y row-position
 *
 * @return false if row-position is too high, else true
 */
bool
TableItem::deleteRow(const uint64_t y)
{
    // precheck
    if(y >= m_body->size())
    {
        return false;
    }

    m_body->remove(y);

    return true;
}

/**
 * @brief set the content of a specific cell inside the table
 *
 * @param x x-position of the cell within the table
 * @param y y-position of the cell within the table
 * @param newValue new cell-value as string
 *
 * @return false if x or y is too hight, esle true
 */
bool
TableItem::setCell(const uint32_t x,
                   const uint32_t y,
                   const std::string &newValue)
{
    // precheck
    if(x >= m_header->size()
            || y >= m_body->size())
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
    if(x >= m_header->size()
            || y >= m_body->size())
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
 * @brief delete a spcific cell from the table
 *
 * @param x x-position of the cell within the table
 * @param y y-position of the cell within the table
 *
 * @return false if cell-content is already deleted or if x or y is too hight, else true
 */
bool
TableItem::deleteCell(const uint32_t x,
                      const uint32_t y)
{
    // precheck
    if(x >= m_header->size()
            || y >= m_body->size())
    {
        return false;
    }

    // get column inner name
    const std::string columnInnerName = m_header->get(x)->get("inner")->toString();

    // remove value if possible
    return m_body->get(y)->remove(columnInnerName);
}

/**
 * @brief request number of columns of the table
 *
 * @return number of columns
 */
uint64_t
TableItem::getNumberOfColums()
{
    return m_header->size();
}

/**
 * @brief request number of rows of the table
 *
 * @return number of rows
 */
uint64_t
TableItem::getNumberOfRows()
{
    return m_body->size();
}

/**
 * @brief converts the table-content into a string
 *
 * @return table as string
 */
std::string
TableItem::print()
{
    // init
    std::vector<uint64_t> xSizes(getNumberOfColums(), 0);
    std::vector<uint64_t> ySizes(getNumberOfRows(), 0);

    // collect size-values of within the table
    for(uint64_t x = 0; x < getNumberOfColums(); x++)
    {
        // collect size-values of the header-entries
        const std::pair<uint64_t, uint64_t> headerCellSize = getHeaderCellSize(x);
        if(xSizes.at(x) < headerCellSize.first) {
            xSizes[x] = headerCellSize.first;
        }

        // collect size-values of each row and column
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

    // create separator-line
    const std::string limitLine = getLimitLine(xSizes);

    std::string result = "";

    // print table-header
    result.append(limitLine);
    result.append(printHeaderLine(xSizes));
    result.append(limitLine);

    // print table body
    for(uint64_t y = 0; y < getNumberOfRows(); y++)
    {
        result.append(printBodyLine(xSizes, y));
    }
    result.append(limitLine);

    return result;
}

/**
 * @brief create separator-line for the table
 *
 * @param sizes list with all width-values for printing placeholder
 *
 * @return separator-line as string
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
 * @brief convert the header of the table into a string
 *
 * @param sizes list with all width-values for printing placeholder
 *
 * @return sting with the content of the header for output
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
        output.append(std::string(sizes.at(i) - value->size(), ' '));
        output.append(" ");
    }

    output.append("|\n");

    return output;
}

/**
 * @brief converts a row of the table into a string
 *
 * @param sizes list with all width-values for printing placeholder
 * @param y row-number
 *
 * @return sting with the content of a row for output
 */
const std::string
TableItem::printBodyLine(const std::vector<uint64_t> &sizes,
                         const uint64_t y)
{
    std::string output = "";

    for(uint64_t i = 0; i < sizes.size(); i++)
    {
        output.append("| ");

        // get cell of the table
        const std::string columnName = m_header->get(i)->get("inner")->toValue()->toString();
        DataItem* item = m_body->get(y)->get(columnName);

        if(item == nullptr)
        {
            // print empty cell
            output.append(std::string(sizes.at(i), ' '));
            output.append(" ");
        }
        else
        {
            // print cell-content and fill the rest with blank
            DataValue* value = item->toValue();
            output.append(value->toString());
            output.append(std::string(sizes.at(i) - value->size(), ' '));
            output.append(" ");
        }
    }

    output.append("|\n");

    return output;
}

/**
 * @brief request the cell-dimensions of a specific cell inside the header
 *
 * @param x column-position
 *
 * @return width and hight of the cell inside the header as pair
 */
const std::pair<uint64_t, uint64_t>
TableItem::getHeaderCellSize(const uint64_t x)
{
    // init
    std::pair<uint64_t, uint64_t> result;
    result.first = 0;
    result.second = 0;

    // precheck
    if(x >= m_header->size())
    {
        return result;
    }

    // get value at requested position
    DataItem* value = m_header->get(x)->get("outer");

    if(value == nullptr) {
        return result;
    }

    // get string-length
    result.first += value->toValue()->size();
    result.second = 0;

    return result;
}

/**
 * @brief request the cell-dimensions of a specific cell inside the table
 *
 * @param x x-position of the cell within the table
 * @param y y-position of the cell within the table
 *
 * @return width and hight of the cell inside the body as pair, or a pair of null-values
 *         if x or y is too hight or cell is deleted
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
    if(x >= m_header->size()
            || y >= m_body->size())
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
    result.first += value->toValue()->size();
    result.second = 0;

    return result;
}

}  // namespace Common
}  // namespace Kitsune

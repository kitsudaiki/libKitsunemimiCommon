/**
 *  @file       table_items.h
 *
 *  @brief      Data-handling object for tables.
 *
 *  @details    This was created to print data as table on the command-line. Its primary to make
 *              data better visible for the user. Internally it uses the the data-items of this
 *              library. So its possible to easily convert json-items of libKitsuneJson into this
 *              table-output for example in REST-API responses.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */


#include <common_items/table_item.h>
#include <common_items/data_items.h>

#include <common_methods/string_methods.h>

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
 * @brief erase the whole content of the table
 */
void
TableItem::clearTable()
{
    delete m_body;
    delete m_header;

    m_header = new DataArray();
    m_body = new DataArray();
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
    DataMap* obj = new DataMap();

    obj->insert("inner", new DataValue(internalName));
    if(shownName != "") {
        obj->insert("outer", new DataValue(shownName));
    } else {
        obj->insert("outer", new DataValue(internalName));
    }

    m_header->append(obj);
    return true;
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
        if(m_header->get(x)->get("inner")->getString() == internalName)
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
    const std::string name = m_header->get(x)->get("inner")->getString();

    // remove colume from header
    m_header->remove(x);

    // remove data of the column
    if(withBody)
    {
        const uint64_t size = m_body->size();

        for(uint64_t y = 0; y < size; y++)
        {
            m_body->get(y)->toMap()->remove(name);
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
        if(m_header->get(x)->get("inner")->getString() == internalName) {
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
    DataMap* obj = new DataMap();

    // check and cut size
    uint64_t size = rowContent.size();
    if(m_header->size() < size) {
        size = m_header->size();
    }

    // add new row content to the table
    for(uint64_t x = 0; x < size; x++)
    {
        obj->insert(m_header->get(x)->get("inner")->getString(),
                    new DataValue(rowContent.at(x)));
    }

    m_body->append(obj);
    return true;
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
    const std::string columnInnerName = m_header->get(x)->get("inner")->getString();
    DataItem* value = m_body->get(y)->get(columnInnerName);

    // set new value
    if(value == nullptr) {
        m_body->get(y)->toMap()->insert(columnInnerName, new DataValue(newValue));
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
    const std::string columnInnerName = m_header->get(x)->get("inner")->getString();
    DataItem* value = m_body->get(y)->get(columnInnerName);

    // check value
    if(value == nullptr) {
        return "";
    }

    // return value-content as string
    return value->getString();
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
    const std::string columnInnerName = m_header->get(x)->get("inner")->getString();

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
 * @param maxColumnWidth maximum width of a column in number of characters
 * @param showOne output as vertical table with the header on the left and the first row
 *                in the right column
 *
 * @return table as string
 */
const std::string
TableItem::toString(const uint32_t maxColumnWidth,
                    const bool showOne)
{
    // init data-handling values
    std::vector<uint64_t> xSizes(getNumberOfColums(), 0);
    std::vector<uint64_t> ySizes(getNumberOfRows(), 0);
    TableBodyAll convertedBody;
    TableRow convertedHeader;

    // converts the table into a better format for the output
    // and get the maximum values of the columns and rows
    const std::vector<std::string> innerNames = getInnerName();
    convertHeaderForOutput(&convertedHeader,
                           &xSizes,
                           maxColumnWidth);
    convertBodyForOutput(&convertedBody,
                         &xSizes,
                         &ySizes,
                         innerNames,
                         maxColumnWidth);

    // print as vertical table if required
    if(showOne)
    {
        return printVerticalTable(&convertedHeader,
                                  &convertedBody);
    }

    // print as normal table
    return printNormalTable(&convertedBody,
                            &xSizes,
                            &ySizes);
}

/**
 * @brief output of the content as classic table.
 *
 * @param convertedBody content of the body in converted form
 * @param xSizes target of the x-size values
 * @param ySizes target of the y-size values
 *
 * @return table as string
 */
const std::string
TableItem::printNormalTable(TableItem::TableBodyAll *convertedBody,
                            std::vector<uint64_t> *xSizes,
                            std::vector<uint64_t> *ySizes)
{
    // create separator-line
    const std::string normalSeparator = getLimitLine(*xSizes);
    std::string result = "";

    // print table-header
    result.append(normalSeparator);
    result.append(printHeaderLine(*xSizes));
    result.append(getLimitLine(*xSizes, true));

    // print table body
    for(uint64_t y = 0; y < getNumberOfRows(); y++)
    {
        result.append(printBodyLine(&convertedBody->at(y), *xSizes, ySizes->at(y)));
        result.append(getLimitLine(*xSizes));
    }

    return result;
}

/**
 * @brief if the table has only one row, it can be printed as vertical table, where the left
 *        column contains the header of the table and the right side the content of the first row.
 *        This makes the output better visible.
 *
 * @param convertedHeader content of the header in converted form
 * @param convertedBody content of the body in converted form
 *
 * @return table as string
 */
const std::string
TableItem::printVerticalTable(TableRow* convertedHeader,
                              TableBodyAll* convertedBody)
{
    std::vector<uint64_t> xSizes(2, 0);
    std::vector<uint64_t> ySizes(getNumberOfColums(), 0);

    // in case of a vertical the size-values have be checked again in another order
    for(uint64_t y = 0; y < getNumberOfColums(); y++)
    {
        // calcluate for the header
        if(xSizes.at(0) < convertedHeader->at(y).at(0).size()) {
            xSizes[0] = convertedHeader->at(y).at(0).size();
        }
        if(ySizes.at(y) < convertedHeader->at(y).size()) {
            ySizes[y] = convertedHeader->at(y).size();
        }

        // calculate for the first row of the body
        if(xSizes.at(1) < convertedBody->at(y).at(0).at(0).size()) {
            xSizes[1] = convertedBody->at(y).at(0).at(0).size();
        }
        if(ySizes.at(y) < convertedBody->at(y).at(0).size()) {
            ySizes[y] = convertedBody->at(y).at(0).size();
        }
    }

    // create separator-line
    const std::string normalSeparator = getLimitLine(xSizes);
    std::string result = "";

    // print table-header
    result.append(normalSeparator);

    // print table body
    for(uint64_t y = 0; y < getNumberOfColums(); y++)
    {
        result.append(printHeaderBodyLine(convertedHeader,
                                          &convertedBody->at(0),
                                          xSizes,
                                          ySizes.at(y),
                                          y));
        result.append(getLimitLine(xSizes));
    }

    return result;
}

/**
 * @brief get all internal column-names
 *
 * @return list with all internal names
 */
const std::vector<std::string>
TableItem::getInnerName()
{
    std::vector<std::string> result;

    for(uint64_t x = 0; x < getNumberOfColums(); x++)
    {
        result.push_back(m_header->get(x)->get("inner")->getString());
    }

    return result;
}

/**
 * @brief finialize a cell of the table for output, by spliting it into multiple lines
 *        if necessary.
 *
 * @param convertedCell target of the result of the convert
 * @param cellContent cell-content as string
 * @param width width of the current column
 * @param maxColumnWidth maximum with of a single column in number of characters
 */
void
TableItem::convertCellForOutput(TableCell* convertedCell,
                                const std::string &cellContent,
                                uint64_t* width,
                                const uint32_t maxColumnWidth)
{
    *convertedCell = splitStringByDelimiter(cellContent, '\n');
    for(uint32_t line = 0; line < convertedCell->size(); line++)
    {
        if(convertedCell->at(line).size() > maxColumnWidth)
        {
            std::vector<std::string> sub = splitStringByLength(convertedCell->at(line),
                                                               maxColumnWidth);
            // delete old entry and replace it with the splitted content
            convertedCell->erase(convertedCell->begin() + line);
            convertedCell->insert(convertedCell->begin() + line,
                                  sub.begin(),
                                  sub.end());
        }

        // check for a new maximum of the column-width
        if(*width < convertedCell->at(line).size()) {
            *width = convertedCell->at(line).size();
        }
    }
}

/**
 * @brief converts the header of the table from a data-item-tree into a string-lists
 *
 * @param convertedHeader target of the result of the convert
 * @param xSizes target of the x-size values
 * @param maxColumnWidth maximum with of a single column in number of characters
 */
void
TableItem::convertHeaderForOutput(TableRow* convertedHeader,
                                  std::vector<uint64_t>* xSizes,
                                  const uint32_t maxColumnWidth)
{
    for(uint64_t x = 0; x < xSizes->size(); x++)
    {
        std::string cellContent = "";

        // get value at requested position
        DataItem* value = m_header->get(x)->get("outer");
        if(value != nullptr) {
            cellContent = value->toValue()->getString();
        }

        // split cell content
        TableCell splittedCellContent;
        convertCellForOutput(&splittedCellContent,
                             cellContent,
                             &(*xSizes)[x],
                             maxColumnWidth);

        convertedHeader->push_back(splittedCellContent);
    }
}

/**
 * @brief converts the body of the table from a data-item-tree into a string-lists
 *
 * @param convertedBody target of the result of the convert
 * @param xSizes target of the x-size values
 * @param ySizes target of the y-size values
 * @param columeInnerNames internal name of the columns, which should be in the result
 * @param maxColumnWidth maximum with of a single column in number of characters
 */
void
TableItem::convertBodyForOutput(TableBodyAll* convertedBody,
                                std::vector<uint64_t>* xSizes,
                                std::vector<uint64_t>* ySizes,
                                const std::vector<std::string> &columeInnerNames,
                                const uint32_t maxColumnWidth)
{
    for(uint64_t y = 0; y < getNumberOfRows(); y++)
    {
        convertedBody->push_back(TableRow());

        for(uint64_t x = 0; x < columeInnerNames.size(); x++)
        {
            std::string cellContent = "";

            // get cell content or use empty string, if cell not exist
            DataItem* value = m_body->get(y)->get(columeInnerNames.at(x));
            if(value != nullptr) {
                cellContent = value->toValue()->getString();
            }

            // split cell content
            TableCell splittedCellContent;
            convertCellForOutput(&splittedCellContent,
                                 cellContent,
                                 &(*xSizes)[x],
                                 maxColumnWidth);

            // check for a new maximum of the row-height
            if(ySizes->at(y) < splittedCellContent.size()) {
                (*ySizes)[y] = splittedCellContent.size();
            }

            convertedBody->at(y).push_back(splittedCellContent);
        }
    }
}

/**
 * @brief create separator-line for the table
 *
 * @param sizes list with all width-values for printing placeholder
 * @param bigLine if true, it use '=' instead of '-' for the lines (default = false)
 *
 * @return separator-line as string
 */
const std::string
TableItem::getLimitLine(const std::vector<uint64_t> &sizes,
                        const bool bigLine)
{
    std::string output = "";

    // set line type
    char lineSegment = '-';
    if(bigLine) {
        lineSegment = '=';
    }

    // create line
    for(uint64_t i = 0; i < sizes.size(); i++)
    {
        output.append("+");
        output.append(std::string(sizes.at(i) + 2, lineSegment));
    }
    output.append("+\n");

    return output;
}

/**
 * @brief convert the header of the table into a string
 *
 * @param xSizes list with all width-values for printing placeholder
 *
 * @return sting with the content of the header for output
 */
const std::string
TableItem::printHeaderLine(const std::vector<uint64_t> &xSizes)
{
    std::string output = "";

    for(uint64_t i = 0; i < xSizes.size(); i++)
    {
        output.append("| ");
        DataValue* value = m_header->get(i)->get("outer")->toValue();
        output.append(value->getString());
        output.append(std::string(xSizes.at(i) - value->size(), ' '));
        output.append(" ");
    }

    output.append("|\n");

    return output;
}

/**
 * @brief converts a row of the table into a string
 *
 * @param rowContent one row of the converted content of the table-body
 * @param xSizes list with all width-values for printing placeholder
 * @param rowHeight hight-value for printing placeholder
 *
 * @return sting with the content of a row for output
 */
const std::string
TableItem::printBodyLine(TableRow* rowContent,
                         const std::vector<uint64_t> &xSizes,
                         const uint64_t rowHeight)
{
    std::string output = "";

    // create output string for all lines of one table-row
    for(uint64_t line = 0; line < rowHeight; line++)
    {
        // print row line by line
        for(uint64_t i = 0; i < xSizes.size(); i++)
        {
            std::string singleCellLine = "";
            if(rowContent->at(i).size() > line) {
                singleCellLine = rowContent->at(i).at(line);
            }

            // create string for one line of one cell
            output.append("| ");
            output.append(singleCellLine);
            output.append(std::string(xSizes.at(i) - singleCellLine.size(), ' '));
            output.append(" ");
        }

        output.append("|\n");
    }

    return output;
}

/**
 * @brief converts a row of the table into a string
 *
 * @param convertedHeader target of the result of the convert
 * @param rowContent one row of the converted content of the table-body
 * @param xSizes list with all width-values for printing placeholder
 * @param rowHeigh number of lines of the table row
 * @param y number of the table row
 *
 * @return sting with the content of a row for output
 */
const std::string
TableItem::printHeaderBodyLine(TableItem::TableRow* headerContent,
                               TableItem::TableRow* rowContent,
                               const std::vector<uint64_t> &xSizes,
                               const uint64_t rowHeigh,
                               const uint64_t y)
{
    std::string output = "";

    // create output string for all lines of one table-row
    for(uint64_t line = 0; line < rowHeigh; line++)
    {
        std::string singleCellLine;

        // get line-content for the left side
        singleCellLine = "";
        if(headerContent->at(y).size() > line) {
            singleCellLine = headerContent->at(y).at(line);
        }

        // print left side
        output.append("| ");
        output.append(singleCellLine);
        output.append(std::string(xSizes.at(y) - singleCellLine.size(), ' '));
        output.append(" ");


        // get line-content for the right side
        singleCellLine = "";
        if(rowContent->at(y).size() > line) {
            singleCellLine = rowContent->at(y).at(line);
        }

        // print right side
        output.append("| ");
        output.append(singleCellLine);
        output.append(std::string(xSizes.at(y) - singleCellLine.size(), ' '));
        output.append(" ");

        output.append("|\n");
    }

    return output;
}

}  // namespace Common
}  // namespace Kitsune

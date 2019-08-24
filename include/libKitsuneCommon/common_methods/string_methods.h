/**
 *  @file    string_methods.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief often used methods for string-operations
 */

#ifndef STRING_METHODS_H
#define STRING_METHODS_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

namespace Kitsune
{
namespace Common
{

/**
 * sptrit a string at a specific delimiter
 *
 * @return vector with the string parts
 */
inline std::vector<std::string>
splitString(const std::string &inputString,
            const char delim)
{
    // precheck
    if(inputString.length() == 0) {
        return std::vector<std::string>();
    }

    // init variables
    std::stringstream inputStream(inputString);
    std::string item;
    std::vector<std::string> result;

    // split
    while(std::getline(inputStream, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

} // namespace Common
} // namespace Kitsune

#endif // STRINGMETHODS_H

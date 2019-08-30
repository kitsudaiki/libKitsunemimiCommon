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
splitStringByDelimiter(const std::string &inputString,
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

/**
 * @brief splitStringByLength
 * @param str
 * @param splitLength
 * @return
 */
inline std::vector<std::string>
splitStringByLength(const std::string &str,
                    const uint64_t splitLength)
{
    const uint64_t numberOfSubstrings = static_cast<const uint64_t>(str.length() / splitLength);
    std::vector<std::string> result;

    // split string
    // number of string +1 to handle leftovers
    for(uint64_t i = 0; i < numberOfSubstrings + 1; i++)
    {
        result.push_back(str.substr(i * splitLength, splitLength));
    }

    return result;
}

} // namespace Common
} // namespace Kitsune

#endif // STRINGMETHODS_H

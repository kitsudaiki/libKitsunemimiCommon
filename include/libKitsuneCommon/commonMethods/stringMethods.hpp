/**
 *  @file    stringMethods.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STRINGMETHODS_HPP
#define STRINGMETHODS_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

namespace Kitsune
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

} // namespace Kitsune

#endif // STRINGMETHODS_HPP
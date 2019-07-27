/**
 *  @file    vectorMethods.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef VECTORMETHODS_H
#define VECTORMETHODS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace Kitsune
{

/**
 * remove from a vector of strings all entries, which contains only a empty string
 */
inline bool
removeEmptyStrings(std::vector<std::string> *inputVector)
{
    // precheck
    if(inputVector == nullptr
            || inputVector->size() == 0)
    {
        return false;
    }

    // remove items
    std::vector<std::string>::iterator it = std::remove_if(inputVector->begin(),
                                                           inputVector->end(),
                                                           std::mem_fun_ref(&std::string::empty));
    inputVector->erase(it, inputVector->end());

    return true;
}

} // namespace Kitsune

#endif // VECTORMETHODS_H

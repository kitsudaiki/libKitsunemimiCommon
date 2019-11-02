/**
 *  @file       vector_methods.h
 *
 *  @brief      often used methods for vector-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef VECTOR_METHODS_H
#define VECTOR_METHODS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace Kitsunemimi
{
namespace Common
{

/**
 * remove from a vector of strings all entries, which contains only a empty string
 */
inline bool
removeEmptyStrings(std::vector<std::string>* inputVector)
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

} // namespace Common
} // namespace Kitsunemimi

#endif // VECTORMETHODS_H

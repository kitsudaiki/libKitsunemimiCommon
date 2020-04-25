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

bool removeEmptyStrings(std::vector<std::string>* inputVector);

} // namespace Kitsunemimi

#endif // VECTORMETHODS_H

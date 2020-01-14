/**
 * @file        process_execution.h
 *
 *  @brief      Methods to execute other programs
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef PROCESS_HANDLING_H
#define PROCESS_HANDLING_H

#include <vector>
#include <iostream>
#include <map>
#include <utility>

namespace Kitsunemimi
{

struct ProcressResult
{
    bool success = true;
    int exitStatus = 0;
    std::string processOutput = "";
    std::string errorMessage = "";
};

ProcressResult runSyncProcess(std::string command);
ProcressResult runSyncProcess(const std::string &programm,
                              const std::vector<std::string> &args);

} // namespace Kitsunemimi

#endif // PROCESS_HANDLING_H

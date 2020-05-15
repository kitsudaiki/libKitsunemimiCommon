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

struct ProcessResult
{
    bool success = true;
    int exitStatus = 0;
    std::string processOutput = "";
    std::string errorMessage = "";
};

ProcessResult runSyncProcess(std::string command);
ProcessResult runSyncProcess(const std::string &programm,
                             const std::vector<std::string> &args);

} // namespace Kitsunemimi

#endif // PROCESS_HANDLING_H

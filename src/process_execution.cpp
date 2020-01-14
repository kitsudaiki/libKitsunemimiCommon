/**
 *  @file       process_execution.cpp
 *
 *  @brief      Methods to execute other programs
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/process_execution.h>
#include <libKitsunemimiCommon/common_methods/string_methods.h>

namespace Kitsunemimi
{

/**
 * @brief run a programm synchrone
 *
 * @param blossomItem blossom-item, where the results of the run should be written back
 * @param command command to execute as shell-command
 *
 * @return result with all information like exit-status and std-output
 */
ProcressResult
runSyncProcess(std::string command)
{
    std::vector<std::string> args;
    args.push_back("-c");
    replaceSubstring(command, "\"", "\\\"");
    args.push_back("\"" + command + "\"");

    return runSyncProcess(std::string("/bin/sh"), args);
}

/**
 * @brief run a programm synchrone
 *
 * @param blossomItem blossom-item, where the results of the run should be written back
 * @param programm path to the programm to execute
 * @param args list of arguments
 *
 * @return result with all information like exit-status and std-output
 */
ProcressResult
runSyncProcess(const std::string &programm,
               const std::vector<std::string> &args)
{
    ProcressResult result;

    // prepare command
    std::string call = programm;
    for(uint32_t i = 0; i < args.size(); i++)
    {
        call += " " + args[i];
    }
    call.append(" 2>&1");

    // prepare buffer
    FILE* stream = nullptr;
    const uint32_t max_buffer = 256;
    char buffer[max_buffer];

    // start execution
    stream = popen(call.c_str(), "r");
    if(stream)
    {
        while(!feof(stream))
        {
            if(fgets(buffer, max_buffer, stream) != nullptr) {
                result.processOutput.append(buffer);
            }
        }
        result.exitStatus = pclose(stream);
    }
    else
    {
        result.errorMessage = "can not execute programm: " + programm;
        result.success = false;

        return result;
    }

    // check exit-status of the external process
    if(result.exitStatus != 0) {
        result.success = false;
    } else {
        result.success = true;
    }

    return result;
}

} // namespace Kitsunemimi

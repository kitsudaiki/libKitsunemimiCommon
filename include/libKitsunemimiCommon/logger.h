/**
 *  @file    logger.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief simple logger for events
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <mutex>
#include <filesystem>

#include <libKitsunemimiCommon/files/binary_file.h>
#include <libKitsunemimiCommon/common_items/table_item.h>

#define LOG_DEBUG Kitsunemimi::LOG_debug
#define LOG_INFO Kitsunemimi::LOG_info
#define LOG_WARNING Kitsunemimi::LOG_warning
#define LOG_ERROR Kitsunemimi::LOG_error

#ifndef ALL_WHITE_OUTPUT
#define YELLOW_COLOR "\033[1;33m"
#define WHITE_COLOR "\033[0m"
#define GREEN_COLOR "\033[1;32m"
#define RED_COLOR "\033[1;31m"
#define BLUE_COLOR "\033[1;34m"
#define PINK_COLOR "\033[1;95m"
#else
#define YELLOW_COLOR "\033[0m"
#define WHITE_COLOR "\033[0m"
#define GREEN_COLOR "\033[0m"
#define RED_COLOR "\033[0m"
#define BLUE_COLOR "\033[0m"
#define PINK_COLOR "\033[0m"
#endif

namespace Kitsunemimi
{

struct ErrorContainer
{
    bool _alreadyPrinted = false;
    std::vector<std::string> _errorMessages;
    std::vector<std::string> _possibleSolution;

    void addMeesage(const std::string &errorMessage)
    {
        _errorMessages.push_back(errorMessage);
        _alreadyPrinted = false;
    }

    void addSolution(const std::string &possibleSolution)
    {
        _possibleSolution.push_back(possibleSolution);
    }

    const std::string toString()
    {
        TableItem output;
        output.addColumn("key");
        output.addColumn("value");

        // add error-messages
        for(int32_t i = _errorMessages.size() - 1; i >= 0; i--) {
            output.addRow({"Error-Message Nr. " + std::to_string(i), _errorMessages.at(i)});
        }

        // build string with possible solutions
        std::string solutions = "";
        for(uint32_t i = 0; i < _possibleSolution.size(); i++)
        {
            if(i != 0) {
                solutions += "\n-----\n";
            }
            solutions += _possibleSolution.at(i);
        }

        // add possible solutions
        if(solutions.size() > 1) {
            output.addRow({"Possible Solution", solutions});
        }

        return output.toString(200, true);
    }
};

bool initFileLogger(const std::string &directoryPath,
                    const std::string &baseFileName,
                    const bool debugLog = false);
bool initConsoleLogger(const bool debugLog = false);
bool setDebugFlag(const bool debugLog);

bool LOG_debug(const std::string &message);
bool LOG_warning(const std::string &message);
bool LOG_error(ErrorContainer &container);
bool LOG_info(const std::string &message,
              const std::string &color = WHITE_COLOR);

void closeLogFile();

//==================================================================================================

class Logger
{
public:
    Logger();
    ~Logger();

    bool initFileLogger(const std::string &directoryPath,
                        const std::string &baseFileName,
                        const bool debugLog);
    bool initConsoleLogger(const bool debugLog);
    bool setDebugFlag(const bool debugLog);

    void closeLogFile();

    bool logData(const std::string &message,
                 const std::string &preTag,
                 const std::string &color,
                 const bool debug = false);

    std::string m_filePath = "";
    bool m_debugLog = false;

    static Kitsunemimi::Logger* m_logger;

private:
    bool m_enableConsoleLog = false;
    bool m_consoleDebugLog = false;

    bool m_enableFileLog = false;
    bool m_fileDebugLog = false;
    std::string m_directoryPath = "";
    std::string m_baseFileName = "";

    std::mutex m_lock;
    std::ofstream m_outputFile;

    const std::string getDatetime();
};

} // namespace Kitsunemimi

#endif // LOGGER_H

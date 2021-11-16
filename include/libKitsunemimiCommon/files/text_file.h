/**
 *  @file    text_file.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief data-items for universal data-structures
 *
 *  @detail different methods for simple text-file-operations
 */

#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <libKitsunemimiCommon/logger.h>

namespace Kitsunemimi
{

bool
readFile(std::string &readContent,
         const std::string &filePath,
         ErrorContainer &error);

bool
writeFile(const std::string &filePath,
          const std::string &content,
          ErrorContainer &error,
          const bool force=true);

bool
appendText(const std::string &filePath,
           const std::string &newText,
           ErrorContainer &error);

bool
replaceLine(const std::string &filePath,
            const uint32_t lineNumber,
            const std::string &newLineContent,
            ErrorContainer &error);

bool
replaceContent(const std::string &filePath,
               const std::string &oldContent,
               const std::string &newContent,
               ErrorContainer &error);

} // namespace Kitsunemimi

#endif // TEXT_FILE_H

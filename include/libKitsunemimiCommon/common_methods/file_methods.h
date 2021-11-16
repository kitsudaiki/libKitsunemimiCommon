/**
 *  @file       file_methods.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef FILE_METHODS_H
#define FILE_METHODS_H

#include <sstream>
#include <assert.h>
#include <vector>
#include <string>
#include <filesystem>

#include <libKitsunemimiCommon/logger.h>

namespace Kitsunemimi
{

bool listFiles(std::vector<std::string> &fileList,
               const std::string &path,
               const bool withSubdirs=true,
               const std::vector<std::string> &exceptions = {});

bool renameFileOrDir(const std::filesystem::path &oldPath,
                     const std::filesystem::path &newPath,
                     ErrorContainer &error);
bool copyPath(const std::filesystem::path &sourcePath,
              const std::filesystem::path &targetPath,
              ErrorContainer &error,
              const bool force=true);
bool createDirectory(const std::filesystem::path &path,
                     ErrorContainer &error);
bool deleteFileOrDir(const std::filesystem::path &path,
                     ErrorContainer &error);

}

#endif // FILE_METHODS_H

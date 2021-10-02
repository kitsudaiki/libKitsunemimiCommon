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

namespace Kitsunemimi
{

bool listFiles(std::vector<std::string> &fileList,
               const std::string &path,
               const bool withSubdirs=true,
               const std::vector<std::string> &exceptions = {});

bool renameFileOrDir(const std::filesystem::path &oldPath,
                     const std::filesystem::path &newPath,
                     std::string &errorMessage);
bool copyPath(const std::filesystem::path &sourcePath,
              const std::filesystem::path &targetPath,
              std::string &errorMessage,
              const bool force=true);
bool createDirectory(const std::filesystem::path &path,
                     std::string &errorMessage);
bool deleteFileOrDir(const std::filesystem::path &path,
                     std::string &errorMessage);

}

#endif // FILE_METHODS_H

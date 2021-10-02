/**
 *  @file       file_methods.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/common_methods/file_methods.h>

namespace Kitsunemimi
{

/**
 * @brief iterate over a directory and subdirectory to file all containing files
 *
 * @param fileList resulting string-list with the absolute path of all found files
 * @param directory directory-path where to search
 * @param withSubdirs false, to list only files in the current directory, but not files from
 *                    subdirectories
 * @param exceptions list with directory-names, which should be skipped
 */
void
getFilesInDir(std::vector<std::string> &fileList,
              const std::filesystem::path &directory,
              const bool withSubdirs,
              const std::vector<std::string> &exceptions)
{
    std::filesystem::directory_iterator end_itr;
    for(std::filesystem::directory_iterator itr(directory);
        itr != end_itr;
        ++itr)
    {
        if(is_directory(itr->path()))
        {
            if(withSubdirs == true)
            {
                bool foundInExceptions = false;

                for(uint64_t i = 0; i < exceptions.size(); i++)
                {
                    if(itr->path().filename().string() == exceptions.at(i)) {
                        foundInExceptions = true;
                    }
                }

                if(foundInExceptions == false) {
                    getFilesInDir(fileList, itr->path(), withSubdirs, exceptions);
                }
            }
        }
        else
        {
            fileList.push_back(itr->path().string());
        }
    }
}

/**
 * @brief iterate over a directory and subdirectory to file all containing files
 *
 * @param fileList resulting string-list with the absolute path of all found files
 * @param path path where to search. This should be a directory. If this is a file-path, this path
 *             is the only one in the resulting list
 * @param withSubdirs false, to list only files in the current directory, but not files from
 *                    subdirectories (Default: true)
 * @param exceptions list with directory-names, which should be skipped (Default: empty list)
 *
 * @return false, if path doesn't exist, else true
 */
bool
listFiles(std::vector<std::string> &fileList,
          const std::string &path,
          const bool withSubdirs,
          const std::vector<std::string> &exceptions)
{
    std::filesystem::path pathObj(path);
    if(std::filesystem::exists(pathObj) == false) {
        return false;
    }

    if(is_directory(pathObj))
    {
        getFilesInDir(fileList,
                      pathObj,
                      withSubdirs,
                      exceptions);
    }
    else
    {
        fileList.push_back(path);
    }

    return true;
}

/**
 * @brief get ralative path in relation to a new root-path
 *
 * @param oldRootPath old root-path
 * @param oldRelativePath old relative path
 * @param newRootPath new root-path
 *
 * @return new relative path
 */
const std::filesystem::path
getRelativePath(const std::filesystem::path &oldRootPath,
                const std::filesystem::path &oldRelativePath,
                const std::filesystem::path &newRootPath)
{
    std::filesystem::path completePath = oldRootPath / oldRelativePath;

    return std::filesystem::relative(completePath, newRootPath);
}

/**
 * @brief rename a file or directory
 *
 * @param oldPath origial path
 * @param newPath new path after renaming
 * @param errorMessage reference for error-message output
 *
 * @return true, if successful, else false
 */
bool
renameFileOrDir(const std::filesystem::__cxx11::path &oldPath,
                const std::filesystem::__cxx11::path &newPath,
                std::string &errorMessage)
{
    if(std::filesystem::exists(oldPath) == false)
    {
        errorMessage = "source-path " + oldPath.string() + " doesn't exist.";
        return false;
    }

    std::error_code errorCode;
    std::filesystem::rename(oldPath, newPath, errorCode);
    if(errorCode.value() != 0)
    {
        errorMessage = errorCode.message();
        return false;
    }

    return true;
}

/**
 * @brief copy a file or directory
 *
 * @param sourcePath origial path
 * @param targetPath path of the copy
 * @param errorMessage reference for error-message output
 * @param force true to delete target, if already exist, if something exist at the target-location
 *              (Default: true)
 *
 * @return true, if successful, else false
 */
bool
copyPath(const std::filesystem::path &sourcePath,
         const std::filesystem::path &targetPath,
         std::string &errorMessage,
         const bool force)
{
    if(std::filesystem::exists(sourcePath) == false)
    {
        errorMessage = "source-path " + sourcePath.string() + " doesn't exist.";
        return false;
    }

    std::error_code errorCode;
    if(force) {
        std::filesystem::remove_all(targetPath);
    }
    std::filesystem::copy(sourcePath, targetPath, errorCode);
    if(errorCode.value() != 0)
    {
        errorMessage = errorCode.message();
        return false;
    }

    return true;
}

/**
 * @brief create a directory
 *
 * @param path path to create
 * @param errorMessage reference for error-message output
 *
 * @return true, if successful, else false
 */
bool
createDirectory(const std::filesystem::path &path,
                std::string &errorMessage)
{
    if(std::filesystem::exists(path)
            && std::filesystem::is_regular_file(path))
    {
        errorMessage = "under path "
                       + path.string()
                       + " a file already exist.";
        return false;
    }

    std::error_code errorCode;
    const bool result = std::filesystem::create_directories(path, errorCode);
    if(result == false) {
        errorMessage = errorCode.message();
    }

    return result;
}

/**
 * @brief delete a path
 *
 * @param path path to delete
 * @param errorMessage reference for error-message output
 *
 * @return true, if successful, else false. Also return true, if path is already deleted.
 */
bool
deleteFileOrDir(const std::filesystem::path &path,
                std::string &errorMessage)
{
    if(std::filesystem::exists(path) == false) {
        return true;
    }

    std::error_code errorCode;
    const bool result = std::filesystem::remove_all(path, errorCode);
    if(result == false) {
        errorMessage = errorCode.message();
    }

    return result;
}

}

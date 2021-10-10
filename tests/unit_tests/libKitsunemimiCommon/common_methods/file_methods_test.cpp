/**
 *  @file      file_methods_test.cpp
 *
 *  @author    Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "file_methods_test.h"

#include <libKitsunemimiCommon/common_methods/file_methods.h>
#include <libKitsunemimiCommon/process_execution.h>

using Kitsunemimi::runSyncProcess;

namespace Kitsunemimi
{

/**
 * @brief constructor
 */
FileMethods_Test::FileMethods_Test()
    : Kitsunemimi::CompareTestHelper("FileMethods_Test")
{
    listFiles_test();
    renameFileOrDir_test();
    copyPath_test();
    createDirectory_test();
    deleteFileOrDir_test();
}

/**
 * @brief listFiles_test
 */
void
FileMethods_Test::listFiles_test()
{
    runSyncProcess(std::string("rm -r /tmp/listFiles_test/").c_str());
    runSyncProcess(std::string("mkdir /tmp/listFiles_test/").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/poi1").c_str());
    runSyncProcess(std::string("mkdir /tmp/listFiles_test/test1").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test1/poi1").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test1/poi2").c_str());
    runSyncProcess(std::string("mkdir /tmp/listFiles_test/test2").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test2/poi1").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test2/poi2").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test2/poi3").c_str());

    std::vector<std::string> fileList;

    listFiles(fileList, "/tmp/listFiles_test/");
    TEST_EQUAL(fileList.size(), 6);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/poi1");
    TEST_EQUAL(fileList.size(), 1);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/test1");
    TEST_EQUAL(fileList.size(), 2);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/", false);
    TEST_EQUAL(fileList.size(), 1);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/", true, std::vector<std::string>() = {"test1"});
    TEST_EQUAL(fileList.size(), 4);
    fileList.clear();

    runSyncProcess(std::string("rm -r /tmp/listFiles_test/").c_str());
}

/**
 * @brief renameFileOrDir_test
 */
void
FileMethods_Test::renameFileOrDir_test()
{
    bool result = false;

    const std::string oldFilePath = "/tmp/renameFileOrDir_test_testfile_ALT";
    const std::string newFileName = "/tmp/renameFileOrDir_test_testfile_NEU";

    runSyncProcess(std::string("touch " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFileName).c_str());

    std::string errorMessage = "";

    result = renameFileOrDir(oldFilePath, newFileName, errorMessage);
    TEST_EQUAL(result, true);

    result = renameFileOrDir(oldFilePath, newFileName, errorMessage);
    TEST_EQUAL(result, false);

    TEST_EQUAL(std::filesystem::exists(oldFilePath), false);
    TEST_EQUAL(std::filesystem::exists(newFileName), true);

    runSyncProcess(std::string("rm " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFileName).c_str());
}

/**
 * @brief copyPath_test
 */
void
FileMethods_Test::copyPath_test()
{
    bool result = false;

    const std::string oldFilePath = "/tmp/copyFile_test_testfile_ALT";
    const std::string newFileName = "/tmp/copyFile_test_testfile_NEU";

    runSyncProcess(std::string("touch " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFileName).c_str());

    std::string errorMessage = "";

    result = copyPath(oldFilePath, newFileName, errorMessage);
    TEST_EQUAL(result, true);

    result = copyPath(oldFilePath, newFileName, errorMessage, false);
    TEST_EQUAL(result, false);

    TEST_EQUAL(std::filesystem::exists(oldFilePath), true);
    TEST_EQUAL(std::filesystem::exists(newFileName), true);

    runSyncProcess(std::string("rm " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFileName).c_str());
}

/**
 * @brief createDirectory_test
 */
void
FileMethods_Test::createDirectory_test()
{
    bool result = false;

    const std::string testDirPath = "/tmp/deleteFileOrDir_test_testdir/test1";

    runSyncProcess(std::string("rm -r " + testDirPath).c_str());
    TEST_EQUAL(std::filesystem::exists(testDirPath), false);

    std::string errorMessage = "";

    result = createDirectory(testDirPath, errorMessage);
    TEST_EQUAL(result, true);

    TEST_EQUAL(std::filesystem::exists(testDirPath), true);

    result = createDirectory(testDirPath, errorMessage);
    TEST_EQUAL(result, false);

    runSyncProcess(std::string("rm -r " + testDirPath).c_str());
}

/**
 * @brief deleteFileOrDir_test
 */
void
FileMethods_Test::deleteFileOrDir_test()
{
    bool result = false;

    const std::string testFilePath = "/tmp/deleteFileOrDir_test_testfile";
    const std::string testDirPath = "/tmp/deleteFileOrDir_test_testdir";

    runSyncProcess(std::string("touch " + testFilePath).c_str());
    runSyncProcess(std::string("mkdir " + testDirPath).c_str());

    std::string errorMessage = "";

    TEST_EQUAL(std::filesystem::exists(testFilePath), true);
    TEST_EQUAL(std::filesystem::exists(testDirPath), true);

    result = deleteFileOrDir(testFilePath, errorMessage);
    TEST_EQUAL(result, true);

    result = deleteFileOrDir(testDirPath, errorMessage);
    TEST_EQUAL(result, true);

    result = deleteFileOrDir(testDirPath, errorMessage);
    TEST_EQUAL(result, true);

    TEST_EQUAL(std::filesystem::exists(testFilePath), false);
    TEST_EQUAL(std::filesystem::exists(testDirPath), false);

    runSyncProcess(std::string("rm " + testFilePath).c_str());
    runSyncProcess(std::string("rm -r " + testDirPath).c_str());
}

}
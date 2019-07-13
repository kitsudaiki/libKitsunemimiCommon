/**
 *  @file    stringMethodsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STRINGMETHODSTEST_H
#define STRINGMETHODSTEST_H

#include <testing/commonTest.h>

namespace Kitsune
{

class StringMethodsTest : public Kitsune::CommonTest
{
public:
    StringMethodsTest();

private:
    void testSplitString();
};

}

#endif // STRINGMETHODSTEST_H

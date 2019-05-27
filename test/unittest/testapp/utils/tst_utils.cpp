#include "tst_utils.h"
#include "tst_preferences.h"
#include "../../macro_for_test.h"

#include <utils/utils.h>

TestUtils::TestUtils(QObject *parent) : QObject(parent)
{
    RUN_CLASS(TestPreferences);
}

void TestUtils::testMicroSecToTimeStr()
{

}

void TestUtils::testSecToTimeStr()
{
    QCOMPARE(Utils::secToTimeStr(0), QString("00:00"));
    QCOMPARE(Utils::secToTimeStr(1), QString("00:01"));
    QCOMPARE(Utils::secToTimeStr(60), QString("01:00"));
    QCOMPARE(Utils::secToTimeStr(61), QString("01:01"));
    QCOMPARE(Utils::secToTimeStr(3600), QString("01:00:00"));
    QCOMPARE(Utils::secToTimeStr(3601), QString("01:00:01"));
    QCOMPARE(Utils::secToTimeStr(3661), QString("01:01:01"));
    QCOMPARE(Utils::secToTimeStr(362439), QString("99:99:99"));
}

void TestUtils::testAbsoluteFilePath()
{

}

void TestUtils::testExploreFile()
{

}

void TestUtils::testCpy2wchar()
{

}

void TestUtils::testDefaultDpiScale()
{

}

void TestUtils::testDpiScaled()
{

}

void TestUtils::testSmallIconSize()
{

}

void TestUtils::testMapNameToThumbName()
{

}

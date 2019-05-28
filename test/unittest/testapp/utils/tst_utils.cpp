#include "tst_utils.h"
#include "tst_preferences.h"
#include "../../macro_for_test.h"

#include <utils/utils.h>

TestUtils::TestUtils(QObject *parent) : QObject(parent)
{
    RUN_CLASS(TestPreferences);

    mDefaultDpiScale = Utils::defaultDpiScale();
}

void TestUtils::testMicroSecToTimeStr()
{
    QCOMPARE(Utils::microSecToTimeStr(0), QString("00:00"));
    QCOMPARE(Utils::microSecToTimeStr(1000), QString("00:01"));
    QCOMPARE(Utils::microSecToTimeStr(60000), QString("01:00"));
    QCOMPARE(Utils::microSecToTimeStr(61000), QString("01:01"));
    QCOMPARE(Utils::microSecToTimeStr(3600000), QString("01:00:00"));
    QCOMPARE(Utils::microSecToTimeStr(3601000), QString("01:00:01"));
    QCOMPARE(Utils::microSecToTimeStr(3661000), QString("01:01:01"));
    QCOMPARE(Utils::microSecToTimeStr(362439000), QString("99:99:99"));
    QCOMPARE(Utils::microSecToTimeStr(999999000), QString("99:99:99"));

    QCOMPARE(Utils::microSecToTimeStr(0, false), QString(" 0: 0"));
    QCOMPARE(Utils::microSecToTimeStr(1000, false), QString(" 0: 1"));
    QCOMPARE(Utils::microSecToTimeStr(60000, false), QString(" 1: 0"));
    QCOMPARE(Utils::microSecToTimeStr(61000, false), QString(" 1: 1"));
    QCOMPARE(Utils::microSecToTimeStr(3600000, false), QString(" 1: 0: 0"));
    QCOMPARE(Utils::microSecToTimeStr(3601000, false), QString(" 1: 0: 1"));
    QCOMPARE(Utils::microSecToTimeStr(3661000, false), QString(" 1: 1: 1"));
    QCOMPARE(Utils::microSecToTimeStr(362439000, false), QString("99:99:99"));
    QCOMPARE(Utils::microSecToTimeStr(999999000, false), QString("99:99:99"));
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
    QCOMPARE(Utils::secToTimeStr(999999), QString("99:99:99"));

    QCOMPARE(Utils::secToTimeStr(0, false), QString(" 0: 0"));
    QCOMPARE(Utils::secToTimeStr(1, false), QString(" 0: 1"));
    QCOMPARE(Utils::secToTimeStr(60, false), QString(" 1: 0"));
    QCOMPARE(Utils::secToTimeStr(61, false), QString(" 1: 1"));
    QCOMPARE(Utils::secToTimeStr(3600, false), QString(" 1: 0: 0"));
    QCOMPARE(Utils::secToTimeStr(3601, false), QString(" 1: 0: 1"));
    QCOMPARE(Utils::secToTimeStr(3661, false), QString(" 1: 1: 1"));
    QCOMPARE(Utils::secToTimeStr(362439, false), QString("99:99:99"));
    QCOMPARE(Utils::secToTimeStr(999999, false), QString("99:99:99"));
}

void TestUtils::testAbsoluteFilePath()
{
    QCOMPARE(Utils::absoluteFilePath("z:/a.txt"), QString("z:/a.txt"));
}

void TestUtils::testExploreFile()
{
    QVERIFY(Utils::exploreFile("C:/windows/explorer.exe"));
}

void TestUtils::testCpy2wchar()
{
    wchar_t buf[200];
    Utils::cpy2wchar(buf, QString::fromStdWString(L"地球"));
    QCOMPARE(wcscmp(buf, L"地球"), 0);

    Utils::cpy2wchar(buf, QString::fromStdWString(L"我要测试你"));
    QCOMPARE(wcscmp(buf, L"我要测试你"), 0);
}

void TestUtils::testDefaultDpiScale()
{
    QVERIFY(mDefaultDpiScale>0);
}

void TestUtils::testDpiScaled()
{
    QCOMPARE(Utils::dpiScaled(2.4), mDefaultDpiScale*2.4);
}

void TestUtils::testSmallIconSize()
{
    QCOMPARE(Utils::smallIconSize(), QSize(16,16));
}

void TestUtils::testMapNameToThumbName()
{
    QCOMPARE(Utils::mapNameToThumbName("map10.dat"), QString("map_10.jpg"));
    QCOMPARE(Utils::mapNameToThumbName("map10"), QString("map_10.jpg"));
    QCOMPARE(Utils::mapNameToThumbName("map0.dat"), QString("map_0.jpg"));
    QCOMPARE(Utils::mapNameToThumbName("a_map0.dat"), QString("a_map_0.jpg"));
}

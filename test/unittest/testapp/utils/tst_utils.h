#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QObject>
#include <QtTest>

class TestUtils : public QObject
{
    Q_OBJECT

public:
    explicit TestUtils(QObject *parent = 0);

private:
    qreal mDefaultDpiScale;

private Q_SLOTS:
    void testMicroSecToTimeStr();
    void testSecToTimeStr();
    void testAbsoluteFilePath();
    void testExploreFile();
    void testCpy2wchar();
    void testDefaultDpiScale();
    void testDpiScaled();
    void testSmallIconSize();
    void testMapNameToThumbName();
};

#endif // TESTUTILS_H

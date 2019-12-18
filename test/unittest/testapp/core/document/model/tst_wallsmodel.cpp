#include "tst_wallsmodel.h"

#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/wallmodel.h>

TestWallsModel::TestWallsModel(QObject *parent) :
    QObject(parent)
{

}


const char g_wallsmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};


void TestWallsModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TWallModel, buf, size);
}

void TestWallsModel::testReadWrite1()
{
    readWriteTest( g_wallsmodel_data1, sizeof( g_wallsmodel_data1));
}

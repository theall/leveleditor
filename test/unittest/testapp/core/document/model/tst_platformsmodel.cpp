#include "tst_platformsmodel.h"

#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/eventmodel.h>
const char g_eventmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};



TestPlatformsModel::TestPlatformsModel(QObject *parent) :
    QObject(parent)
{

}


void TestPlatformsModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TEventModel, buf, size);
}

void TestPlatformsModel::testReadWrite1()
{
    readWriteTest( g_eventmodel_data1, sizeof( g_eventmodel_data1));
}



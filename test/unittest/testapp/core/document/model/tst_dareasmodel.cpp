#include "tst_dareasmodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/dareamodel.h>
const char g_dareamodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};

TestDAreasModel::TestDAreasModel(QObject *parent) :
    QObject(parent)
{

}


void TestDAreasModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TDAreaModel, buf, size);
}

void TestDAreasModel::testReadWrite1()
{
    readWriteTest(g_dareamodel_data1, sizeof(g_dareamodel_data1));
}

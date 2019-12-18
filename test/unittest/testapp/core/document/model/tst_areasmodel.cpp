#include "tst_areasmodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/areamodel.h>

const char g_areamodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};





TestAreasModel::TestAreasModel(QObject *parent) :
    QObject(parent)
{

}


void TestAreasModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TAreaModel, buf, size);
}

void TestAreasModel::testReadWrite1()
{
    readWriteTest(g_areamodel_data1, sizeof(g_areamodel_data1));
}

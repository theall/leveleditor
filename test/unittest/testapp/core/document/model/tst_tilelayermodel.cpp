#include "tst_tilelayermodel.h"

#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/tilelayermodel.h>
const char g_tilelayermodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};

TestTileLayerModel::TestTileLayerModel(QObject *parent) :
    QObject(parent)
{

}

void TestTileLayerModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TTileModel, buf, size);
}

void TestTileLayerModel::testReadWrite1()
{
    readWriteTest( g_tilelayermodel_data1, sizeof( g_tilelayermodel_data1));
}

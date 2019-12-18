#include "tst_respawnsmodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/respawnmodel.h>
const char g_respawnsmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};
TestRespawnsModel::TestRespawnsModel(QObject *parent) :
    QObject(parent)
{

}

void TestRespawnsModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TRespawnModel, buf, size);
}

void TestRespawnsModel::testReadWrite1()
{
    readWriteTest( g_respawnsmodel_data1, sizeof( g_respawnsmodel_data1));
}


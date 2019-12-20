#include "tst_triggersmodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/triggermodel.h>
const char g_triggersmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};

TestTriggersModel::TestTriggersModel(QObject *parent) :
    QObject(parent)
{

}

void TestTriggersModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TTriggerModel, buf, size);
}

void TestTriggersModel::testReadWrite1()
{
    readWriteTest( g_triggersmodel_data1, sizeof( g_triggersmodel_data1));
}

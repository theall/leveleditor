#include "tst_eventsmodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/eventmodel.h>
const char g_eventsmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};



TestEventsModel::TestEventsModel(QObject *parent) :
    QObject(parent)
{

}


void TestEventsModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TEventModel, buf, size);
}

void TestEventsModel::testReadWrite1()
{
    readWriteTest( g_eventsmodel_data1, sizeof( g_eventsmodel_data1));
}


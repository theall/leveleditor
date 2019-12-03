#include "tst_trigger.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/trigger.h>
const char g_trigger_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00',
};
TestTrigger::TestTrigger(QObject *parent) : 
    QObject(parent)
{

}

void TestTrigger::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TTrigger, buf, size);
}

void TestTrigger::testReadWrite1()
{
    readWriteTest(g_trigger_data1, sizeof(g_trigger_data1));
}

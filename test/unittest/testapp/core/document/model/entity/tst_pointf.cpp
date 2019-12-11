#include "tst_pointf.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/pointf.h>

const char g_pointf_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C'

};

const char g_pointf_data2[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C'

};

TestPointF::TestPointF(QObject *parent) : 
    QObject(parent)
{

}

void TestPointF::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TPointF, buf, size);
}

void TestPointF::testReadWrite1()
{
    readWriteTest(g_pointf_data1, sizeof(g_pointf_data1));
}

void TestPointF::testReadWrite2()
{
    readWriteTest(g_pointf_data2, sizeof(g_pointf_data2));
}




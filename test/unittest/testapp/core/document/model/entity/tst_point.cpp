#include "tst_point.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/point.h>

const char g_point_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C'

};

const char g_point_data2[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C'

};


TestPoint::TestPoint(QObject *parent) : 
    QObject(parent)
{

}

void TestPoint::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TPoint, buf, size);
}

void TestPoint::testReadWrite1()
{
    readWriteTest(g_point_data2, sizeof(g_point_data2));
}

void TestPoint::testReadWrite2()
{
    readWriteTest(g_point_data2, sizeof(g_point_data2));
}





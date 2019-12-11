#include "tst_rect.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/rect.h>

const char g_rect_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
};

const char g_rect_data2[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
};

const char g_rect_data3[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
};

TestRect::TestRect(QObject *parent) : 
    QObject(parent)
{

}

void TestRect::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TRect, buf, size);
}

void TestRect::testReadWrite1()
{
    readWriteTest(g_rect_data1, sizeof(g_rect_data1));
}

void TestRect::testReadWrite2()
{
    readWriteTest(g_rect_data2, sizeof(g_rect_data2));
}

void TestRect::testReadWrite3()
{
    readWriteTest(g_rect_data3, sizeof(g_rect_data3));
}


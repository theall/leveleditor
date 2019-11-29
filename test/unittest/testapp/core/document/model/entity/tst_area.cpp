#include "tst_area.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/area.h>

const char g_area_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9'
};

const char g_area_data2[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x02', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9'
};

const char g_area_data3[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x04', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9'
};

TestArea::TestArea(QObject *parent) : 
    QObject(parent)
{

}

void TestArea::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TArea, buf, size);
}

void TestArea::testReadWrite1()
{
    readWriteTest(g_area_data1, sizeof(g_area_data1));
}

void TestArea::testReadWrite2()
{
    readWriteTest(g_area_data2, sizeof(g_area_data2));
}

void TestArea::testReadWrite3()
{
    readWriteTest(g_area_data3, sizeof(g_area_data3));
}

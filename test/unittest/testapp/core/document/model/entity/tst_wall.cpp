#include "tst_wall.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/wall.h>

const char g_wall_data1[] = {
    '\x20', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00',
    '\x20', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00',
};

const char g_wall_data2[] = {
    '\x20', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00',
    '\x20', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00',
};

const char g_wall_data3[] = {
    '\x20', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00',
    '\x20', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00',
};
TestWall::TestWall(QObject *parent) : 
    QObject(parent)
{

}

void TestWall::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TWall, buf, size);
}

void TestWall::testReadWrite1()
{
    readWriteTest(g_wall_data1, sizeof(g_wall_data1));
}

void TestWall::testReadWrite2()
{
    readWriteTest(g_wall_data2, sizeof(g_wall_data2));
}

void TestWall::testReadWrite3()
{
    readWriteTest(g_wall_data3, sizeof(g_wall_data3));
}



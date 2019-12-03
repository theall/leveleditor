#include "tst_plat.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/plat.h>
const char g_plat_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66',
};
TestPlat::TestPlat(QObject *parent) : 
    QObject(parent)
{

}
void TestPlat::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TPlat, buf, size);
}

void TestPlat::testReadWrite1()
{
    readWriteTest(g_plat_data1, sizeof(g_plat_data1));
}


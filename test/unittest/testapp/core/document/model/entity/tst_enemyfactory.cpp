#include "tst_enemyfactory.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/enemyfactory.h>

const char g_enemyfactory_data1[] = {
    '\x58', '\x30', '\xE3', '\x26', '\x78', '\xF1', '\xD2', '\xB',
    '\x68', '\xF1', '\xD2', '\xB', '\x00', '\x00', '\x00', '\x00',
    '\x58', '\x30', '\xE3', '\x26'
};

const char g_enemyfactory_data2[] = {
    '\x58', '\x30', '\xE3', '\x26', '\x78', '\xF1', '\xD2', '\xB',
    '\x68', '\xF1', '\xD2', '\xB', '\x00', '\x00', '\x00', '\x00',
    '\x58', '\x30', '\xE3', '\x26'
};

const char g_enemyfactory_data3[] = {
    '\x58', '\x30', '\xE3', '\x26', '\x78', '\xF1', '\xD2', '\xB',
    '\x68', '\xF1', '\xD2', '\xB', '\x00', '\x00', '\x00', '\x00',
    '\x58', '\x30', '\xE3', '\x26'
};

TestEnemyFactory::TestEnemyFactory(QObject *parent) : 
    QObject(parent)
{

}

void TestEnemyFactory::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TEnemyFactory, buf, size);
}

void TestEnemyFactory::testReadWrite1()
{
      readWriteTest(g_enemyfactory_data1, sizeof(g_enemyfactory_data1));
}

void TestEnemyFactory::testReadWrite2()
{
      readWriteTest(g_enemyfactory_data2, sizeof(g_enemyfactory_data2));
}

void TestEnemyFactory::testReadWrite3()
{
      readWriteTest(g_enemyfactory_data3, sizeof(g_enemyfactory_data3));
}






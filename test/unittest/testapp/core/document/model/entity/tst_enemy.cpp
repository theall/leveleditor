#include "tst_enemy.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/enemy.h>


const char g_enemy_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x42', '\x54', '\x8C', '\x6C',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x00', '\x00', '\x00', '\x00',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00'
};

const char g_enemy_data2[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x42', '\x54', '\x8C', '\x6C',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x00', '\x00', '\x00', '\x00',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00'
};

const char g_enemy_data3[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x42', '\x54', '\x8C', '\x6C',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x00', '\x00', '\x00', '\x00',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00'
};

const char g_enemy_data4[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x42', '\x54', '\x8C', '\x6C',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x00', '\x00', '\x00', '\x00',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00'
};



TestEnemy::TestEnemy(QObject *parent) :
    QObject(parent)
{

}

void TestEnemy::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TEnemy, buf, size);
}

void TestEnemy::testReadWrite1()
{
    readWriteTest(g_enemy_data1, sizeof(g_enemy_data1));
}

void TestEnemy::testReadWrite2()
{
    readWriteTest(g_enemy_data2, sizeof(g_enemy_data2));
}

void TestEnemy::testReadWrite3()
{
    readWriteTest(g_enemy_data3, sizeof(g_enemy_data3));
}

void TestEnemy::testReadWrite4()
{
    readWriteTest(g_enemy_data4, sizeof(g_enemy_data4));
}




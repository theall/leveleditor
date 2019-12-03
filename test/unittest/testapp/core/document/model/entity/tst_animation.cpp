#include "tst_animation.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/animation.h>

const char g_animation_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x00', '\x00', '\x00', '\x00',
    '\x57', '\x22', '\xDF', '\x88', '\x00', '\x00', '\x00', '\x00',
    '\x00', '\x00', '\x00', '\x00'
};

TestAnimation::TestAnimation(QObject *parent) : 
    QObject(parent)
{

}

void TestAnimation::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TAnimation, buf, size);
}

void TestAnimation::testReadWrite1()
{
    readWriteTest(g_animation_data1, sizeof(g_animation_data1));
}


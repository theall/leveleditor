#include "tst_frame.h"
#include "../streamiotest.h"

#include <QtTest>
#include <core/document/model/entity/frame.h>

const char g_frame_data1[] = {
    '\x57', '\x22', '\xDF', '\x88', '\x00', '\x00', '\x00', '\x00',
    '\x00', '\x00', '\x00', '\x00'
};

const char g_frame_data2[] = {
    '\x57', '\x22', '\xDF', '\x88', '\x00', '\x00', '\x00', '\x00',
    '\x00', '\x00', '\x00', '\x00'
};

const char g_frame_data3[] = {
    '\x57', '\x22', '\xDF', '\x88', '\x00', '\x00', '\x00', '\x00',
    '\x00', '\x00', '\x00', '\x00'
};

//'\x57', '\x22', '\xDF', '\x88', '\x00', '\x00', '\x00', '\x00',
//'\x00', '\x00', '\x00', '\x00'

TestFrame::TestFrame(QObject *parent) : 
    QObject(parent)
{

}

void TestFrame::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TFrame, buf, size);
}

void TestFrame::testReadWrite1()
{
      readWriteTest(g_frame_data1, sizeof(g_frame_data1));
}

void TestFrame::testReadWrite2()
{
      readWriteTest(g_frame_data2, sizeof(g_frame_data2));
}

void TestFrame::testReadWrite3()
{
      readWriteTest(g_frame_data3, sizeof(g_frame_data3));
}



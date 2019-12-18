#include "tst_animationsmodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/animationmodel.h>

const char g_animationsmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};

TestAnimationsModel::TestAnimationsModel(QObject *parent) :
    QObject(parent)
{

}

void TestAnimationsModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TAnimationModel, buf, size);
}

void TestAnimationsModel::testReadWrite1()
{
    readWriteTest(g_animationsmodel_data1, sizeof(g_animationsmodel_data1));
}


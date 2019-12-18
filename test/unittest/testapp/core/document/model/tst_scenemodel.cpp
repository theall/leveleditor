
#include "tst_scenemodel.h"
#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/scenemodel.h>

const char g_scenemodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\x00', '\x00', '\x00', '\x00',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
    '\x3D', '\x6D', '\x35', '\x66', '\xF8', '\x0F', '\x30', '\xB9',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
    '\x00', '\x00', '\x00', '\x00', '\x3D', '\x6D', '\x35', '\x66',
    '\x42', '\x54', '\x8C', '\x6C', '\x3D', '\xD3', '\x6E', '\x9C',
    '\x57', '\x22', '\xDF', '\x88', '\xBA', '\xC6', '\xCF', '\x6D',
};
TestSceneModel::TestSceneModel(QObject *parent) :
    QObject(parent)
{

}

void TestSceneModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TSceneModel, buf, size);
}

void TestSceneModel::testReadWrite1()
{
    readWriteTest(g_scenemodel_data1, sizeof(g_scenemodel_data1));
}


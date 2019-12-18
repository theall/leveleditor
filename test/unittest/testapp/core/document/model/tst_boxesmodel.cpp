#include "tst_boxesmodel.h"

#include "testapp/core/document/model/streamiotest.h"
#include <QtTest>
#include <core/document/model/boxmodel.h>




const char g_boxesmodel_data1[] = {
    '\x42', '\x54', '\x8C', '\x6C'
};

TestBoxesModel::TestBoxesModel(QObject *parent) :
    QObject(parent)
{

}





void TestBoxesModel::readWriteTest(const char *buf, int size)
{
    READ_WRITE_OBJECT_TEST(TBoxModel, buf, size);
}

void TestBoxesModel::testReadWrite1()
{
    readWriteTest(g_boxesmodel_data1, sizeof(g_boxesmodel_data1));
}

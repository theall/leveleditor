#include "tst_scenemodel.h"
#include <core/document/document.h>
#include <core/document/model/scenemodel.h>
#include <utils/preferences.h>

#include <QFile>
#include <QtTest>

TestSceneModel::TestSceneModel(QObject *parent) : 
    QObject(parent)
{

}

void TestSceneModel::testReadSave()
{
    TDocument document;
    TSceneModel model(&document);

    QString gameRoot = TPreferences::instance()->gameRoot();
    QVERIFY(!gameRoot.isEmpty());

    QString testMapName = gameRoot + "/Maps/Original/amap1.dat";

    QFile f(testMapName);
    QVERIFY(f.exists());

    QByteArray inData = f.readAll();
    f.close();

    QDataStream inStream(&inData, QIODevice::ReadOnly);
    inStream.setByteOrder(QDataStream::LittleEndian);
    inStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    model.readFromStream(inStream);

    QByteArray outData;
    QDataStream outStream(&outData, QIODevice::WriteOnly);
    outStream.setByteOrder(QDataStream::LittleEndian);
    outStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    model.saveToStream(outStream);

    QCOMPARE(inData, outData);
}


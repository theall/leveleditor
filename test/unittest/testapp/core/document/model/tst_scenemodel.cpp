#include "tst_scenemodel.h"
#include <core/document/document.h>
#include <core/document/model/scenemodel.h>
#include <utils/preferences.h>
#include <macro_for_test.h>
#include <QFile>
#include <QtTest>

#include "entity/tst_animation.h"
#include "entity/tst_area.h"
#include "entity/tst_box.h"
#include "entity/tst_darea.h"
#include "entity/tst_door.h"
#include "entity/tst_enemy.h"
#include "entity/tst_enemyfactory.h"
#include "entity/tst_frame.h"
#include "entity/tst_object.h"
#include "entity/tst_plat.h"
#include "entity/tst_point.h"
#include "entity/tst_pointf.h"
#include "entity/tst_rect.h"
#include "entity/tst_respawn.h"
#include "entity/tst_startpoint.h"
#include "entity/tst_tile.h"
#include "entity/tst_tilemovemodel.h"
#include "entity/tst_trigger.h"
#include "entity/tst_wall.h"

TestSceneModel::TestSceneModel(QObject *parent) : 
    QObject(parent)
{
    RUN_CLASS(TestAnimation);
    RUN_CLASS(TestArea);
    RUN_CLASS(TestBox);
    RUN_CLASS(TestDArea);
    RUN_CLASS(TestDoor);
    RUN_CLASS(TestEnemy);
    RUN_CLASS(TestEnemyFactory);
    RUN_CLASS(TestFrame);
    RUN_CLASS(TestObject);
    RUN_CLASS(TestPlat);
    RUN_CLASS(TestPoint);
    RUN_CLASS(TestPointF);
    RUN_CLASS(TestRect);
    RUN_CLASS(TestRespawn);
    RUN_CLASS(TestStartPoint);
    RUN_CLASS(TestTile);
    RUN_CLASS(TestTileMoveModel);
    RUN_CLASS(TestTrigger);
    RUN_CLASS(TestWall);
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


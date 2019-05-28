#include "tst_tileset.h"
#include <core/assets/tileset.h>
#include <macro_for_test.h>

TestTileset::TestTileset(QObject *parent) : 
    QObject(parent)
{

}

void TestTileset::testSetId()
{
    VERIFY_READ_WRITE_CLASS_VALUE(TTileset,id,setId,10);
}

void TestTileset::testAddTile()
{
    TTileset tileset;
    TTileId tileId;
    tileset.add(&tileId);
    QCOMPARE(tileset.getTileId(0), &tileId);
    tileset.add(0);
    QCOMPARE(tileset.tileList().size(), 1);
}

void TestTileset::testSort()
{
    TTileset tileset;
    TTileId tile1;
    TTileId tile2;
    TTileId tile3;
    TTileId tile4;
    TTileId tile5;
    tileset.add(&tile1);
    tileset.add(&tile2);
    tileset.add(&tile3);
    tileset.add(&tile4);
    tileset.add(&tile5);
    tileset.sort();
    QCOMPARE(tileset.tileList().size(), 5);
    QVERIFY(tileset.indexOf(&tile1)!=-1);
    QVERIFY(tileset.indexOf(&tile2)!=-1);
    QVERIFY(tileset.indexOf(&tile3)!=-1);
    QVERIFY(tileset.indexOf(&tile4)!=-1);
    QVERIFY(tileset.indexOf(&tile5)!=-1);
}

void TestTileset::testSetTileIdList()
{
    TTileset tileset;
    TTileIdList tileIdList;
    tileIdList.append(new TTileId);
    tileIdList.append(new TTileId);
    tileIdList.append(new TTileId);
    tileIdList.append(new TTileId);
    tileIdList.append(new TTileId);
    tileset.setTileList(tileIdList);
    QCOMPARE(tileset.tileList(), tileIdList);
}


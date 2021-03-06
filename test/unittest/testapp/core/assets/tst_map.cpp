#include "tst_map.h"
#include <QtTest>
#include <core/assets/maps.h>

TestMap::TestMap(QObject *parent) : 
    QObject(parent)
{

}

void TestMap::testNewMap()
{
    TModule module;
    TMapBundle mapBundle(&module);
    TMap map(TMap::ADV, &mapBundle);
    QCOMPARE(map.type(), TMap::ADV);
    QCOMPARE(map.id(), -1);
    QVERIFY(map.thumbnail());
    QCOMPARE(map.indexInMapBundle(), -1);

    map.setType(TMap::VS);
    QCOMPARE(map.type(), TMap::VS);

    map.setType(TMap::CTF);
    QCOMPARE(map.type(), TMap::CTF);
}

void TestMap::testOpenMap()
{
    TModule module;
    TMapBundle mapBundle(&module);
    TMap map(TMap::ADV, &mapBundle);
    QVERIFY(map.open());
}

void TestMap::testSaveMap()
{

}


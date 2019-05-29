#include "tst_tileid.h"
#include <core/assets/tileid.h>
#include <macro_for_test.h>

TestTileId::TestTileId(QObject *parent) : 
    QObject(parent)
{

}

void TestTileId::testSetId()
{
    TTileId tileId;
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, id, setId, 0);
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, id, setId, 1);
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, id, setId, -1);
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, id, setId, 9);
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, id, setId, 99999999);
}

void TestTileId::testSetPixmap()
{
    TTileId tileId;
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, pixmap, setPixmap, (TPixmap*)nullptr);
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, pixmap, setPixmap, new TPixmap(this));
}

void TestTileId::testSetTilesetId()
{
    TTileId tileId;
    VERIFY_READ_WRITE_OBJECT_VALUE(tileId, tilesetId, setTilesetId, 2345);
}


#include "tst_core.h"
#include "assets/tst_assetsmanager.h"
#include "assets/tst_cachedpixmap.h"
#include "assets/tst_cachedsound.h"
#include "assets/tst_faceid.h"
#include "assets/tst_map.h"
#include "assets/tst_mapbundle.h"
#include "assets/tst_module.h"
#include "assets/tst_pixmap.h"
#include "assets/tst_sound.h"
#include "assets/tst_tileid.h"
#include "assets/tst_tileset.h"
#include "document/tst_document.h"
#include "model/tst_charactermodel.h"
#include "model/tst_mapsmodel.h"
#include "model/tst_tilesetmodelmanager.h"
#include "model/tst_tilesetmodel.h"

#include <core/core.h>
#include <macro_for_test.h>

TestCore::TestCore(QObject *parent) :
    QObject(parent)
{
    RUN_CLASS(TestAssetsManager);
    RUN_CLASS(TestCachedPixmap);
    RUN_CLASS(TestCachedSound);
    RUN_CLASS(TestFaceId);
    RUN_CLASS(TestMap);
    RUN_CLASS(TestMapBundle);
    RUN_CLASS(TestModule);
    RUN_CLASS(TestPixmap);
    RUN_CLASS(TestSound);
    RUN_CLASS(TestTileId);
    RUN_CLASS(TestTileset);

    RUN_CLASS(TestDocument);

    RUN_CLASS(TestCharacterModel);
    RUN_CLASS(TestMapsModel);
    RUN_CLASS(TestTilesetModel);
    RUN_CLASS(TestTilesetModelManager);
}

void TestCore::testInit()
{
    TCore core;
}

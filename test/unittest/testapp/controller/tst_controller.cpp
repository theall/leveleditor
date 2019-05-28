#include "tst_controller.h"
#include "tst_characterpanelcontroller.h"
#include "tst_layerscontroller.h"
#include "tst_maincontroller.h"
#include "tst_mainpropertycontroller.h"
#include "tst_mapsdockcontroller.h"
#include "tst_miniscenecontroller.h"
#include "tst_optionscontroller.h"
#include "tst_propertycontroller.h"
#include "tst_tabcontroller.h"
#include "tst_tilesetcontroller.h"
#include "tst_undocontroller.h"

#include <macro_for_test.h>

TestController::TestController(QObject *parent) :
    QObject(parent)
{
    RUN_CLASS(TestTabController);
    RUN_CLASS(TestMainController);
    RUN_CLASS(TestUndoController);
    RUN_CLASS(TestLayersController);
    RUN_CLASS(TestOptionsController);
    RUN_CLASS(TestTilesetController);
    RUN_CLASS(TestMapsDockController);
    RUN_CLASS(TestPropertyController);
    RUN_CLASS(TestMiniSceneController);
    RUN_CLASS(TestMainPropertyController);
    RUN_CLASS(TestCharacterPanelController);
}


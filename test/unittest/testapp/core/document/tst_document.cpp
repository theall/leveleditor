#include "tst_document.h"
#include "model/tst_scenemodel.h"

#include <macro_for_test.h>

TestDocument::TestDocument(QObject *parent) : 
    QObject(parent)
{
    RUN_CLASS(TestSceneModel);
}


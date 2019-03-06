#include "sceneModel.h"
#include "entity/point.h"
#include "../base/tr.h"

static const QString P_BACKGROUND_COLOR = T("Background Color");
static const QString P_FLAG1 = T("Flag Point 1");
static const QString P_FLAG2 = T("Flag Point 2");
static const QString P_SCROLLABLE = T("Scrollable");
static const QString P_START_POINT = T("Start Point");
static const QString P_FIGHT_MODE = T("Fight Mode");
static const QString P_NUMBER = T("Number");
static const QString P_SCREEN_LOCK = T("Screen Lock");
static const QString P_CAMERA = T("Camera");
static const QString P_AIR_STRIKE = T("Air Strike");
static const QString P_MUSIC1 = T("Music 1");
static const QString P_MUSIC2 = T("Music 2");

TSceneModel::TSceneModel(QObject *parent) :
    TPropertyObject(parent)
  , mAnimationsModel(new TAnimationsModel(this))
  , mAreasModel(new TAreasModel(this))
  , mBoxesModel(new TBoxesModel(this))
  , mDAreasModel(new TDAreasModel(this))
  , mEventsModel(new TEventsModel(this))
  , mLayersModel(new TLayersModel(this))
  , mPlatformsModel(new TPlatformsModel(this))
  , mRespawnsModel(new TRespawnsModel(this))
  , mTriggersModel(new TTriggersModel(this))
  , mWallsModel(new TWallsModel(this))
  , mGraphicsScene(new TGraphicsScene(this))
{
    initPropertySheet();

    mLayersModel->addLayer(tr("Default"));
}

TLayersModel *TSceneModel::layersModel() const
{
    return mLayersModel;
}

TGraphicsScene *TSceneModel::graphicsScene() const
{
    return mGraphicsScene;
}

void TSceneModel::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue)
{
    Q_UNUSED(oldValue);

    if(!item)
        return;

    PropertyID pid = item->propertyId();
    if(pid == PID_SCENE_BACKGROUND_COLOR) {
        mGraphicsScene->setBackgroundColor(item->value().value<QColor>());
    }
}

void TSceneModel::initPropertySheet()
{
    connect(mPropertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

    mPropertySheet->addProperty(PT_COLOR, P_BACKGROUND_COLOR, PID_SCENE_BACKGROUND_COLOR);
    mPropertySheet->addProperty(PT_VECTOR, P_FLAG1, PID_SCENE_FLAG1);
    mPropertySheet->addProperty(PT_VECTOR, P_FLAG2, PID_SCENE_FLAG2);
    mPropertySheet->addProperty(PT_BOOL, P_SCROLLABLE, PID_SCENE_SCROLLABLE);
    mPropertySheet->addProperty(PT_VECTOR, P_START_POINT, PID_SCENE_START_POINT);
    TPropertyItem *fightModeItem = mPropertySheet->addProperty(PT_ENUM, P_FIGHT_MODE, PID_SCENE_FIGHT_MODE);
    QStringList fightModeNames;
    fightModeNames.append("Death Match");
    fightModeNames.append("Hit Target");
    fightModeItem->addAttribute(PA_ENUM_NAMES, fightModeNames);
    mPropertySheet->addProperty(PT_INT, P_NUMBER, PID_SCENE_NUMBER);
    mPropertySheet->addProperty(PT_BOOL, P_SCREEN_LOCK, PID_SCENE_SCREEN_LOCK);
    mPropertySheet->addProperty(PT_RECT, P_CAMERA, PID_SCENE_CAMERA);
    mPropertySheet->addProperty(PT_BOOL, P_AIR_STRIKE, PID_SCENE_AIR_STRIKE);
    mPropertySheet->addProperty(PT_SOUND_ITEM, P_MUSIC1, PID_SCENE_MUSIC1);
    mPropertySheet->addProperty(PT_SOUND_ITEM, P_MUSIC2, PID_SCENE_MUSIC2);
}

void TSceneModel::saveToStream(QDataStream &stream) const
{

}

void TSceneModel::readFromStream(QDataStream &stream)
{
    mAreasModel->readFromStream(stream);
    mDAreasModel->readFromStream(stream);
    mPlatformsModel->readFromStream(stream);
    mBoxesModel->readFromStream(stream);
    mWallsModel->readFromStream(stream);

    int r, g, b;
    stream >> r;
    stream >> g;
    stream >> b;

    mLayersModel->readFromStream(stream);
    mRespawnsModel->readFromStream(stream);

    TPoint flag1, flag2;
    flag1.readFromStream(stream);
    flag2.readFromStream(stream);

    int scrollMap;
    stream >> scrollMap;

    mEventsModel->readFromStream(stream);
    mTriggersModel->readFromStream(stream);
    mAnimationsModel->readFromStream(stream);

    mPropertySheet->setValue(P_BACKGROUND_COLOR, QColor(r,g,b));
    mPropertySheet->setValue(P_FLAG1, flag1);
    mPropertySheet->setValue(P_FLAG2, flag2);
}

#include "sceneModel.h"

#include "areamodel.h"
#include "animationmodel.h"
#include "boxmodel.h"
#include "dareamodel.h"
#include "eventmodel.h"
#include "tilelayermodel.h"
#include "platmodel.h"
#include "respawnmodel.h"
#include "triggermodel.h"
#include "wallmodel.h"
#include "enemyfactorymodel.h"

#include "../property/propertyobject.h"
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

#define COLUMN_INDEX_NAME 0
#define COLUMN_INDEX_VISIBILITY 1
#define COLUMN_INDEX_LOCK 2

TSceneModel::TSceneModel(const TMap::Type &mapType, QObject *parent) :
    TBaseModel(TBaseModel::INVALID, parent)
  , mMapType(mapType)
  , mPropertyObject(new TPropertyObject(this))
  , mPropertySheet(mPropertyObject->propertySheet())
  , mTileLayerModel1(new TTileModel(this))
  , mTileLayerModel2(new TTileModel(this))
  , mTileLayerModel3(new TTileModel(this))
  , mAnimationModel(new TAnimationModel(this))
  , mAreasModel(new TAreaModel(this))
  , mBoxModel(new TBoxModel(this))
  , mDAreasModel(new TDAreaModel(this))
  , mEventsModel(new TEventModel(this))
  , mPlatformsModel(new TPlatModel(this))
  , mRespawnsModel(new TRespawnModel(this))
  , mTriggersModel(new TTriggerModel(this))
  , mWallsModel(new TWallModel(this))
  , mEnemyFactoryModel(new TEnemyFactoryModel(this))
  , mTileLayerModel4(new TTileModel(this))
  , mTileLayerModel5(new TTileModel(this))
  , mTileLayerModel6(new TTileModel(this))
  , mCurrentIndex(-1)
  , mFlagPointObject1(new TPointObject(this))
  , mFlagPointObject2(new TPointObject(this))
{
    setName(tr("Map Property"));

    mBaseModelList.append(mTileLayerModel1);
    mBaseModelList.append(mTileLayerModel2);
    mBaseModelList.append(mTileLayerModel3);
    //mBaseModelList.append(mAnimationModel);
    mBaseModelList.append(mAreasModel);
    mBaseModelList.append(mBoxModel);
    mBaseModelList.append(mDAreasModel);
    //mBaseModelList.append(mEventsModel);
    mBaseModelList.append(mPlatformsModel);
    mBaseModelList.append(mRespawnsModel);
    mBaseModelList.append(mTriggersModel);
    mBaseModelList.append(mWallsModel);
    mBaseModelList.append(mEnemyFactoryModel);
    mBaseModelList.append(mTileLayerModel4);
    mBaseModelList.append(mTileLayerModel5);
    mBaseModelList.append(mTileLayerModel6);
    mBaseModelList.append(this);
    mCurrentIndex = mBaseModelList.size() - 1;

    mTileLayerModel1->setName(tr("Background 1"));
    mTileLayerModel2->setName(tr("Background 2"));
    mTileLayerModel3->setName(tr("Background 3"));
    mTileLayerModel4->setName(tr("Foreground 1"));
    mTileLayerModel5->setName(tr("Foreground 2"));
    mTileLayerModel6->setName(tr("Foreground 3"));

    mTileLayerModelList.append(mTileLayerModel1);
    mTileLayerModelList.append(mTileLayerModel2);
    mTileLayerModelList.append(mTileLayerModel3);
    mTileLayerModelList.append(mTileLayerModel4);
    mTileLayerModelList.append(mTileLayerModel5);
    mTileLayerModelList.append(mTileLayerModel6);

    initPropertySheet();

    mFlagPointObject1->setTypeString(P_FLAG1);
    mFlagPointObject2->setTypeString(P_FLAG2);
}

TSceneModel::~TSceneModel()
{

}

QColor TSceneModel::getBackgroundColor() const
{
    TPropertyItem *item = mPropertySheet->get(P_BACKGROUND_COLOR);
    if(item)
        return item->value().value<QColor>();
    return QColor();
}

TPropertySheet *TSceneModel::propertySheet() const
{
    return mPropertySheet;
}

TBaseModelList TSceneModel::getBaseModelList() const
{
    return mBaseModelList;
}

TBaseModel *TSceneModel::getBaseModel(int index) const
{
    TBaseModel *baseModel = nullptr;
    if(index>=0 && index<mBaseModelList.size())
        baseModel = mBaseModelList.at(index);
    return baseModel;
}

int TSceneModel::getBaseModelIndex(TBaseModel *baseModel) const
{
    return mBaseModelList.indexOf(baseModel);
}

int TSceneModel::currentIndex() const
{
    return mCurrentIndex;
}

void TSceneModel::setCurrentIndex(int index)
{
    if(mCurrentIndex == index)
        return;

    mCurrentIndex = index;

    emit currentIndexChanged(index);
}

TBaseModel *TSceneModel::getCurrentModel() const
{
    TBaseModel *baseModel = nullptr;
    if(mCurrentIndex>=0 && mCurrentIndex<mBaseModelList.size())
        baseModel = mBaseModelList.at(mCurrentIndex);
    return baseModel;
}

int TSceneModel::getCurrentIndex() const
{
    return mCurrentIndex;
}

TTileModel *TSceneModel::getCurrentAsTileLayerModel() const
{
    TTileModel *tileLayerModel = nullptr;
    TBaseModel *baseModel = mBaseModelList.at(mCurrentIndex);
    if(baseModel && baseModel->isTile())
        tileLayerModel = dynamic_cast<TTileModel*>(baseModel);
    return tileLayerModel;
}

TBaseModel::Type TSceneModel::getCurretnModelType() const
{
    TBaseModel *baseModel = mBaseModelList.at(mCurrentIndex);
    return baseModel?baseModel->type():TBaseModel::INVALID;
}

bool TSceneModel::isCurrentTileLayerModel() const
{
    TBaseModel *m = getCurrentModel();
    return m && m->isTile();
}

TTile *TSceneModel::getTile(int tileset, int number) const
{
    if(tileset<0 || tileset>=mTileLayerModelList.size())
        return nullptr;

    TTileModel *tileLayerModel = mTileLayerModelList.at(tileset);
    if(!tileLayerModel)
        return nullptr;
    return tileLayerModel->getTile(number);
}

QRectF TSceneModel::getCamera() const
{
    return mPropertySheet->getValue(PID_SCENE_CAMERA).toRectF();
}

QRect TSceneModel::getCameraAsRect() const
{
    return mPropertySheet->getValue(PID_SCENE_CAMERA).toRect();
}

QPointF TSceneModel::getFlag1Point() const
{
    return mFlagPointObject1->pos();
}

QPointF TSceneModel::getFlag2Point() const
{
    return mFlagPointObject2->pos();
}

TPointObject *TSceneModel::getFlagPointObject2() const
{
    return mFlagPointObject2;
}

TMap::Type TSceneModel::getMapType() const
{
    return mMapType;
}

bool TSceneModel::isAdvMap() const
{
    return mMapType == TMap::ADV;
}

TPointObject *TSceneModel::getFlagPointObject1() const
{
    return mFlagPointObject1;
}

TAnimationModel *TSceneModel::getAnimationsModel() const
{
    return mAnimationModel;
}

TEnemyFactoryModel *TSceneModel::getEnemyFactoryModel() const
{
    return mEnemyFactoryModel;
}

TTileModel *TSceneModel::getTileLayerModel6() const
{
    return mTileLayerModel6;
}

TTileModel *TSceneModel::getTileLayerModel5() const
{
    return mTileLayerModel5;
}

TTileModel *TSceneModel::getTileLayerModel4() const
{
    return mTileLayerModel4;
}

TTileModel *TSceneModel::getTileLayerModel3() const
{
    return mTileLayerModel3;
}

TTileModel *TSceneModel::getTileLayerModel2() const
{
    return mTileLayerModel2;
}

TTileModel *TSceneModel::getTileLayerModel1() const
{
    return mTileLayerModel1;
}

TWallModel *TSceneModel::getWallsModel() const
{
    return mWallsModel;
}

TTriggerModel *TSceneModel::getTriggersModel() const
{
    return mTriggersModel;
}

TRespawnModel *TSceneModel::getRespawnsModel() const
{
    return mRespawnsModel;
}

TPlatModel *TSceneModel::getPlatformsModel() const
{
    return mPlatformsModel;
}

TEventModel *TSceneModel::getEventsModel() const
{
    return mEventsModel;
}

TDAreaModel *TSceneModel::getDAreasModel() const
{
    return mDAreasModel;
}

TBoxModel *TSceneModel::getBoxesModel() const
{
    return mBoxModel;
}

TAreaModel *TSceneModel::getAreasModel() const
{
    return mAreasModel;
}

void TSceneModel::initPropertySheet()
{
    TPropertyItem *propertyItem = mPropertySheet->addProperty(PT_COLOR, P_BACKGROUND_COLOR, PID_SCENE_BACKGROUND_COLOR);
    propertyItem->setValue(QColor(Qt::blue));

    mPropertySheet->addProperty(PT_BOOL, P_SCROLLABLE, PID_SCENE_SCROLLABLE);
    mPropertySheet->addProperty(PT_POINTF, P_START_POINT, PID_SCENE_START_POINT);

    if(mMapType != TMap::ADV) {
        TPropertyItem *fightModeItem = mPropertySheet->addProperty(PT_ENUM, P_FIGHT_MODE, PID_SCENE_FIGHT_MODE);
        QStringList fightModeNames;
        fightModeNames.append("Death Match");
        fightModeNames.append("Hit Target");
        fightModeNames.append("Catch Flag");
        fightModeItem->addAttribute(PA_ENUM_NAMES, fightModeNames);

        propertyItem = mFlagPointObject1->posPropertyItem();
        propertyItem->setName(P_FLAG1);
        mPropertySheet->addProperty(propertyItem);

        propertyItem = mFlagPointObject2->posPropertyItem();
        propertyItem->setName(P_FLAG2);
        mPropertySheet->addProperty(propertyItem);
    }

    mPropertySheet->addProperty(PT_INT, P_NUMBER, PID_SCENE_NUMBER);
    mPropertySheet->addProperty(PT_BOOL, P_SCREEN_LOCK, PID_SCENE_SCREEN_LOCK);
    mPropertySheet->addProperty(PT_RECT, P_CAMERA, PID_SCENE_CAMERA);
    mPropertySheet->addProperty(PT_BOOL, P_AIR_STRIKE, PID_SCENE_AIR_STRIKE);
    mPropertySheet->addProperty(PT_SOUND_ITEM, P_MUSIC1, PID_SCENE_MUSIC1);
    mPropertySheet->addProperty(PT_SOUND_ITEM, P_MUSIC2, PID_SCENE_MUSIC2);
}

void TSceneModel::bindPlat(TAreaPlat *areaPlat)
{
    int platIndex = areaPlat->platIndex();
    TPlat *plat = mPlatformsModel->getPlat(platIndex);
    if(!plat)
        platIndex = -1;
    areaPlat->setPlat(plat, platIndex);
}

void TSceneModel::saveToStream(QDataStream &stream) const
{
    mAreasModel->saveToStream(stream);
    mDAreasModel->saveToStream(stream);
    mPlatformsModel->saveToStream(stream);
    mBoxModel->saveToStream(stream);
    mWallsModel->saveToStream(stream);

    QColor backgroundColor = mPropertySheet->getValue(PID_SCENE_BACKGROUND_COLOR).value<QColor>();
    stream << backgroundColor.red();
    stream << backgroundColor.green();
    stream << backgroundColor.blue();

    mTileLayerModel1->saveToStream(stream);
    mTileLayerModel2->saveToStream(stream);
    mTileLayerModel3->saveToStream(stream);
    mTileLayerModel4->saveToStream(stream);
    mTileLayerModel5->saveToStream(stream);
    mTileLayerModel6->saveToStream(stream);

    mRespawnsModel->saveToStream(stream);

    stream << mPropertySheet->getValue(PID_SCENE_FLAG1).toPoint();
    stream << mPropertySheet->getValue(PID_SCENE_FLAG2).toPoint();
    stream << mPropertySheet->getValue(PID_SCENE_SCROLLABLE).toInt();

    mEventsModel->saveToStream(stream);
    mTriggersModel->saveToStream(stream);

    for(int i=0;i<5;i++) {
        stream << mNextMap[i];
    }

    int vsMode = 0;
    int var4 = 0;
    int var5 = 0;
    int var6 = 0;
    int var7 = 0;
    int var8 = 0;
    int var9 = 0;
    int var10 = 0;
    int stri1 = 0;
    int stri2 = 0;
    int stri3 = 0;
    QRect cameraRect = mPropertySheet->getValue(PID_SCENE_CAMERA).toRect();
    stream << mPropertySheet->getValue(PID_SCENE_START_POINT).toPoint();
    stream << mPropertySheet->getValue(PID_SCENE_FIGHT_MODE).toInt();
    stream << mPropertySheet->getValue(PID_SCENE_NUMBER).toInt();;
    stream << mPropertySheet->getValue(PID_SCENE_SCREEN_LOCK).toInt();
    stream << vsMode;
    stream << cameraRect.bottom();
    stream << cameraRect.top();
    stream << mPropertySheet->getValue(PID_SCENE_AIR_STRIKE).toInt();
    stream << var4;
    stream << var5;
    stream << var6;
    stream << var7;
    stream << var8;
    stream << var9;
    stream << var10;
    stream << stri1;
    stream << stri2;
    stream << stri3;
    stream << cameraRect.left();
    stream << cameraRect.right();
    stream << mPropertySheet->getValue(PID_SCENE_MUSIC1).toInt();
    stream << mPropertySheet->getValue(PID_SCENE_MUSIC2).toInt();

    mAnimationModel->saveToStream(stream);
    mEnemyFactoryModel->saveToStream(stream);
}

void TSceneModel::readFromStream(QDataStream &stream)
{
    mAreasModel->readFromStream(stream);
    mDAreasModel->readFromStream(stream);
    mPlatformsModel->readFromStream(stream);

    // Set binding plat into area
    for(TArea *area : mAreasModel->areaList()) {
        bindPlat(area);
    }
    for(TDArea *dArea : mDAreasModel->dAreaList()) {
        bindPlat(dArea);
    }

    mBoxModel->readFromStream(stream);
    mWallsModel->readFromStream(stream);

    int r, g, b;
    stream >> r;
    stream >> g;
    stream >> b;

    mTileLayerModel1->readFromStream(stream);
    mTileLayerModel2->readFromStream(stream);
    mTileLayerModel3->readFromStream(stream);
    mTileLayerModel4->readFromStream(stream);
    mTileLayerModel5->readFromStream(stream);
    mTileLayerModel6->readFromStream(stream);

    mRespawnsModel->readFromStream(stream);

    mFlagPointObject1->readFromStream(stream);
    mFlagPointObject2->readFromStream(stream);

    int scrollMap;
    stream >> scrollMap;

    mEventsModel->readFromStream(stream);
    mTriggersModel->readFromStream(stream);

    for(int i=0;i<5;i++) {
        int temp = 0;
        stream >> temp;
        mNextMap[i] = temp;
    }

    int xScrStart;
    int yScrStart;
    int fightMode;
    int mapNumber;
    int scrLock;
    int vsMode;
    int yScrCameraLimit;
    int uScrLimit;
    int noAirStrike;
    int var4;
    int var5;
    int var6;
    int var7;
    int var8;
    int var9;
    int var10;
    int stri1;
    int stri2;
    int stri3;
    int lScrLimit;
    int rScrLimit;
    int music1;
    int music2;
    stream >> xScrStart;
    stream >> yScrStart;
    stream >> fightMode;
    stream >> mapNumber;
    stream >> scrLock;
    stream >> vsMode;
    stream >> yScrCameraLimit;
    stream >> uScrLimit;
    stream >> noAirStrike;
    stream >> var4;
    stream >> var5;
    stream >> var6;
    stream >> var7;
    stream >> var8;
    stream >> var9;
    stream >> var10;
    stream >> stri1;
    stream >> stri2;
    stream >> stri3;
    stream >> lScrLimit;
    stream >> rScrLimit;
    stream >> music1;
    stream >> music2;

    mAnimationModel->readFromStream(stream);

    // Process animation
    for(TFrameModel *frameModel : mAnimationModel->frameModelList()) {
        TAnimation *animation = frameModel->animation();
        if(!animation)
            continue;

        int tileLayer = animation->getTileLayer();
        if(tileLayer>=0 && tileLayer<mTileLayerModelList.size()) {
            animation->setTile(getTile(tileLayer, animation->getTileNumber()));
        }

        for(TFrame *frame : animation->frameList()) {
            tileLayer = frame->getTileLayer();
            if(tileLayer>=0 && tileLayer<mTileLayerModelList.size()) {
                frame->setTile(getTile(tileLayer, frame->getTileNumber()));
            }
        }
    }

    mEnemyFactoryModel->readFromStream(stream);

    mPropertySheet->setValue(PID_SCENE_BACKGROUND_COLOR, QColor(r,g,b));
    mPropertySheet->setValue(PID_SCENE_START_POINT, QPoint(xScrStart, yScrStart));
    mPropertySheet->setValue(PID_SCENE_FIGHT_MODE, fightMode);
    mPropertySheet->setValue(PID_SCENE_SCREEN_LOCK, scrLock);
    mPropertySheet->setValue(PID_SCENE_CAMERA, QRect(QPoint(lScrLimit,uScrLimit), QPoint(rScrLimit, yScrCameraLimit)));
    mPropertySheet->setValue(PID_SCENE_SCROLLABLE, scrollMap);
    mPropertySheet->setValue(PID_SCENE_NUMBER, mapNumber);
    mPropertySheet->setValue(PID_SCENE_AIR_STRIKE, noAirStrike);
    mPropertySheet->setValue(PID_SCENE_MUSIC1, music1);
    mPropertySheet->setValue(PID_SCENE_MUSIC2, music2);
    mPropertySheet->setValue(PID_SCENE_FLAG1, mFlagPointObject1->pos(), false);
    mPropertySheet->setValue(PID_SCENE_FLAG2, mFlagPointObject2->pos(), false);
}

int TSceneModel::columnCount(const QModelIndex &) const
{
    return 3;
}

int TSceneModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
        return mBaseModelList.size();
    }
    return 0;
}

QVariant TSceneModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row<0 || row>=mBaseModelList.size()) {
        if(role==Qt::DisplayRole) {
            return "Unimplemented";
        }
        return QVariant();
    }

    TBaseModel *baseModel = mBaseModelList.at(row);
    int column = index.column();
    if(role==Qt::DisplayRole) {
        if(column==COLUMN_INDEX_NAME)
            return baseModel->name();
    } else if(role == Qt::DecorationRole) {
        if(column==COLUMN_INDEX_NAME)
            return baseModel->icon();
    } else if(role == Qt::CheckStateRole) {
        if (column == COLUMN_INDEX_VISIBILITY)
          return baseModel->visible() ? Qt::Checked : Qt::Unchecked;
        if (column == COLUMN_INDEX_LOCK)
          return baseModel->locked() ? Qt::Checked : Qt::Unchecked;
    }
    return TBaseModel::data(index, role);
}

bool TSceneModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row();
    if(row<0 || row>=mBaseModelList.size())
        return false;

    if (role == Qt::CheckStateRole) {
        int column = index.column();
        TBaseModel *baseModel = mBaseModelList.at(row);
        if (column == COLUMN_INDEX_VISIBILITY) {
            Qt::CheckState c = static_cast<Qt::CheckState>(value.toInt());
            const bool visible = (c == Qt::Checked);
            baseModel->setVisibility(visible);
        }
        if (column == COLUMN_INDEX_LOCK) {
            Qt::CheckState c = static_cast<Qt::CheckState>(value.toInt());
            const bool locked = (c == Qt::Checked);
            baseModel->setLocked(locked);
        }
        return true;
    }

    return false;
}

/**
 * Makes sure the items are checkable and names editable.
 */
Qt::ItemFlags TSceneModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags rc = QAbstractItemModel::flags(index);

    int column = index.column();
    if (column==COLUMN_INDEX_VISIBILITY || column==COLUMN_INDEX_LOCK)
        rc |= Qt::ItemIsUserCheckable;

    return rc;
}

/**
 * Returns the headers for the table.
 */
QVariant TSceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role==Qt::DisplayRole && orientation==Qt::Horizontal) {
        switch (section) {
        case COLUMN_INDEX_NAME: return tr("Name");
        case COLUMN_INDEX_VISIBILITY: return tr("Visible");
        case COLUMN_INDEX_LOCK: return tr("Locked");
        }
    }
    return QVariant();
}

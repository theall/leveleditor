#include "sceneModel.h"
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

TSceneModel::TSceneModel(QObject *parent) :
    TBaseModel(TBaseModel::INVALID, parent)
  , mPropertyObject(new TPropertyObject(this))
  , mPropertySheet(mPropertyObject->propertySheet())
  , mTileLayerModel1(new TTileLayerModel(this))
  , mTileLayerModel2(new TTileLayerModel(this))
  , mTileLayerModel3(new TTileLayerModel(this))
  , mAnimationsModel(new TAnimationsModel(this))
  , mAreasModel(new TAreasModel(this))
  , mBoxesModel(new TBoxesModel(this))
  , mDAreasModel(new TDAreasModel(this))
  , mEventsModel(new TEventsModel(this))
  , mPlatformsModel(new TPlatformsModel(this))
  , mRespawnsModel(new TRespawnsModel(this))
  , mTriggersModel(new TTriggersModel(this))
  , mWallsModel(new TWallsModel(this))
  , mEnemyFactoryModel(new TEnemyFactoryModel(this))
  , mTileLayerModel4(new TTileLayerModel(this))
  , mTileLayerModel5(new TTileLayerModel(this))
  , mTileLayerModel6(new TTileLayerModel(this))
  , mCurrentIndex(-1)
{
    setName(tr("SceneModel"));

    mBaseModelList.append(mTileLayerModel1);
    mBaseModelList.append(mTileLayerModel2);
    mBaseModelList.append(mTileLayerModel3);
    mBaseModelList.append(mAnimationsModel);
    mBaseModelList.append(mAreasModel);
    mBaseModelList.append(mBoxesModel);
    mBaseModelList.append(mDAreasModel);
    mBaseModelList.append(mEventsModel);
    mBaseModelList.append(mPlatformsModel);
    mBaseModelList.append(mRespawnsModel);
    mBaseModelList.append(mTriggersModel);
    mBaseModelList.append(mWallsModel);
    mBaseModelList.append(mEnemyFactoryModel);
    mBaseModelList.append(mTileLayerModel4);
    mBaseModelList.append(mTileLayerModel5);
    mBaseModelList.append(mTileLayerModel6);
    mCurrentIndex = mBaseModelList.size() - 1;

    mTileLayerModel1->setName(tr("Background 1"));
    mTileLayerModel2->setName(tr("Background 2"));
    mTileLayerModel3->setName(tr("Background 3"));
    mTileLayerModel4->setName(tr("Foreground 1"));
    mTileLayerModel5->setName(tr("Foreground 2"));
    mTileLayerModel6->setName(tr("Foreground 3"));
    initPropertySheet();
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

TTileLayerModel *TSceneModel::getCurrentAsTileLayerModel() const
{
    TTileLayerModel *tileLayerModel = nullptr;
    TBaseModel *baseModel = mBaseModelList.at(mCurrentIndex);
    if(baseModel && baseModel->isTile())
        tileLayerModel = dynamic_cast<TTileLayerModel*>(baseModel);
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

TEnemyFactoryModel *TSceneModel::getEnemyFactoryModel() const
{
    return mEnemyFactoryModel;
}

TTileLayerModel *TSceneModel::getTileLayerModel6() const
{
    return mTileLayerModel6;
}

TTileLayerModel *TSceneModel::getTileLayerModel5() const
{
    return mTileLayerModel5;
}

TTileLayerModel *TSceneModel::getTileLayerModel4() const
{
    return mTileLayerModel4;
}

TTileLayerModel *TSceneModel::getTileLayerModel3() const
{
    return mTileLayerModel3;
}

TTileLayerModel *TSceneModel::getTileLayerModel2() const
{
    return mTileLayerModel2;
}

TTileLayerModel *TSceneModel::getTileLayerModel1() const
{
    return mTileLayerModel1;
}

TWallsModel *TSceneModel::getWallsModel() const
{
    return mWallsModel;
}

TTriggersModel *TSceneModel::getTriggersModel() const
{
    return mTriggersModel;
}

TRespawnsModel *TSceneModel::getRespawnsModel() const
{
    return mRespawnsModel;
}

TPlatformsModel *TSceneModel::getPlatformsModel() const
{
    return mPlatformsModel;
}

TEventsModel *TSceneModel::getEventsModel() const
{
    return mEventsModel;
}

TDAreasModel *TSceneModel::getDAreasModel() const
{
    return mDAreasModel;
}

TBoxesModel *TSceneModel::getBoxesModel() const
{
    return mBoxesModel;
}

TAreasModel *TSceneModel::getAreasModel() const
{
    return mAreasModel;
}

void TSceneModel::initPropertySheet()
{
    TPropertyItem *propertyItem = mPropertySheet->addProperty(PT_COLOR, P_BACKGROUND_COLOR, PID_SCENE_BACKGROUND_COLOR);
    propertyItem->setValue(QColor(Qt::blue));

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
    mAreasModel->saveToStream(stream);
    mDAreasModel->saveToStream(stream);
    mPlatformsModel->saveToStream(stream);
    mBoxesModel->saveToStream(stream);
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
    qint8 stri1 = 0;
    qint8 stri2 = 0;
    qint8 stri3 = 0;
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

    mAnimationsModel->saveToStream(stream);
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

    mTileLayerModel1->readFromStream(stream);
    mTileLayerModel2->readFromStream(stream);
    mTileLayerModel3->readFromStream(stream);
    mTileLayerModel4->readFromStream(stream);
    mTileLayerModel5->readFromStream(stream);
    mTileLayerModel6->readFromStream(stream);

    mRespawnsModel->readFromStream(stream);

    QPoint flag1, flag2;
    stream >> flag1;
    stream >> flag2;

    int scrollMap;
    stream >> scrollMap;

    mEventsModel->readFromStream(stream);
    mTriggersModel->readFromStream(stream);

    for(int i=0;i<5;i++) {
        stream >> mNextMap[i];
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
    qint8 stri1;
    qint8 stri2;
    qint8 stri3;
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

    mAnimationsModel->readFromStream(stream);

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

    mPropertySheet->setValue(PID_SCENE_FLAG1, flag1);
    mPropertySheet->setValue(PID_SCENE_FLAG2, flag2);
}

int TSceneModel::rowCount(const QModelIndex &) const
{
    return mBaseModelList.size();
}

QVariant TSceneModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row<0 || row>=mBaseModelList.size())
        return QVariant();

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

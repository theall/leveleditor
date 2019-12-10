#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QColor>
#include <QRectF>

#include "basemodel.h"

class TAreaModel;
class TBoxModel;
class TDAreaModel;
class TEventModel;
class TPlatModel;
class TRespawnModel;
class TTriggerModel;
class TWallModel;
class TEnemyFactoryModel;
class TTileModel;
class TTileModel;
class TTileModel;
class TTileModel;
class TTileModel;
class TTileModel;
class TAnimationModel;
class TPointObject;
class TPropertySheet;
class TTile;

class TSceneModel : public TBaseModel
{
    Q_OBJECT

public:
    explicit TSceneModel(QObject *parent = nullptr);
    ~TSceneModel();

    TAreaModel *getAreasModel() const;
    TBoxModel *getBoxesModel() const;
    TDAreaModel *getDAreasModel() const;
    TEventModel *getEventsModel() const;
    TPlatModel *getPlatformsModel() const;
    TRespawnModel *getRespawnsModel() const;
    TTriggerModel *getTriggersModel() const;
    TWallModel *getWallsModel() const;
    TEnemyFactoryModel *getEnemyFactoryModel() const;
    TTileModel *getTileLayerModel1() const;
    TTileModel *getTileLayerModel2() const;
    TTileModel *getTileLayerModel3() const;
    TTileModel *getTileLayerModel4() const;
    TTileModel *getTileLayerModel5() const;
    TTileModel *getTileLayerModel6() const;
    TAnimationModel *getAnimationsModel() const;

    QColor getBackgroundColor() const;
    TPropertySheet *propertySheet() const;
    TBaseModelList getBaseModelList() const;
    TBaseModel *getBaseModel(int index) const;

    int currentIndex() const;
    void setCurrentIndex(int index);

    TBaseModel *getCurrentModel() const;
    int getCurrentIndex() const;

    TTileModel *getCurrentAsTileLayerModel() const;
    TBaseModel::Type getCurretnModelType() const;

    bool isCurrentTileLayerModel() const;
    TTile *getTile(int tileset, int number) const;

    QRectF getCamera() const;
    QRect getCameraAsRect() const;
    QPointF getFlag1Point() const;
    QPointF getFlag2Point() const;

    TPointObject *getFlagPointObject1() const;
    TPointObject *getFlagPointObject2() const;

signals:
    void currentIndexChanged(int index);

private:
    int mNextMap[5];

    // As TSceneModel can not extra extend TPropertyObject, this variable is crated to expose property sheet.
    TPropertyObject *mPropertyObject;
    TPropertySheet *mPropertySheet;

    TTileModel *mTileLayerModel1;
    TTileModel *mTileLayerModel2;
    TTileModel *mTileLayerModel3;
    TAnimationModel *mAnimationModel;
    TAreaModel *mAreasModel;
    TBoxModel *mBoxModel;
    TDAreaModel *mDAreasModel;
    TEventModel *mEventsModel;
    TPlatModel *mPlatformsModel;
    TRespawnModel *mRespawnsModel;
    TTriggerModel *mTriggersModel;
    TWallModel *mWallsModel;
    TEnemyFactoryModel *mEnemyFactoryModel;
    TTileModel *mTileLayerModel4;
    TTileModel *mTileLayerModel5;
    TTileModel *mTileLayerModel6;
    TBaseModelList mBaseModelList;
    QList<TTileModel*> mTileLayerModelList;
    int mCurrentIndex;
    TPointObject *mFlagPointObject1;
    TPointObject *mFlagPointObject2;

    void initPropertySheet();

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // SCENEMODEL_H

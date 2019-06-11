#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include "basemodel.h"
#include "animationmodel.h"
#include "areamodel.h"
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

#include <QColor>

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
    TTileLayerModel *getTileLayerModel1() const;
    TTileLayerModel *getTileLayerModel2() const;
    TTileLayerModel *getTileLayerModel3() const;
    TTileLayerModel *getTileLayerModel4() const;
    TTileLayerModel *getTileLayerModel5() const;
    TTileLayerModel *getTileLayerModel6() const;

    QColor getBackgroundColor() const;
    TPropertySheet *propertySheet() const;
    TBaseModelList getBaseModelList() const;
    TBaseModel *getBaseModel(int index) const;

    int currentIndex() const;
    void setCurrentIndex(int index);

    TBaseModel *getCurrentModel() const;
    int getCurrentIndex() const;

    TTileLayerModel *getCurrentAsTileLayerModel() const;
    TBaseModel::Type getCurretnModelType() const;

    bool isCurrentTileLayerModel() const;
    TTile *getTile(int tileset, int number) const;

signals:
    void currentIndexChanged(int index);

private:
    int mNextMap[5];

    // As TSceneModel can not extra extend TPropertyObject, this variable is crated to expose property sheet.
    TPropertyObject *mPropertyObject;
    TPropertySheet *mPropertySheet;

    TTileLayerModel *mTileLayerModel1;
    TTileLayerModel *mTileLayerModel2;
    TTileLayerModel *mTileLayerModel3;
    TAnimationModel *mAnimationsModel;
    TAreaModel *mAreasModel;
    TBoxModel *mBoxesModel;
    TDAreaModel *mDAreasModel;
    TEventModel *mEventsModel;
    TPlatModel *mPlatformsModel;
    TRespawnModel *mRespawnsModel;
    TTriggerModel *mTriggersModel;
    TWallModel *mWallsModel;
    TEnemyFactoryModel *mEnemyFactoryModel;
    TTileLayerModel *mTileLayerModel4;
    TTileLayerModel *mTileLayerModel5;
    TTileLayerModel *mTileLayerModel6;
    TBaseModelList mBaseModelList;
    QList<TTileLayerModel*> mTileLayerModelList;
    int mCurrentIndex;

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

#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include "basemodel.h"
#include "animationsmodel.h"
#include "areasmodel.h"
#include "boxesmodel.h"
#include "dareasmodel.h"
#include "eventsmodel.h"
#include "tilelayermodel.h"
#include "platformsmodel.h"
#include "respawnsmodel.h"
#include "triggersmodel.h"
#include "wallsmodel.h"
#include "../property/propertyobject.h"

#include <QColor>

class TSceneModel : public TBaseModel
{
    Q_OBJECT

public:
    TSceneModel(QObject *parent = nullptr);

    TAreasModel *getAreasModel() const;
    TBoxesModel *getBoxesModel() const;
    TDAreasModel *getDAreasModel() const;
    TEventsModel *getEventsModel() const;
    TPlatformsModel *getPlatformsModel() const;
    TRespawnsModel *getRespawnsModel() const;
    TTriggersModel *getTriggersModel() const;
    TWallsModel *getWallsModel() const;
    TTileLayerModel *getTileLayerModel1() const;
    TTileLayerModel *getTileLayerModel2() const;
    TTileLayerModel *getTileLayerModel3() const;
    TTileLayerModel *getTileLayerModel4() const;
    TTileLayerModel *getTileLayerModel5() const;
    TTileLayerModel *getTileLayerModel6() const;

    QColor getBackgroundColor() const;
    TPropertySheet *propertySheet() const;

private:
    int mNextMap[5];
    TPropertyObject *mPropertyObject;
    TPropertySheet *mPropertySheet;

    TTileLayerModel *mTileLayerModel1;
    TTileLayerModel *mTileLayerModel2;
    TTileLayerModel *mTileLayerModel3;
    TAnimationsModel *mAnimationsModel;
    TAreasModel *mAreasModel;
    TBoxesModel *mBoxesModel;
    TDAreasModel *mDAreasModel;
    TEventsModel *mEventsModel;
    TPlatformsModel *mPlatformsModel;
    TRespawnsModel *mRespawnsModel;
    TTriggersModel *mTriggersModel;
    TWallsModel *mWallsModel;
    TTileLayerModel *mTileLayerModel4;
    TTileLayerModel *mTileLayerModel5;
    TTileLayerModel *mTileLayerModel6;
    TBaseModelList mBaseModelList;

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

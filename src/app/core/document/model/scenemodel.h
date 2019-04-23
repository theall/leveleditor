#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include "animationsmodel.h"
#include "areasmodel.h"
#include "boxesmodel.h"
#include "dareasmodel.h"
#include "eventsmodel.h"
#include "layersmodel.h"
#include "platformsmodel.h"
#include "respawnsmodel.h"
#include "triggersmodel.h"
#include "wallsmodel.h"

#include <QColor>

class TSceneModel : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TSceneModel(QObject *parent = nullptr);

    TLayersModel *layersModel() const;
    TAreasModel *getAreasModel() const;
    TBoxesModel *getBoxesModel() const;
    TDAreasModel *getDAreasModel() const;
    TEventsModel *getEventsModel() const;
    TLayersModel *getLayersModel() const;
    TPlatformsModel *getPlatformsModel() const;
    TRespawnsModel *getRespawnsModel() const;
    TTriggersModel *getTriggersModel() const;
    TWallsModel *getWallsModel() const;

    QColor getBackgroundColor() const;

private:
    TAnimationsModel *mAnimationsModel;
    TAreasModel *mAreasModel;
    TBoxesModel *mBoxesModel;
    TDAreasModel *mDAreasModel;
    TEventsModel *mEventsModel;
    TLayersModel *mLayersModel;
    TPlatformsModel *mPlatformsModel;
    TRespawnsModel *mRespawnsModel;
    TTriggersModel *mTriggersModel;
    TWallsModel *mWallsModel;

    void initPropertySheet();

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};

#endif // SCENEMODEL_H

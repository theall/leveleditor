#ifndef TCLIPBOARD_H
#define TCLIPBOARD_H

#include <QList>
#include "../core/document/graphics/layeritem/objectitem/objectitem.h"
#include "../core/document/model/entity/object.h"
#include "../core/document/model/entity/animation.h"
#include "../core/document/model/entity/area.h"
#include "../core/document/model/entity/areaplat.h"
#include "../core/document/model/entity/box.h"
#include "../core/document/model/entity/darea.h"
#include "../core/document/model/entity/enemy.h"
#include "../core/document/model/entity/enemyfactory.h"
#include "../core/document/model/entity/frame.h"
#include "../core/document/model/entity/plat.h"
#include "../core/document/model/entity/point.h"
#include "../core/document/model/entity/wall.h"
#include "../core/document/model/entity/tile.h"
#include "../core/document/model/entity/trigger.h"
#include "../core/document/model/basemodel.h"
#include "../core/document/model/areamodel.h"
#include "../core/document/model/boxmodel.h"
#include "../core/document/model/dareamodel.h"
#include "../core/document/model/enemymodel.h"
#include "../core/document/model/enemyfactorymodel.h"
#include "../core/document/model/platmodel.h"
#include "../core/document/model/triggermodel.h"
#include "../core/document/model/tilelayermodel.h"
#include "../core/assets/assetsmanager.h"

class TClipboard : public QObject
{
    DECL_SINGLE_INSTANCE(TClipboard)

public:
    ~TClipboard();

    void setData(const TObjectItemList &objectItemList, TBaseModel *baseModel);
    bool whetherObject(const TObject::Type &type) const;
    bool isEmpty();
    TObject::Type getType() const;
    TObjectList getObjectList() const;
    QList<QPointF> getPointList() const;

    template<class T>
    QList<T*> getData() const
    {
        QList<T*> objectList;
        for(QByteArray byteArray : mDataList)
        {
            T *t = new T();
            QDataStream stream(&byteArray, QIODevice::WriteOnly);
            ((TObject*)t)->readFromStream(stream);
            objectList.append(t);
        }
        return objectList;
    }

private:
    TClipboard(QObject *parent = nullptr);

    void setIndexList(const TObjectList &objectList, TBaseModel *baseModel);


    QList<int> mIndexList;
    TObject::Type mType;
    QList<QByteArray> mDataList;
    QList<QPointF> mPointList;
};
#endif // TCLIPBOARD_H

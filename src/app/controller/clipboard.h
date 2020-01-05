#ifndef TCLIPBOARD_H
#define TCLIPBOARD_H

#include <QList>
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
#include "../core/assets/assetsmanager.h"

class TClipboard : public QObject
{
    DECL_SINGLE_INSTANCE(TClipboard)

public:
    ~TClipboard();

    void setRectF(const QRectF &rectF);
    QList<QPointF> getPointFList() const;
    void setPointFList(const QList<QPointF> &pointFList);
    void setData(const TObject::Type &type, const TObjectList &objectList);
    bool whetherObject(const TObject::Type &type) const;
    bool isEmpty();
    TObject::Type getType() const;
    TObjectList getObjectList() const;

    template<class T>
    QList<T*> getData(QPointF pos) const
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

    TObject::Type mType;
    QList<QByteArray> mDataList;
    QList<QPointF> mPointFList;
    QRectF mRectF;
};
#endif // TCLIPBOARD_H

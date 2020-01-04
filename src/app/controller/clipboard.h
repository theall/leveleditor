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

    void setData(const TObject::Type &type, const TObjectList &objectList);
    bool hasObject(const TObject::Type &type) const;
    TObjectList getObjectList() const;

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

    TObject::Type mType;
    QList<QByteArray> mDataList;
};
#endif // TCLIPBOARD_H

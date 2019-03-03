#include "area.h"

#include <QCoreApplication>

const QString g_objectName= QCoreApplication::translate("Area", "Area");
const QString g_areaTypeString[TArea::TypeCount] = {
    QCoreApplication::translate("Area", "collide"),
    QCoreApplication::translate("Area", "attack"),
    QCoreApplication::translate("Area", "undertake"),
    QCoreApplication::translate("Area", "terrian")
};

TArea::TArea(Type type, QObject *parent) :
    TShapeObject(parent)
  , mType(type)
{
    setObjectName(g_objectName);
}

TArea::TArea(const QRectF &rect, Type type, QObject *parent) :
    TShapeObject(rect, parent)
  , mType(type)
{
    setObjectName(g_objectName);
}

TArea::TArea(qreal x, qreal y, qreal w, qreal h, Type type, QObject *parent) :
    TShapeObject(x, y, w, h, parent)
  , mType(type)
{
    setObjectName(g_objectName);
}

TArea::Type TArea::type() const
{
    return mType;
}

void TArea::setType(const Type &type)
{
    mType = type;
}

void TArea::initPropertySheet()
{

}

TAreaManager::TAreaManager(const TArea::Type &areaType, QObject *parent) :
    QObject(parent)
  , mAreaType(areaType)
{

}

TAreaManager::~TAreaManager()
{

}

QJsonArray TAreaManager::toJson()
{
    QJsonArray jsonArray;
    for(TArea *area : mAreaList)
    {
        QJsonArray array;
        QRectF rt = area->bounds();
        array.append(rt.left());
        array.append(rt.top());
        array.append(rt.width());
        array.append(rt.height());
        jsonArray.append(array);
    }

    return jsonArray;
}

QList<QRectF> TAreaManager::toRectList() const
{
    QList<QRectF> rectList;
    for(TArea *area : mAreaList)
    {
        rectList.append(area->bounds());
    }
    return rectList;
}

void TAreaManager::add(qreal x, qreal y, qreal width, qreal height)
{
    add(new TArea(x, y, width, height, mAreaType, this));
}

void TAreaManager::add(TArea *area)
{
    TAreaList areaList;
    areaList.append(area);
    add(areaList);
}

void TAreaManager::add(const TAreaList &areaList)
{
    if(areaList.size() > 0)
    {
        mAreaList += areaList;
        emit areasAdded(areaList);
        emit areasChanged();
    }
}

void TAreaManager::remove(int index)
{
    if(index>=0 && index<mAreaList.size())
    {
        remove(mAreaList.at(index));
    }
}

void TAreaManager::remove(TArea *area)
{
    if(mAreaList.removeOne(area))
    {
        TAreaList areaList;
        areaList.append(area);
        remove(areaList);
    }
}

TAreaList TAreaManager::remove(const TAreaList &areaList)
{
    TAreaList areaListRemoved;
    for(TArea *area : areaList)
    {
        if(mAreaList.removeOne(area))
            areaListRemoved.append(area);
    }
    if(areaListRemoved.size() > 0) {
        emit areasRemoved(areaListRemoved);
        emit areasChanged();
    }
    return areaListRemoved;
}

void TAreaManager::move(const TAreaList &areaList, const QPointF &distance)
{
    TAreaList areaListMoved;
    for(TArea *area : areaList)
    {
        if(mAreaList.contains(area))
            areaListMoved.append(area);
    }
    for(TArea *area : areaListMoved)
    {
        area->setPosition(area->position()+distance);
    }
}

bool TAreaManager::isEmpty() const
{
    return mAreaList.isEmpty();
}

void TAreaManager::clear()
{
    mAreaList.clear();
}

void TAreaManager::setRectList(const QList<QRectF> &rects)
{
    mAreaList.clear();
    for(QRectF r : rects)
    {
        mAreaList.append(new TArea(r, mAreaType, this));
    }
    if(mAreaList.size() > 0) {
        emit areasAdded(mAreaList);
        emit areasChanged();
    }
}

TAreaList TAreaManager::areaList() const
{
    return mAreaList;
}

TArea::Type TAreaManager::areaType() const
{
    return mAreaType;
}

QString TAreaManager::areaTypeString() const
{
    return g_areaTypeString[mAreaType];
}

QDataStream &operator<<(QDataStream &out, const TAreaManager &areaManager)
{
    out << areaManager.toRectList();
    return out;
}

QDataStream &operator>>(QDataStream &in, TAreaManager &areaManager)
{
    QList<QRectF> rectList;
    in >> rectList;
    areaManager.setRectList(rectList);
    return in;
}

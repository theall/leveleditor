#include "area.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_RECT = T("Area");
static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_DANGER_AREA = T("Danger Area");
static const QString P_EDGES = T("Edges");
static const QString P_MOVE_BY = T("Move By");

TArea::TArea(QObject *parent) :
    TObject(TObject::AREA, parent, false)
{
    initPropertySheet();
}

void TArea::saveToStream(QDataStream &stream) const
{

}

void TArea::readFromStream(QDataStream &stream)
{
    int x,y,w,h,fleeDir,dangerArea,edges,moveBy;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    stream >> fleeDir;
    stream >> dangerArea;
    stream >> edges;
    stream >> moveBy;
    mPropertySheet->setValue(P_RECT, QRect(x,y,w,h));
    mPropertySheet->setValue(P_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(P_DANGER_AREA, dangerArea);
    mPropertySheet->setValue(P_EDGES, edges);
    mPropertySheet->setValue(P_MOVE_BY, moveBy);
}

void TArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_RECT, P_RECT, PID_AREA_RECT);
    mPropertySheet->addProperty(PT_INT, P_FLEE_DIR, PID_AREA_FLEE_DIR);
    mPropertySheet->addProperty(PT_INT, P_DANGER_AREA, PID_AREA_DANGER_AREA);
    mPropertySheet->addProperty(PT_INT, P_EDGES, PID_AREA_EDGES);
    mPropertySheet->addProperty(PT_INT, P_MOVE_BY, PID_AREA_MOVE_BY);
}

QString TArea::typeString() const
{
    return T("Area");
}

bool TArea::isCongener(TObject *object) const
{
    return static_cast<TArea*>(object);
}

QRectF TArea::rect() const
{
    return mPropertySheet->getValue(PID_AREA_RECT).toRectF();
}

QPointF TArea::pos() const
{
    return mPropertySheet->getValue(PID_AREA_RECT).toRectF().topLeft();
}

void TArea::setPos(const QPointF &pos)
{
    QRectF currentRect = mPropertySheet->getValue(PID_AREA_RECT).toRectF();
    QPointF currentPos = currentRect.topLeft();
    if(currentPos == pos)
        return;

    currentRect.moveTo(pos);
    mPropertySheet->setValue(PID_AREA_RECT, currentRect);
}

QSize TArea::size() const
{
    return mPropertySheet->getValue(PID_AREA_RECT).toRectF().size().toSize();
}

void TArea::setSize(const QSize &size)
{
    QRectF currentRect = mPropertySheet->getValue(PID_AREA_RECT).toRectF();
    QSize currentSize = currentRect.size().toSize();
    if(currentSize == size)
        return;

    currentRect.setSize(currentSize);
    mPropertySheet->setValue(PID_AREA_RECT, currentRect);
}

void TArea::setRect(const QRectF &rect)
{
    QRectF currentRect = mPropertySheet->getValue(PID_AREA_RECT).toRectF();
    if(currentRect == rect)
        return;

    mPropertySheet->setValue(PID_AREA_RECT, rect);
}

void TArea::move(const QPointF &offset)
{
    if(offset.isNull())
        return;

    QRectF currentRect = mPropertySheet->getValue(PID_AREA_RECT).toRectF();
    currentRect.moveTopLeft(currentRect.topLeft()+offset);
    mPropertySheet->setValue(PID_AREA_RECT, currentRect);
}

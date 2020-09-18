#include "area.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_DANGER_AREA = T("Danger Area");

TArea::TArea(QObject *parent) :
    TAreaPlat(TObject::AREA, parent)
{
    initPropertySheet();
}

TArea::TArea(const QRect &rect, QObject *parent) :
    TAreaPlat(rect, TObject::AREA, parent)
{
    initPropertySheet();
}

void TArea::setPlatNameList(const QStringList &platNames)
{
    mPropertySheet->get(PID_AREA_MOVE_BY)->setAttribute(PA_ENUM_NAMES, platNames);
}

void TArea::saveToStream(QDataStream &stream) const
{
    QRect r = getRect().toRect();
    stream << r.left();
    stream << r.top();
    stream << r.width();
    stream << r.height();
    stream << mPropertySheet->getValue(PID_AREA_FLEE_DIR).toInt();
    stream << (int)mPropertySheet->getValue(PID_AREA_DANGER_AREA).toBool();
    stream << 0;// No use always 0
    TAreaPlat::saveToStream(stream);
}

void TArea::readFromStream(QDataStream &stream)
{
    int x,y,w,h,fleeDir,dangerArea,edges;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    stream >> fleeDir;
    stream >> dangerArea;
    stream >> edges;
    TAreaPlat::readFromStream(stream);

    setRect(x, y, w, h);
    mPropertySheet->setValue(PID_AREA_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(PID_AREA_DANGER_AREA, (bool)dangerArea);
}

void TArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_DIR, P_FLEE_DIR, PID_AREA_FLEE_DIR);
    mPropertySheet->addProperty(PT_BOOL, P_DANGER_AREA, PID_AREA_DANGER_AREA);
}

void TArea::slotBindPlatChanged(TPlat *, int, TPlat *, int)
{

}

QString TArea::typeString() const
{
    return T("Area");
}

bool TArea::isCongener(TObject *object) const
{
    return static_cast<TArea*>(object);
}

QByteArray TArea::toByteArray(TObject *object) const
{

}

void TArea::loadFromByteArray(const QByteArray &byteArray)
{

}

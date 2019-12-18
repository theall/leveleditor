#include "darea.h"
#include "../../base/tr.h"

#include <QRect>

static const QString P_FLEE_DIR = T("Flee Direction");
static const QString P_ESCAPE_TYPE = T("Escape Type");
static const QString P_TARGET = T("Target");
static const QString TP_AI_ESCAPE = T("This flag is for ai to escape danger area.\n"
                                    "True\t perform up-special action.\n"
                                    "False\t perform jump action, the target value speciy jump mode");
static const QString TP_AI_TARGET = T("This value is only take effect under the escape flag is true.\n"
                                      "While this value is 5, ai will definitely perform jump action.\n"
                                      "If not 5, it will perform jump action as long as the y-coordinate\n"
                                      "distance between ai and locked player larger than target value.");

TDArea::TDArea(QObject *parent) :
    TAreaPlat(TObject::DAREA, parent)
  , mEscapePropertyItem(nullptr)
  , mTargetPropertyItem(nullptr)
{
    initPropertySheet();
}

TDArea::TDArea(const QRect &rect, QObject *parent) :
    TAreaPlat(rect, TObject::DAREA, parent)
  , mEscapePropertyItem(nullptr)
  , mTargetPropertyItem(nullptr)
{
    initPropertySheet();
}

void TDArea::slotAiEscapeModePropertyChanged(const QVariant &, const QVariant &newValue)
{
    bool forceUp = newValue.toBool();
    mTargetPropertyItem->setReadOnly(forceUp);
}

void TDArea::saveToStream(QDataStream &stream) const
{
    QRect r = getRect().toRect();
    stream << r.left();
    stream << r.top();
    stream << r.width();
    stream << r.height();
    stream << mPropertySheet->getValue(PID_DAREA_FLEE_DIR).toInt();
    stream << mPropertySheet->getValue(PID_DAREA_TYPE).toInt();
    stream << mPropertySheet->getValue(PID_DAREA_TARGET).toInt();
    TAreaPlat::saveToStream(stream);
}

void TDArea::readFromStream(QDataStream &stream)
{
    int x,y,w,h,fleeDir,type,target;
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    stream >> fleeDir;
    stream >> type;
    stream >> target;
    TAreaPlat::readFromStream(stream);

    setRect(x, y, w, h);
    mPropertySheet->setValue(PID_DAREA_FLEE_DIR, fleeDir);
    mPropertySheet->setValue(PID_DAREA_TYPE, type);
    mPropertySheet->setValue(PID_DAREA_TARGET, target);
}

void TDArea::initPropertySheet()
{
    mPropertySheet->addProperty(PT_DIR, P_FLEE_DIR, PID_DAREA_FLEE_DIR);
    mEscapePropertyItem = mPropertySheet->addProperty(PT_BOOL, P_ESCAPE_TYPE, PID_DAREA_TYPE);
    mEscapePropertyItem->setToolTip(TP_AI_ESCAPE);
    mTargetPropertyItem = mPropertySheet->addProperty(PT_INT, P_TARGET, PID_DAREA_TARGET, QVariant(), mEscapePropertyItem);
    mTargetPropertyItem->setToolTip(TP_AI_TARGET);
    connect(mEscapePropertyItem, SIGNAL(valueChanged(QVariant,QVariant)), this, SLOT(slotAiEscapeModePropertyChanged(QVariant,QVariant)));
}

QString TDArea::typeString() const
{
    return T("Danger Area");
}

bool TDArea::isCongener(TObject *object) const
{
    return static_cast<TDArea*>(object);
}

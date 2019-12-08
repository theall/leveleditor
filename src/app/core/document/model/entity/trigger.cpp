#include "trigger.h"
#include "../../base/tr.h"

#include <QRect>
#include <QPoint>

static const QString P_WAY = T("Way");
static const QString P_ON = T("On");
static const QString P_ACTION = T("Action");
static const QString P_PASS_BY = T("Pass By");
static const QString P_OBJECT_HIT = T("Object Hit");
static const QString P_EVENT = T("Event");
static const QString P_DRAW = T("Draw");
static const QString P_IMAGE_NO = T("Image NO");
static const QString P_IMAGE_POS = T("Image Pos");
static const QString P_AFFECT = T("Affect");
static const QString P_SOUND = T("Sound");
static const QString P_FOLLOW = T("Follow");
static const QString P_PLATFORM_POS = T("Platform Pos");
static const QString P_ON_STATUS = T("On Status");
static const QString P_OFF_STATUS = T("Off Status");

TTrigger::TTrigger(QObject *parent) :
    TRectObject(TObject::TRIGGER, parent)
{
    initPropertySheet();
}

void TTrigger::saveToStream(QDataStream &stream) const
{
    stream << getRect();
    stream << mPropertySheet->getValue(PID_TRIGGER_WAY).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_ON).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_ACTION).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_PASS_BY).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_OBJECT_HIT).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_EVENT).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_DRAW).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_IMAGE_NO).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_IMAGE_POS).toPoint();
    stream << mPropertySheet->getValue(PID_TRIGGER_AFFECT).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_SOUND).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_FOLLOW).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_PLATFORM_POS).toPoint();
    stream << mPropertySheet->getValue(PID_TRIGGER_ON_STATUS).toInt();
    stream << mPropertySheet->getValue(PID_TRIGGER_OFF_STATUS).toInt();
}

void TTrigger::readFromStream(QDataStream &stream)
{
    QRect rect;
    int way;
    int on;
    int action;
    int passBy;
    int objHit;
    int event;
    int draw;
    int imageN;
    QPoint imagePos;
    int affect;
    int sound;
    int follow;
    QPoint platPos;
    int onStatus;
    int offStatus;
    stream >> rect;
    stream >> way;
    stream >> on;
    stream >> action;
    stream >> passBy;
    stream >> objHit;
    stream >> event;
    stream >> draw;
    stream >> imageN;
    stream >> imagePos;
    stream >> affect;
    stream >> sound;
    stream >> follow;
    stream >> platPos;
    stream >> onStatus;
    stream >> offStatus;
    setRect(rect);
    mPropertySheet->setValue(PID_TRIGGER_WAY, way);
    mPropertySheet->setValue(PID_TRIGGER_ON, on);
    mPropertySheet->setValue(PID_TRIGGER_ACTION, action);
    mPropertySheet->setValue(PID_TRIGGER_PASS_BY, passBy);
    mPropertySheet->setValue(PID_TRIGGER_OBJECT_HIT, objHit);
    mPropertySheet->setValue(PID_TRIGGER_EVENT, event);
    mPropertySheet->setValue(PID_TRIGGER_DRAW, draw);
    mPropertySheet->setValue(PID_TRIGGER_IMAGE_NO, imageN);
    mPropertySheet->setValue(PID_TRIGGER_IMAGE_POS, imagePos);
    mPropertySheet->setValue(PID_TRIGGER_AFFECT, affect);
    mPropertySheet->setValue(PID_TRIGGER_SOUND, sound);
    mPropertySheet->setValue(PID_TRIGGER_FOLLOW, follow);
    mPropertySheet->setValue(PID_TRIGGER_PLATFORM_POS, platPos);
    mPropertySheet->setValue(PID_TRIGGER_ON_STATUS, onStatus);
    mPropertySheet->setValue(PID_TRIGGER_OFF_STATUS, offStatus);
}

void TTrigger::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_WAY, PID_TRIGGER_WAY);
    mPropertySheet->addProperty(PT_INT, P_ON, PID_TRIGGER_ON);
    mPropertySheet->addProperty(PT_INT, P_ACTION, PID_TRIGGER_ACTION);
    mPropertySheet->addProperty(PT_INT, P_PASS_BY, PID_TRIGGER_PASS_BY);
    mPropertySheet->addProperty(PT_INT, P_OBJECT_HIT, PID_TRIGGER_OBJECT_HIT);
    mPropertySheet->addProperty(PT_INT, P_EVENT, PID_TRIGGER_EVENT);
    mPropertySheet->addProperty(PT_INT, P_DRAW, PID_TRIGGER_DRAW);
    mPropertySheet->addProperty(PT_INT, P_IMAGE_NO, PID_TRIGGER_IMAGE_NO);
    mPropertySheet->addProperty(PT_POINT, P_IMAGE_POS, PID_TRIGGER_IMAGE_POS);
    mPropertySheet->addProperty(PT_INT, P_AFFECT, PID_TRIGGER_AFFECT);
    mPropertySheet->addProperty(PT_INT, P_SOUND, PID_TRIGGER_SOUND);
    mPropertySheet->addProperty(PT_INT, P_FOLLOW, PID_TRIGGER_FOLLOW);
    mPropertySheet->addProperty(PT_POINT, P_PLATFORM_POS, PID_TRIGGER_PLATFORM_POS);
    mPropertySheet->addProperty(PT_INT, P_ON_STATUS, PID_TRIGGER_ON_STATUS);
    mPropertySheet->addProperty(PT_INT, P_OFF_STATUS, PID_TRIGGER_OFF_STATUS);
}

QString TTrigger::typeString() const
{
    return T("Trigger");
}

bool TTrigger::isCongener(TObject *) const
{
    return false;
}

#include "trigger.h"
#include "../../../assets/triggerid.h"
#include "../../../assets/assetsmanager.h"
#include "../../base/tr.h"

#include <QRect>
#include <QPoint>

static const QString P_TYPE = T("Type");
static const QString P_ON = T("On");
static const QString P_ACTION = T("Action");
static const QString P_PASS_BY = T("Pass By");
static const QString P_OBJECT_HIT = T("Object Hit");
static const QString P_EVENT = T("Event");
static const QString P_DRAW = T("Draw");
static const QString P_IMAGE = T("Image");
static const QString P_IMAGE_NO = T("Number");
static const QString P_IMAGE_POS = T("Pos");
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
    QRect rect = getRect().toRect();
    stream << rect.left();
    stream << rect.top();
    stream << rect.width();
    stream << rect.height();
    stream << mPropertySheet->getValue(PID_TRIGGER_TYPE).toInt()+1;
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
    int x;
    int y;
    int w;
    int h;
    int type;
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
    stream >> x;
    stream >> y;
    stream >> w;
    stream >> h;
    stream >> type;
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

    mTriggerId = TAssetsManager::getInstance()->getTriggerId(imageN);

    setRect(x, y, w, h);
    mPropertySheet->setValue(PID_TRIGGER_TYPE, type-1);
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

QPointF TTrigger::getImageOffset() const
{
    return mPropertySheet->getValue(PID_TRIGGER_IMAGE_POS).toPointF();
}

TTriggerId *TTrigger::triggerId() const
{
    return mTriggerId;
}

void TTrigger::setTriggerId(TTriggerId *triggerId)
{
    mTriggerId = triggerId;
}

void TTrigger::initPropertySheet()
{
    TPropertyItem *propertyItem = mPropertySheet->addProperty(PT_ENUM, P_TYPE, PID_TRIGGER_TYPE);
    QStringList typeString;
    typeString << tr("Once");
    typeString << tr("On/off");
    typeString << tr("Action");
    typeString << tr("Next music");
    typeString << tr("Next map 1");
    typeString << tr("Next map 2");
    typeString << tr("Next map 3");
    typeString << tr("Next map 4");
    typeString << tr("Next map 5");
    typeString << tr("Change fight mode");
    typeString << tr("Screen lock");
    typeString << tr("No air special");
    typeString << tr("No double jump");
    typeString << tr("Secret area discovery");
    propertyItem->addAttribute(PA_ENUM_NAMES, typeString);

    mPropertySheet->addProperty(PT_BOOL, P_ON, PID_TRIGGER_ON);
    propertyItem = mPropertySheet->addProperty(PT_BOOL, P_ACTION, PID_TRIGGER_ACTION);
    propertyItem->setToolTip(tr("Trigger while player press up on this area."));

    propertyItem = mPropertySheet->addProperty(PT_BOOL, P_PASS_BY, PID_TRIGGER_PASS_BY);
    propertyItem->setToolTip(tr("Trigger while player is on this area."));

    propertyItem = mPropertySheet->addProperty(PT_BOOL, P_OBJECT_HIT, PID_TRIGGER_OBJECT_HIT);
    propertyItem->setToolTip(tr("Trigger while item hits this area."));

    mPropertySheet->addProperty(PT_INT, P_EVENT, PID_TRIGGER_EVENT);
    mPropertySheet->addProperty(PT_BOOL, P_DRAW, PID_TRIGGER_DRAW);

    propertyItem = mPropertySheet->addGroupProperty(P_IMAGE);
    mPropertySheet->addProperty(PT_INT, P_IMAGE_NO, PID_TRIGGER_IMAGE_NO, QVariant(), propertyItem);
    mPropertySheet->addProperty(PT_POINT, P_IMAGE_POS, PID_TRIGGER_IMAGE_POS, QVariant(),propertyItem);

    propertyItem = mPropertySheet->addProperty(PT_BOOL, P_AFFECT, PID_TRIGGER_AFFECT);
    propertyItem->setToolTip(tr("true: affect alive players, false: affect all players."));

    mPropertySheet->addProperty(PT_SOUND_ITEM, P_SOUND, PID_TRIGGER_SOUND);
    mPropertySheet->addProperty(PT_INT, P_FOLLOW, PID_TRIGGER_FOLLOW);
    mPropertySheet->addProperty(PT_POINT, P_PLATFORM_POS, PID_TRIGGER_PLATFORM_POS);
    mPropertySheet->addProperty(PT_BOOL, P_ON_STATUS, PID_TRIGGER_ON_STATUS);
    mPropertySheet->addProperty(PT_BOOL, P_OFF_STATUS, PID_TRIGGER_OFF_STATUS);
}

QString TTrigger::typeString() const
{
    return T("Trigger");
}

bool TTrigger::isCongener(TObject *) const
{
    return false;
}

QByteArray TTrigger::toByteArray(TObject *object) const
{

}

void TTrigger::loadFromByteArray(const QByteArray &byteArray)
{

}

#include "box.h"
#include "../../base/tr.h"

#include <QPoint>
#include <QPointF>

static const QString P_POS = T("Pos");
static const QString P_SIZE = T("Size");
static const QString P_SPEED = T("Move Speed");
static const QString P_TARGET = T("Target");
static const QString P_DRAW = T("Draw");
static const QString P_TYPE = T("Type");
static const QString P_CHUNK_TYPE = T("Chunk type");
static const QString P_HIT = T("Hit");
static const QString P_HIT_MODE = T("Mode");
static const QString P_HIT_TIME = T("Time");
static const QString P_HIT_SPEED = T("Speed");
static const QString P_HIT_Y_SPEED = T("Y Speed");
static const QString P_DAMAGE = T("Damage");
static const QString P_HIT_SOUND = T("Sound");
static const QString P_USE_TRIGGER = T("Use Trigger");
static const QString P_BREAK = T("Break");
static const QString P_SOUND = T("Sound");
static const QString P_BREAKABLE = T("Breakable");
static const QString P_EVENTN = T("Event 1");
static const QString P_EVENTN2 = T("Event 2");
static const QString TP_DRAW = T("Draw box border if this flag is set.");
static const QString TP_BREAK = T("While this flag is true, the box will play \n"
                                  "sound and make chunk after it arrive the final point.");

static const QStringList P_ENUM_BOX_TYPE = {
    T("Default"),
    T("Buzz saw"),
    T("Lava chunk"),
    T("blue/red target"),
    T("vent"),
    T("laser box"),
    T("flower")
};

TBox::TBox(QObject *parent) :
    TRectObject(TObject::BOX, parent)
{
    initPropertySheet();
}

TBox::TBox(const QRect &rect, QObject *parent) :
    TRectObject(rect, TObject::DAREA, parent)
{
    initPropertySheet();
}

QList<QPoint> TBox::pointList() const
{
    return mPointList;
}

void TBox::saveToStream(QDataStream &stream) const
{
    QRectF rect = getRect();
    stream << rect.left();
    stream << rect.top();
    stream << mPropertySheet->getValue(PID_BOX_SPEED).toPointF();
    stream << mPropertySheet->getValue(PID_BOX_TARGET).toInt();
    stream << mPropertySheet->getValue(PID_BOX_DRAW).toInt()  ;
    stream << (int)rect.width();
    stream << (int)rect.height();
    stream << mCurrentPoint;// curPoint
    stream << mPointList.size();// pointsAmount
    stream << mPropertySheet->getValue(PID_BOX_TYPE).toInt();
    stream << mPropertySheet->getValue(PID_BOX_CHUNK_TYPE).toInt();
    stream << mPropertySheet->getValue(PID_BOX_HIT_MODE).toInt();
    stream << mPropertySheet->getValue(PID_BOX_HIT_TIME).toFloat();
    stream << mPropertySheet->getValue(PID_BOX_HIT_SPEED).toPointF();
    stream << mPropertySheet->getValue(PID_BOX_DAMAGE).toInt();
    stream << mPropertySheet->getValue(PID_BOX_HIT_SOUND).toInt();
    stream << mPropertySheet->getValue(PID_BOX_USE_TRIGGER).toInt();
    stream << mPropertySheet->getValue(PID_BOX_EVENTN).toInt();
    stream << mFinalPoint; // finalDest
    stream << mPropertySheet->getValue(PID_BOX_BREAK).toInt();
    stream << mPropertySheet->getValue(PID_BOX_SOUND).toInt();
    stream << mPropertySheet->getValue(PID_BOX_BREAKABLE).toInt();
    stream << mPropertySheet->getValue(PID_BOX_EVENTN2).toInt();
    for(QPoint point : mPointList) {
        stream << point;
    }
}

void TBox::readFromStream(QDataStream &stream)
{
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int target;
    int draw;
    int width;
    int height;
    int curPoint;
    int pointsAmount;
    int type;
    int chunkType;
    int hitMode;
    float hitTime;
    float hitSpeed;
    float hitYSpeed;
    int damage;
    int hitSound;
    int useTrigger;
    int eventN;
    int finalDest;
    int _break;
    int sound;
    int breakable;
    int eventN2;
    stream >> x;
    stream >> y;
    stream >> xSpeed;
    stream >> ySpeed;
    stream >> target;
    stream >> draw;
    stream >> width;
    stream >> height;
    stream >> curPoint;
    stream >> pointsAmount;
    stream >> type;
    stream >> chunkType;
    stream >> hitMode;
    stream >> hitTime;
    stream >> hitSpeed;
    stream >> hitYSpeed;
    stream >> damage;
    stream >> hitSound;
    stream >> useTrigger;
    stream >> eventN;
    stream >> finalDest;
    stream >> _break;
    stream >> sound;
    stream >> breakable;
    stream >> eventN2;
    mPointList.clear();
    for(int i=0;i<pointsAmount;i++) {
        QPoint point;
        stream >> point;
        mPointList.append(point);
    }
    mCurrentPoint = curPoint;
    mFinalPoint = finalDest;

    QPointF pos(x, y);
    QPointF speed(xSpeed, ySpeed);
    QSizeF size(width, height);
    setRect(QRectF(pos, size));

    mPropertySheet->setValue(PID_BOX_SPEED, speed);
    mPropertySheet->setValue(PID_BOX_TARGET, target);
    mPropertySheet->setValue(PID_BOX_DRAW, draw);
    mPropertySheet->setValue(PID_BOX_TYPE, type);
    mPropertySheet->setValue(PID_BOX_CHUNK_TYPE, chunkType);
    mPropertySheet->setValue(PID_BOX_HIT_MODE, hitMode);
    mPropertySheet->setValue(PID_BOX_HIT_TIME, hitTime);
    mPropertySheet->setValue(PID_BOX_HIT_SPEED, QPointF(hitSpeed,hitYSpeed));
    mPropertySheet->setValue(PID_BOX_DAMAGE, damage);
    mPropertySheet->setValue(PID_BOX_HIT_SOUND, hitSound);
    mPropertySheet->setValue(PID_BOX_USE_TRIGGER, useTrigger);
    mPropertySheet->setValue(PID_BOX_BREAK, _break);
    mPropertySheet->setValue(PID_BOX_SOUND, sound);
    mPropertySheet->setValue(PID_BOX_BREAKABLE, breakable);
    mPropertySheet->setValue(PID_BOX_EVENTN, eventN);
    mPropertySheet->setValue(PID_BOX_EVENTN2, eventN2);
}

void TBox::initPropertySheet()
{
    mPropertySheet->addProperty(PT_POINTF, P_SPEED, PID_BOX_SPEED);
    mPropertySheet->addProperty(PT_BOOL, P_BREAKABLE, PID_BOX_BREAKABLE);
    mPropertySheet->addProperty(PT_INT, P_TARGET, PID_BOX_TARGET);
    TPropertyItem *groupItem = mPropertySheet->addGroupProperty(P_HIT);
    mPropertySheet->addProperty(PT_BOOL, P_DRAW, PID_BOX_DRAW)->setToolTip(TP_DRAW);
    mPropertySheet->addProperty(PT_ENUM, P_TYPE, PID_BOX_TYPE)->setAttribute(PA_ENUM_NAMES, P_ENUM_BOX_TYPE);
    mPropertySheet->addProperty(PT_INT, P_CHUNK_TYPE, PID_BOX_CHUNK_TYPE, QVariant(), groupItem);
    mPropertySheet->addProperty(PT_INT, P_HIT_MODE, PID_BOX_HIT_MODE, QVariant(), groupItem);
    mPropertySheet->addProperty(PT_INT, P_HIT_TIME, PID_BOX_HIT_TIME, QVariant(), groupItem);
    mPropertySheet->addProperty(PT_POINTF, P_HIT_SPEED, PID_BOX_HIT_SPEED, QVariant(), groupItem);
    mPropertySheet->addProperty(PT_INT, P_DAMAGE, PID_BOX_DAMAGE, QVariant(), groupItem);
    mPropertySheet->addProperty(PT_INT, P_HIT_SOUND, PID_BOX_HIT_SOUND, QVariant(), groupItem);
    mPropertySheet->addProperty(PT_BOOL, P_BREAK, PID_BOX_BREAK)->setToolTip(TP_BREAK);
    mPropertySheet->addProperty(PT_INT, P_SOUND, PID_BOX_SOUND, QVariant());
    mPropertySheet->addProperty(PT_INT, P_USE_TRIGGER, PID_BOX_USE_TRIGGER);
    mPropertySheet->addProperty(PT_INT, P_EVENTN, PID_BOX_EVENTN);
    mPropertySheet->addProperty(PT_INT, P_EVENTN2, PID_BOX_EVENTN2);
}

QString TBox::typeString() const
{
    return T("Box");
}

bool TBox::isCongener(TObject *object) const
{
    return static_cast<TBox*>(object);
}

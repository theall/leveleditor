#include "plat.h"
#include "../../base/tr.h"

static const QString P_SPEED = T("Speed");
static const QString P_DANGER = T("Danger");
static const QString P_DRAW = T("Draw");
static const QString P_CURRENT_POINT = T("Current point");
static const QString P_TILE = T("Tile");
static const QString P_USE_TRIGGER = T("Use trigger");
static const QString P_EVENT_NUMBER = T("Event number");
static const QString P_FINAL_POINT = T("Final point");
static const QString P_BREAK = T("Break");
static const QString P_CHUNK = T("Chunk");
static const QString P_SOUND = T("Sound");
static const QString P_BREAKABLE = T("Breakable");
static const QString P_EVENT_NUMBER_2 = T("Event number 2");

TPlat::TPlat(QObject *parent) :
    TRectObject(TObject::PLAT, parent)
{
    initPropertySheet();
}

TPlat::TPlat(const QRect &rect, QObject *parent) :
    TRectObject(rect, TObject::DAREA, parent)
{
    initPropertySheet();
}

void TPlat::saveToStream(QDataStream &stream) const
{
    QRectF rect = getRect();
    QPointF speed = mPropertySheet->getValue(PID_PLAT_SPEED).toPointF();
    stream << (float)rect.left();
    stream << (float)rect.top();
    stream << (float)speed.x();
    stream << (float)speed.y();
    stream << mPropertySheet->getValue(PID_PLAT_DANGER).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_DRAW).toInt();
    stream << (int)rect.width();
    stream << (int)rect.height();
    stream << mPropertySheet->getValue(PID_PLAT_CURRENT_POINT).toInt();
    stream << mPointList.size();
    stream << mPropertySheet->getValue(PID_PLAT_TILE).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_USE_TRIGGER).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_EVENT_NUMBER).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_FINAL_POINT).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_BREAK).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_CHUNK).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_SOUND).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_BREAKABLE).toInt();
    stream << mPropertySheet->getValue(PID_PLAT_EVENT_NUMBER_2).toInt();

    for(QPoint point : mPointList) {
        stream << point;
    }
}

void TPlat::readFromStream(QDataStream &stream)
{
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int danger;
    int draw;
    int width;
    int height;
    int curPoint;
    int pointsAmount;
    int pic;
    int useTrigger;
    int eventN;
    int finalDest;
    int break_;
    int chunk;
    int sound;
    int breakable;
    int eventN2;
    stream >> x;
    stream >> y;
    stream >> xSpeed;
    stream >> ySpeed;
    stream >> danger;
    stream >> draw;
    stream >> width;
    stream >> height;
    stream >> curPoint;
    stream >> pointsAmount;
    stream >> pic;
    stream >> useTrigger;
    stream >> eventN;
    stream >> finalDest;
    stream >> break_;
    stream >> chunk;
    stream >> sound;
    stream >> breakable;
    stream >> eventN2;
    mPointList.clear();
    for(int i=0;i<pointsAmount;i++) {
        QPoint point;
        stream >> point;
        mPointList.append(point);
    }
    setRect(QRectF(x, y, width, height));
    mPropertySheet->setValue(PID_PLAT_SPEED, QPointF(xSpeed, ySpeed));
    mPropertySheet->setValue(PID_PLAT_DANGER, danger);
    mPropertySheet->setValue(PID_PLAT_DRAW, draw);
    mPropertySheet->setValue(PID_PLAT_CURRENT_POINT, curPoint);
    mPropertySheet->setValue(PID_PLAT_TILE, pic);
    mPropertySheet->setValue(PID_PLAT_USE_TRIGGER, useTrigger);
    mPropertySheet->setValue(PID_PLAT_EVENT_NUMBER, eventN);
    mPropertySheet->setValue(PID_PLAT_FINAL_POINT, finalDest);
    mPropertySheet->setValue(PID_PLAT_BREAK, break_);
    mPropertySheet->setValue(PID_PLAT_CHUNK, chunk);
    mPropertySheet->setValue(PID_PLAT_SOUND, sound);
    mPropertySheet->setValue(PID_PLAT_BREAKABLE, breakable);
    mPropertySheet->setValue(PID_PLAT_EVENT_NUMBER_2, eventN2);
    if(mDocument) {
        //mPixmap = mDocument->getPixmap(QString::asprintf("plat%d.bmp", pic))->pixmap();
    }
}

void TPlat::initPropertySheet()
{
    mPropertySheet->addProperty(PT_DOUBLE, P_SPEED, PID_PLAT_SPEED);
    mPropertySheet->addProperty(PT_INT, P_DANGER, PID_PLAT_DANGER);
    mPropertySheet->addProperty(PT_INT, P_DRAW, PID_PLAT_DRAW);
    mPropertySheet->addProperty(PT_INT, P_CURRENT_POINT, PID_PLAT_CURRENT_POINT);
    mPropertySheet->addProperty(PT_INT, P_TILE, PID_PLAT_TILE);
    mPropertySheet->addProperty(PT_INT, P_USE_TRIGGER, PID_PLAT_USE_TRIGGER);
    mPropertySheet->addProperty(PT_INT, P_EVENT_NUMBER, PID_PLAT_EVENT_NUMBER);
    mPropertySheet->addProperty(PT_INT, P_FINAL_POINT, PID_PLAT_FINAL_POINT);
    mPropertySheet->addProperty(PT_INT, P_BREAK, PID_PLAT_BREAK);
    mPropertySheet->addProperty(PT_INT, P_CHUNK, PID_PLAT_CHUNK);
    mPropertySheet->addProperty(PT_INT, P_SOUND, PID_PLAT_SOUND);
    mPropertySheet->addProperty(PT_INT, P_BREAKABLE, PID_PLAT_BREAKABLE);
    mPropertySheet->addProperty(PT_INT, P_EVENT_NUMBER_2, PID_PLAT_EVENT_NUMBER_2);
}

QString TPlat::typeString() const
{
    return tr("Platform");
}

bool TPlat::isCongener(TObject *) const
{
    return false;
}

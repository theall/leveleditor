#include "tile.h"
#include "../../base/tr.h"
#include "../../base/findobj.h"
#include "../../document.h"
#include "../../../assets/cachedpixmap.h"

#include <QPoint>
#include <QPointF>

static const QString P_POS_1 = T("Pos 1");
static const QString P_POS_2 = T("Pos 2");
static const QString P_IMAGE = T("Image");
static const QString P_END_1 = T("End 1");
static const QString P_END_2 = T("End 2");
static const QString P_RAND_1 = T("Rand 1");
static const QString P_RAND_2 = T("Rand 2");
static const QString P_SPEED = T("Speed");
static const QString P_START_POS = T("Start Pos");
static const QString P_FOLLOW = T("Follow");
static const QString P_FOLLOW_TYPE = T("Follow Type");
static const QString P_TARGET = T("Target");
static const QString P_SCREEN_SPEED = T("Screen Speed");

TTile::TTile(QObject *parent) :
    TPropertyObject(parent)
{
    FIND_OBJECT;

    initPropertySheet();
}

void TTile::saveToStream(QDataStream &stream) const
{
    QPointF pos1 = mPropertySheet->getValue(P_POS_1).toPointF();
    stream << (float)pos1.x();
    stream << (float)pos1.y();
}

void TTile::readFromStream(QDataStream &stream)
{
    float x;
    float y;
    int number;
    int setNumber;
    int xEnd1;
    int xEnd2;
    int xRand1;
    int xRand2;
    float xSpeed;
    int yEnd1;
    int yEnd2;
    int yRand1;
    int yRand2;
    float ySpeed;
    int xStart;
    int yStart;
    int follow;
    int target;
    int x2;
    int y2;
    int followType;
    float xScrSpeed;
    float yScrSpeed;
    stream >> x;
    stream >> y;
    stream >> number;
    stream >> setNumber;
    stream >> xEnd1;
    stream >> xEnd2;
    stream >> xRand1;
    stream >> xRand2;
    stream >> xSpeed;
    stream >> yEnd1;
    stream >> yEnd2;
    stream >> yRand1;
    stream >> yRand2;
    stream >> ySpeed;
    stream >> xStart;
    stream >> yStart;
    stream >> follow;
    stream >> target;
    stream >> x2;
    stream >> y2;
    stream >> followType;
    stream >> xScrSpeed;
    stream >> yScrSpeed;

    QPointF pos1(x, y);
    QPoint pos2(x2, y2);
    QPoint end1(xEnd1, yEnd1);
    QPoint end2(xEnd2, yEnd2);
    QPoint rand1(xRand1, yRand1);
    QPoint rand2(xRand2, yRand2);
    QPointF speed(xSpeed, ySpeed);
    QPoint startPos(xStart, yStart);
    QPointF screenSpeed(xScrSpeed, yScrSpeed);
    QString imagePath = QString("%1_%2.bmp").arg(setNumber).arg(number);

    mPropertySheet->setValue(P_POS_1, pos1);
    mPropertySheet->setValue(P_POS_2, pos2);
    mPropertySheet->setValue(P_IMAGE, imagePath);
    mPropertySheet->setValue(P_END_1, end1);
    mPropertySheet->setValue(P_END_2, end2);
    mPropertySheet->setValue(P_RAND_1, rand1);
    mPropertySheet->setValue(P_RAND_2, rand2);
    mPropertySheet->setValue(P_SPEED, speed);
    mPropertySheet->setValue(P_START_POS, startPos);
    mPropertySheet->setValue(P_FOLLOW, follow);
    mPropertySheet->setValue(P_FOLLOW_TYPE, followType);
    mPropertySheet->setValue(P_TARGET, target);
    mPropertySheet->setValue(P_SCREEN_SPEED, screenSpeed);

    TPixmap *pixmap = mDocument->getPixmap(imagePath);
    if(pixmap) {
        mPixmap = pixmap->pixmap();
        mRect.setTopLeft(pos1);
        mRect.setSize(mPixmap.size());
    }
}

void TTile::render(QPainter *painter, const QRectF &rect)
{
    if(rect.intersected(mRect).isEmpty())
        return;

    painter->drawPixmap(mRect.topLeft(), mPixmap);
}

void TTile::initPropertySheet()
{
    mPropertySheet->addProperty(PT_VECTORF, P_POS_1, PID_TILE_POS_1);
    mPropertySheet->addProperty(PT_VECTOR, P_POS_2, PID_TILE_POS_2);
    mPropertySheet->addProperty(PT_PIXMAP, P_IMAGE, PID_TILE_IMAGE);
    mPropertySheet->addProperty(PT_VECTOR, P_END_1, PID_TILE_END_1);
    mPropertySheet->addProperty(PT_VECTOR, P_END_2, PID_TILE_END_2);
    mPropertySheet->addProperty(PT_VECTOR, P_RAND_1, PID_TILE_RAND_1);
    mPropertySheet->addProperty(PT_VECTOR, P_RAND_2, PID_TILE_RAND_2);
    mPropertySheet->addProperty(PT_VECTORF, P_SPEED, PID_TILE_SPEED);
    mPropertySheet->addProperty(PT_VECTOR, P_START_POS, PID_TILE_START_POS);
    mPropertySheet->addProperty(PT_INT, P_FOLLOW, PID_TILE_FOLLOW);
    mPropertySheet->addProperty(PT_INT, P_FOLLOW_TYPE, PID_TILE_FOLLOW_TYPE);
    mPropertySheet->addProperty(PT_INT, P_TARGET, PID_TILE_TARGET);
    mPropertySheet->addProperty(PT_VECTOR, P_SCREEN_SPEED, PID_TILE_SCREEN_SPEED);
}

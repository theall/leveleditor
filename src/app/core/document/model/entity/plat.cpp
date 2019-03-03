#include "plat.h"
#include "point.h"
#include "../../document.h"

TPlat::TPlat(QObject *parent) :
    TPropertyObject(parent)
  , mDocument(nullptr)
{

}

void TPlat::saveToStream(QDataStream &stream) const
{

}

void TPlat::readFromStream(QDataStream &stream)
{
    float x;
    float y;
    int xSpeed;
    int ySpeed;
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
    if(mDocument) {
        mPixmap = mDocument->getPixmap(QString::asprintf("plat%d.bmp", pic))->pixmap();
    }
    for(int i=0;i<pointsAmount;i++) {
        TPoint point;
        point.readFromStream(stream);
    }
}

void TPlat::initPropertySheet()
{

}

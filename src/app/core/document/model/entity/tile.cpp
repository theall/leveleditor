#include "tile.h"
#include "../../base/tr.h"
#include "../../../assets/tileid.h"
#include "../../../assets/cachedpixmap.h"
#include "../../../assets/assetsmanager.h"

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

TTileMoveModel::TTileMoveModel(QObject *parent) :
    QObject(parent)
{

}

TTileMoveModel::Type TTileMoveModel::type() const
{
    return mType;
}

void TTileMoveModel::setType(const Type &type)
{
    mType = type;
}

TStartPoint::TStartPoint(QObject *parent) :
    TPointObject(parent)
{

}

TStartPoint::~TStartPoint()
{

}

QString TStartPoint::typeString() const
{
    return "Start Pos";
}

bool TStartPoint::isCongener(TObject *) const
{
    return false;
}

void TStartPoint::initPropertySheet()
{

}

TDoor::TDoor(QObject *parent) :
    TRectObject(TObject::DOOR, parent)
  , mDir(None)
  , mType(TDoor::Recycle)
  , mStartPoint(new TStartPoint(this))
{

}

TDoor::Dir TDoor::dir() const
{
    return mDir;
}

void TDoor::setDir(const Dir &dir)
{
    mDir = dir;
}

void TDoor::move(qreal offset, const Edge &edge)
{
    QRectF r = getRect();
    qreal dx1 = 0;
    qreal dy1 = 0;
    qreal dx2 = 0;
    qreal dy2 = 0;
    if(mDir == Horizontal) {
        if(edge&Left) {
            dx1 = offset;
        }
        if(edge&Right) {
            dx2 = offset;
        }
    } else if(mDir == Vertical) {
        if(edge&Left) {
            dy1 = offset;
        }
        if(edge&Right) {
            dy2 = offset;
        }
    }
    r.adjust(dx1, dy1, dx2, dy2);
    setRect(r);
}

void TDoor::slide(const QPointF &offset)
{
    QPointF distance(offset);
    if(mDir == Horizontal) {
        distance.setX(0);
    } else if(mDir == Vertical) {
        distance.setY(0);
    }
    //TObject::move(distance);
}

TDoor::Type TDoor::type() const
{
    return mType;
}

void TDoor::setType(const Type &type)
{
    mType = type;
}

void TDoor::setPos(const QPointF &)
{
    //TObject::setPos(pos);
}

TStartPoint *TDoor::startPoint() const
{
    return mStartPoint;
}

void TDoor::setStartPos(const QPointF &pos)
{
//    mStartPoint->setPos(pos);
}

QString TDoor::typeString() const
{
    return "Door";
}

bool TDoor::isCongener(TObject *) const
{
    return false;
}

void TDoor::initPropertySheet()
{

}

TTile::TTile(QObject *parent) :
    TPointObject(TObject::TILE, parent)
  , mPixmap(nullptr)
  , mDoor(nullptr)
  , mTarget(nullptr)
  , mTileId(nullptr)
  , mHasMoveModel(false)
  , mTargetNumber(-1)
  , mTilesetNo(-1)
  , mTileNo(-1)
{
    initPropertySheet();
}

void TTile::saveToStream(QDataStream &stream) const
{
    QPointF p = pos();
    stream << p;
    stream << mTileId->id();
    stream << mTileId->tilesetId();

    QRect endRect(0,0,1,1);// Not(0,0,0,0)
    if(mHasMoveModel) {
        endRect = mDoor->getRect().toRect();
    }
    stream << endRect.left();// xEnd1
    stream << endRect.right();// xEnd2

    QPoint rand1 = mPropertySheet->getValue(PID_TILE_RAND_1).toPoint();
    QPoint rand2 = mPropertySheet->getValue(PID_TILE_RAND_2).toPoint();
    stream << rand1.x();
    stream << rand2.x();

    QPointF speed = mPropertySheet->getValue(PID_TILE_SPEED).toPointF();
    stream << speed.x();
    stream << endRect.top();
    stream << endRect.bottom();
    stream << rand1.y();
    stream << rand2.y();
    stream << speed.y();

    QPoint startPos(0,0);
    if(mHasMoveModel) {
        startPos = mDoor->startPoint()->pos().toPoint();
    }
    stream << startPos;
    stream << mPropertySheet->getValue(PID_TILE_FOLLOW).toInt();
    stream << mPropertySheet->getValue(PID_TILE_TARGET).toInt();
    stream << mPropertySheet->getValue(PID_TILE_POS_2).toPoint();
    stream << mPropertySheet->getValue(PID_TILE_FOLLOW_TYPE).toInt();
    stream << mPropertySheet->getValue(PID_TILE_SCREEN_SPEED).toPointF();
}

void TTile::readFromStream(QDataStream &stream)
{
    float x;
    float y;
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
    stream >> mTileNo;
    stream >> mTilesetNo;
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

    mTargetNumber = target;

    QPointF pos1(x, y);
    QPoint pos2(x2, y2);
    QPoint end1(xEnd1, yEnd1);
    QPoint end2(xEnd2, yEnd2);
    QPoint rand1(xRand1, yRand1);
    QPoint rand2(xRand2, yRand2);
    QPointF speed(xSpeed, ySpeed);
    QPoint startPos(xStart, yStart);
    QPointF screenSpeed(xScrSpeed, yScrSpeed);
    TDoor::Dir moveDir = TDoor::None;
    if(xSpeed>=0.1 || xScrSpeed>=0.1)
        moveDir = TDoor::Horizontal;
    else if(ySpeed>=0.1 || yScrSpeed>=0.1) {
        moveDir = TDoor::Vertical;
    }
    if(moveDir!=TDoor::None && !end1.isNull() && !end2.isNull()) {
        // Has move on tile
        mHasMoveModel = true;
    } else {
        mHasMoveModel = false;
    }

    mPropertySheet->setValue(PID_TILE_POS_1, pos1);
    mPropertySheet->setValue(PID_TILE_POS_2, pos2);
    mPropertySheet->setValue(PID_TILE_RAND_1, rand1);
    mPropertySheet->setValue(PID_TILE_RAND_2, rand2);
    mPropertySheet->setValue(PID_TILE_SPEED, speed);
    mPropertySheet->setValue(PID_TILE_FOLLOW, follow);
    mPropertySheet->setValue(PID_TILE_FOLLOW_TYPE, followType);
    mPropertySheet->setValue(PID_TILE_TARGET, target);
    mPropertySheet->setValue(PID_TILE_SCREEN_SPEED, screenSpeed);
    TAssetsManager *assetsManger = TAssetsManager::getInstance();
    mTileId = assetsManger->getTile(mTilesetNo, mTileNo);
    setPos(pos1);
    setUp();

    if(mHasMoveModel) {
        mDoor = new TDoor(this);
        mDoor->setStartPos(startPos);
        QPointF tilePos = pos();
        qreal tileTop = tilePos.y();
        qreal tileLeft = tilePos.x();
        if(end1.y() < 0.1) {
            end1.setY(tileTop);
        }
        if(end1.x() < 0.1) {
            end1.setX(tileLeft);
        }

        QSize tileSize = QSize(100, 100);//= mTileId->pixmap()->size();
        if(end2.y() < 1)
            end2.setY(tileTop + tileSize.height());
        if(end2.x() < 1)
            end2.setX(tileLeft + tileSize.width());
        mDoor->setDir(moveDir);
        if(rand1.x() > 0) {
            mDoor->setType(TDoor::Random);
        } else if(follow) {
            mDoor->setType(TDoor::Follow);
        }

        mDoor->setRect(QRectF(end1, QSize(end2.x()-end1.x(),end2.y()-end1.y())));
    }
}

QByteArray TTile::toByteArray(TObject *object) const
{

}

void TTile::loadFromByteArray(const QByteArray &byteArray)
{

}

QPixmap TTile::pixmap() const
{
    if(mPixmap)
        return mPixmap->pixmap();
    return QPixmap();
}

TPixmap *TTile::primitive() const
{
    return mPixmap;
}

TDoor *TTile::door() const
{
    return mDoor;
}

bool TTile::hasMoveModel() const
{
    return mHasMoveModel;
}

void TTile::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue)
{
    PropertyID pid = item->propertyId();
    if(pid == PID_OBJECT_POS) {
        if(mDoor) {
            // Slide door with tile
            QPointF offset = item->value().toPointF() - oldValue.toPointF();
            mDoor->slide(offset);
        }
    }
}

int TTile::getTileNo() const
{
    return mTileNo;
}

void TTile::setTileNo(int tileNo)
{
    mTileNo = tileNo;
}

int TTile::getTilesetNo() const
{
    return mTilesetNo;
}

void TTile::setTilesetNo(int tilesetNo)
{
    mTilesetNo = tilesetNo;
}

TTileId *TTile::tileId() const
{
    return mTileId;
}

void TTile::setTileId(TTileId *tileId)
{
    if(mTileId == tileId)
        return;

    mTileId = tileId;

    setUp();
}

QPointF TTile::getSpeed() const
{
    return mPropertySheet->getValue(PID_TILE_SPEED).toPointF();
}

QRectF TTile::getRect() const
{
    return mPixmap?QRectF(pos(),mPixmap->pixmap().size()):QRectF();
}

void TTile::setUp()
{
    if(mTileId) {
        mPixmap = mTileId->pixmap();
        mPropertySheet->setValue(P_IMAGE, mPixmap->fileName());
    }
}

int TTile::targetNumber() const
{
    return mTargetNumber;
}

TTile *TTile::target() const
{
    return mTarget;
}

void TTile::setTarget(TTile *target)
{
    mTarget = target;
}

void TTile::initPropertySheet()
{
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

    connect(mPropertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

}

QString TTile::typeString() const
{
    return T("Tile");
}

bool TTile::isCongener(TObject *object) const
{
    TTile *tile = dynamic_cast<TTile*>(object);
    if(!tile)
        return false;

    TPixmap *pixmap = tile->primitive();
    return mPixmap==pixmap || mPixmap->pixmap().size()==pixmap->pixmap().size();
}

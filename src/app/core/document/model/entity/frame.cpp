#include "frame.h"
#include "tile.h"
#include "../../base/tr.h"

static const QString P_TILE_LAYER = T("Tile Layer");
static const QString P_NUMBER = T("Number");
static const QString P_DURATION = T("Duration");

TFrame::TFrame(QObject *parent) :
    TObject(TObject::FRAME, parent)
  , mTile(nullptr)
  , mTileLayer(-1)
  , mTileNumber(-1)
{
    initPropertySheet();
}

TFrame::TFrame(TTile *tile, QObject *parent) :
    TObject(TObject::FRAME, parent)
  , mTile(tile)
  , mTileLayer(-1)
  , mTileNumber(-1)
{
    Q_ASSERT(tile);

    initPropertySheet();
}

TFrame::~TFrame()
{

}

TTile *TFrame::getTile() const
{
    return mTile;
}

void TFrame::setTile(TTile *tile)
{
    if(mTile == tile)
        return;

    mTile = tile;
}

QPixmap TFrame::getPixmap() const
{
    return mTile?mTile->pixmap():QPixmap();
}

int TFrame::getDuration() const
{
     return mDuration;
}

int TFrame::getTileNumber() const
{
    return mTileNumber;
}

int TFrame::getTileLayer() const
{
    return mTileLayer;
}

void TFrame::saveToStream(QDataStream &stream) const
{
    stream << mPropertySheet->getValue(PID_FRAME_TILE_LAYER).toInt();
    stream << mPropertySheet->getValue(PID_FRAME_TILE_NUMBER).toInt();
    stream << mPropertySheet->getValue(PID_FRAME_DURATION).toInt();
}

void TFrame::readFromStream(QDataStream &stream)
{
    stream >> mTileLayer;
    stream >> mTileNumber;
    stream >> mDuration;
    mTileNumber--;
    mPropertySheet->setValue(PID_FRAME_TILE_LAYER, mTileLayer);
    mPropertySheet->setValue(PID_FRAME_TILE_NUMBER, mTileNumber);
    mPropertySheet->setValue(PID_FRAME_DURATION, mDuration);
}

void TFrame::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_TILE_LAYER, PID_FRAME_TILE_LAYER)->setReadOnly(true);
    mPropertySheet->addProperty(PT_INT, P_NUMBER, PID_FRAME_TILE_NUMBER)->setReadOnly(true);
    mPropertySheet->addProperty(PT_INT, P_DURATION, PID_FRAME_DURATION)->setRange();
}

QString TFrame::typeString() const
{
    return T("Frame");
}

bool TFrame::isCongener(TObject *object) const
{
    return static_cast<TFrame*>(object);
}

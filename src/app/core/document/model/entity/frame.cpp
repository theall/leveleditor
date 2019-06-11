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

TFrame::~TFrame()
{

}

TTile *TFrame::getTile() const
{
    return mTile;
}

void TFrame::setTile(TTile *tile)
{
    mTile = tile;
}

QPixmap TFrame::getPixmap() const
{
    return mTile?mTile->pixmap():QPixmap();
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
    stream << mPropertySheet->getValue(PID_FRAME_TILE_LAYER).toPoint();
    stream << mPropertySheet->getValue(PID_FRAME_TILE_NUMBER).toPoint();
    stream << mPropertySheet->getValue(PID_FRAME_DURATION).toPoint();
}

void TFrame::readFromStream(QDataStream &stream)
{
    int duration;
    stream >> mTileLayer;
    stream >> mTileNumber;
    stream >> duration;
    mPropertySheet->setValue(PID_FRAME_TILE_LAYER, mTileLayer);
    mPropertySheet->setValue(PID_FRAME_TILE_NUMBER, mTileNumber);
    mPropertySheet->setValue(PID_FRAME_DURATION, duration);
}

void TFrame::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_TILE_LAYER, PID_FRAME_TILE_LAYER);
    mPropertySheet->addProperty(PT_INT, P_NUMBER, PID_FRAME_TILE_NUMBER);
    mPropertySheet->addProperty(PT_INT, P_DURATION, PID_FRAME_DURATION);
}

QString TFrame::typeString() const
{
    return T("Frame");
}

bool TFrame::isCongener(TObject *object) const
{
    return static_cast<TFrame*>(object);
}

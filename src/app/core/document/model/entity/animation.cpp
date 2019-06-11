#include "animation.h"
#include "tile.h"
#include "../../base/tr.h"

static const QString P_SEQUENCE = T("Sequence");
static const QString P_TILE_LAYER = T("Tile Layer");
static const QString P_TILE_NUMBER = T("Tile Number");
static const QString P_CURRENT_FRAME = T("Current frame");

TAnimation::TAnimation(QObject *parent) :
    TObject(TObject::ANIMATION, parent)
  , mTile(nullptr)
  , mTileLayer(-1)
  , mTileNumber(-1)
{
    initPropertySheet();
}

TAnimation::~TAnimation()
{

}

TFrameList TAnimation::frameList() const
{
    return mFrameList;
}

void TAnimation::setFrameList(const TFrameList &frameList)
{
    mFrameList = frameList;
}

QPixmap TAnimation::getIcon() const
{
    return mTile?mTile->pixmap():QPixmap();
}

void TAnimation::setTile(TTile *tile)
{
    mTile = tile;
}

TTile *TAnimation::getTile() const
{
    return mTile;
}

int TAnimation::getTileNumber() const
{
    return mTileNumber;
}

int TAnimation::getTileLayer() const
{
    return mTileLayer;
}

void TAnimation::saveToStream(QDataStream &stream) const
{
    int frameSequences = mPropertySheet->getValue(PID_ANIMATION_SEQUENCE).toInt();
    int frameCount = mFrameList.size();
    int tileLayer = mPropertySheet->getValue(PID_ANIMATION_TILE_LAYER).toInt();
    int tileNumber = mPropertySheet->getValue(PID_ANIMATION_TILE_NUMBER).toInt();

    // Current frame start from 1
    int currentFrame = mPropertySheet->getValue(PID_ANIMATION_CURRENT_FRAME).toInt();
    stream << frameSequences;
    stream << frameCount;
    stream << tileLayer;
    stream << tileNumber;
    stream << currentFrame;

    for(TFrame *frame : mFrameList) {
        frame->saveToStream(stream);
    }
}

void TAnimation::readFromStream(QDataStream &stream)
{
    int frameSequences; // Frame counter, shift next frame if frameSequences > current frame duration
    int frameCount;
    int tileLayer;
    int tileNumber;
    int currentFrame;
    stream >> frameSequences;
    stream >> frameCount;
    stream >> tileLayer;
    stream >> tileNumber;
    stream >> currentFrame;
    mFrameList.clear();
    for(int i=0;i<frameCount;i++) {
        TFrame *frame = new TFrame(this);
        frame->readFromStream(stream);
        mFrameList.append(frame);
    }
    mPropertySheet->setValue(PID_ANIMATION_SEQUENCE, frameSequences);
    mPropertySheet->setValue(PID_ANIMATION_TILE_LAYER, tileLayer);
    mPropertySheet->setValue(PID_ANIMATION_TILE_NUMBER, tileNumber);
    mPropertySheet->setValue(PID_ANIMATION_CURRENT_FRAME, currentFrame);
}

void TAnimation::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_SEQUENCE, PID_ANIMATION_SEQUENCE);
    mPropertySheet->addProperty(PT_INT, P_TILE_LAYER, PID_ANIMATION_TILE_LAYER);
    mPropertySheet->addProperty(PT_INT, P_TILE_NUMBER, PID_ANIMATION_TILE_NUMBER);
    mPropertySheet->addProperty(PT_INT, P_CURRENT_FRAME, PID_ANIMATION_CURRENT_FRAME);
}

QString TAnimation::typeString() const
{
    return T("Animation");
}

bool TAnimation::isCongener(TObject *object) const
{
    return static_cast<TAnimation*>(object);
}

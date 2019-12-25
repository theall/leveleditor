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

int TAnimation::getFrameSize() const
{
    return mFrameList.size();
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
    if(mTile == tile)
        return;

    mTile = tile;
}

void TAnimation::setTileNumber(int tileNumber)
{
    mTileNumber = tileNumber;
}

void TAnimation::setTileLayer(int tileLayer)
{
    mTileLayer = tileLayer;
}

QPixmap TAnimation::getFramePixmap(int index) const
{
    if(index<0 || index>=mFrameList.size())
        return QPixmap();

    return mFrameList.at(index)->getPixmap();
}

void TAnimation::clear()
{
    mFrameList.clear();
}

TFrame *TAnimation::getFrame(int index) const
{
    if(index<0 || index>=mFrameList.size())
        return nullptr;

    return mFrameList.at(index);
}

TTile *TAnimation::getFrameTile(int index) const
{
    if(index<0 || index>=mFrameList.size())
        return nullptr;

    return mFrameList.at(index)->getTile();
}

TPropertySheet *TAnimation::getFramePropertySheet(int index) const
{
    if(index<0 || index>=mFrameList.size())
        return nullptr;

    return mFrameList.at(index)->propertySheet();
}

TFrameList TAnimation::getFrameList() const
{
    return mFrameList;
}

int TAnimation::getTotalDuration() const
{
    int duration = 0;
    for(TFrame *frame : mFrameList) {
        duration += frame->getDuration();
    }
    return duration;
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
    int frameCount = mFrameList.size();
    // Current frame start from 1
    int currentFrame = mPropertySheet->getValue(PID_ANIMATION_CURRENT_FRAME).toInt();
    stream << mFrameSequences;
    stream << frameCount;
    stream << mTileLayer;
    stream << mTileNumber+1;
    stream << currentFrame;

    for(TFrame *frame : mFrameList) {
        frame->saveToStream(stream);
    }
}

void TAnimation::readFromStream(QDataStream &stream)
{
    int frameCount;
    int currentIndex;
    stream >> mFrameSequences;// Frame counter, shift next frame if frameSequences > current frame duration
    stream >> frameCount;
    stream >> mTileLayer;
    stream >> mTileNumber;
    stream >> currentIndex;
    mTileNumber--;
    mFrameList.clear();
    for(int i=0;i<frameCount;i++) {
        TFrame *frame = new TFrame(this);
        frame->readFromStream(stream);
        mFrameList.append(frame);
    }
    mPropertySheet->setValue(PID_ANIMATION_CURRENT_FRAME, currentIndex);
}

void TAnimation::initPropertySheet()
{
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

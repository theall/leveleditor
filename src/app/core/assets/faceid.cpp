#include "faceid.h"

TFaceId::TFaceId() :
    mId(-1)
  , mPixmap(nullptr)
{

}

TFaceId::TFaceId(int id, TPixmap *pixmap) :
    mId(id)
  , mPixmap(pixmap)
{

}

TFaceId::~TFaceId()
{
    if(mPixmap) {
        delete mPixmap;
        mPixmap = nullptr;
    }
}

int TFaceId::id() const
{
    return mId;
}

void TFaceId::setId(int id)
{
    mId = id;
}

TPixmap *TFaceId::pixmap() const
{
    return mPixmap;
}

void TFaceId::setPixmap(TPixmap *pixmap)
{
    mPixmap = pixmap;
}

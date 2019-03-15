#include "pixmap.h"

#include <QBitmap>
#include <QPainter>
#include <QFileInfo>

TPixmap::TPixmap(QObject *parent) :
    QObject(parent)
  , mIsValid(false)
{

}

TPixmap::~TPixmap()
{

}

QPixmap TPixmap::thumbnail() const
{
    return mThumbnail;
}

TPixmap &TPixmap::operator=(const TPixmap &pixmap)
{
    mFileFullName = pixmap.fileFullName();
    mFileName = pixmap.fileName();
    mThumbnail = pixmap.thumbnail();
    mPixmap = pixmap.pixmap();
    return *this;
}

int TPixmap::width() const
{
    return mPixmap.width();
}

int TPixmap::height() const
{
    return mPixmap.height();
}

bool TPixmap::isValid() const
{
    return mIsValid;
}

QString TPixmap::fileFullName() const
{
    return mFileFullName;
}

QString TPixmap::fileName() const
{
    return mFileName;
}

QPixmap TPixmap::pixmap() const
{
    return mPixmap;
}

void TPixmap::load(const QString &file)
{
    mFileFullName = file;
    mFileName = QFileInfo(file).fileName();

    reload();
}

void TPixmap::reload()
{           
    mIsValid = false;
    mPixmap.load(mFileFullName);
    if(mPixmap.isNull())
        return;

    QBitmap mask = mPixmap.createMaskFromColor(Qt::black);
    mPixmap.setMask(mask);

    int w = mPixmap.width();
    int h = mPixmap.height();
    if(w>64 || h>64)
    {
        QImage img = mPixmap.toImage();
        img.scaled(64, 64);
        mThumbnail = QPixmap::fromImage(img);
    } else {
        mThumbnail = mPixmap;
    }
    mIsValid = true;
}

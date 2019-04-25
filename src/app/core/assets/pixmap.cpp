#include "pixmap.h"

#include <QFile>
#include <QBitmap>
#include <QPainter>
#include <QFileInfo>

QByteArray loadImageFile(const QString &file) {
    QFile readFile(file);
    QByteArray result;
    if(readFile.open(QIODevice::ReadOnly))
    {
        result = readFile.readAll();
        readFile.close();
    }
    return result;
}

TPixmap::TPixmap(QObject *parent) :
    QObject(parent)
  , mIsValid(false)
{

}

TPixmap::TPixmap(const QString &file, QObject *parent) :
    QObject(parent)
  , mIsValid(false)
  , mFileFullName(file)
  , mFileName(QFileInfo(file).fileName())
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

QPixmap TPixmap::content()
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
    QByteArray imageData = loadImageFile(mFileFullName);
    mIsValid = mPixmap.loadFromData(imageData);
    if(!mIsValid)
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
}

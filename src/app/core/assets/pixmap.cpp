#include "pixmap.h"

#include <QFile>
#include <QBitmap>
#include <QPainter>
#include <QFileInfo>

#define DEFAULT_THUMB_SIZE 64

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
  , mThumbnailFixedSize(QSize(DEFAULT_THUMB_SIZE,DEFAULT_THUMB_SIZE))
{
    mPixmap = QPixmap(QSize(1,1));

    createMaskOnPixmap();
}

TPixmap::TPixmap(const QSize &size, QObject *parent) :
    QObject(parent)
  , mIsValid(false)
  , mPixmapFixedSize(size)
  , mThumbnailFixedSize(QSize(DEFAULT_THUMB_SIZE,DEFAULT_THUMB_SIZE))
{
    mPixmap = QPixmap(mPixmapFixedSize);

    createMaskOnPixmap();
}

TPixmap::TPixmap(const QString &file, QObject *parent) :
    QObject(parent)
  , mIsValid(false)
  , mFileFullName(file)
  , mThumbnailFixedSize(QSize(DEFAULT_THUMB_SIZE,DEFAULT_THUMB_SIZE))
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

QSize TPixmap::pixmapFixedSize() const
{
    return mPixmapFixedSize;
}

void TPixmap::setPixmapFixedSize(const QSize &pixmapFixedSize)
{
    mPixmapFixedSize = pixmapFixedSize;
}

QSize TPixmap::thumbnailFixedSize() const
{
    return mThumbnailFixedSize;
}

void TPixmap::setThumbnailFixedSize(const QSize &thumbnailFixedSize)
{
    mThumbnailFixedSize = thumbnailFixedSize;
}

void TPixmap::setPixmap(const QPixmap &pixmap)
{
    mPixmap = pixmap;

    createMaskOnPixmap();
}

void TPixmap::save()
{
    if(mFileFullName.isEmpty())
        return;

    mPixmap.save(mFileFullName);
}

void TPixmap::createMaskOnPixmap()
{
    QBitmap mask = mPixmap.createMaskFromColor(Qt::black);
    mPixmap.setMask(mask);

    updateThumbnail();
}

void TPixmap::updateThumbnail()
{
    int w = mPixmap.width();
    int h = mPixmap.height();
    if(w>mThumbnailFixedSize.width() || h>mThumbnailFixedSize.height())
    {
        QImage img = mPixmap.toImage();
        img.scaled(mThumbnailFixedSize);
        mThumbnail = QPixmap::fromImage(img);
    } else {
        mThumbnail = mPixmap;
    }
}

void TPixmap::setFileFullName(const QString &fileFullName)
{
    mFileFullName = fileFullName;
    mFileName = QFileInfo(fileFullName).fileName();
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

    if(!mPixmapFixedSize.isEmpty()) {
        QImage img = mPixmap.toImage();
        img.scaled(mPixmapFixedSize);
        mPixmap = QPixmap::fromImage(img);
    }

    createMaskOnPixmap();
}

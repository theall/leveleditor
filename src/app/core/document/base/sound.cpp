#include "sound.h"

#include <QFileInfo>

TSound::TSound(QObject *parent) :
    QObject(parent)
  , mMediaContent(nullptr)
{

}

TSound::~TSound()
{

}

TSound &TSound::operator=(const TSound &sound)
{
    mFileFullName = sound.fileFullName();
    mFileName = sound.fileName();
    QMediaContent *media = sound.mediaContent();
    if(media) {
        if(mMediaContent)
            delete mMediaContent;
        mMediaContent = new QMediaContent(*media);
    }
    return *this;
}

QMediaContent *TSound::mediaContent() const
{
    return mMediaContent;
}

QString TSound::fileFullName() const
{
    return mFileFullName;
}

QString TSound::fileName() const
{
    return mFileName;
}

void TSound::load(const QString &file)
{
    mFileFullName = file;
    mFileName = QFileInfo(file).fileName();

    reload();
}

void TSound::reload()
{
    if(mMediaContent)
        delete mMediaContent;

    mMediaContent = new QMediaContent(QUrl(mFileFullName));
}

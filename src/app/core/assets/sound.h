#ifndef SOUND_H
#define SOUND_H

#include <QList>
#include <QMediaContent>

class TSound : public QObject
{
    Q_OBJECT

public:
    TSound(QObject *parent = nullptr);
    ~TSound();

    void load(const QString &file);
    void reload();

    QString fileName() const;
    QString fileFullName() const;

    TSound &operator=(const TSound &sound);

    QMediaContent *mediaContent() const;

private:
    QString mFileFullName;
    QString mFileName;
    QMediaContent *mMediaContent;
};

typedef QList<TSound*> TSoundList;
#endif // SOUND_H

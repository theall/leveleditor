#ifndef DOCUMENT_PIXMAP_H
#define DOCUMENT_PIXMAP_H

#include <QObject>
#include <QPixmap>

class TPixmap : public QObject
{
    Q_OBJECT

public:
    TPixmap(QObject *parent = nullptr);
    ~TPixmap();

    void load(const QString &file);
    void reload();

    QString fileName() const;
    QString fileFullName() const;

    QPixmap pixmap() const;
    QPixmap thumbnail() const;
    TPixmap &operator=(const TPixmap &pixmap);

    int width() const;
    int height() const;

    bool isValid() const;

private:
    bool mIsValid;
    QString mFileFullName;
    QString mFileName;
    QPixmap mPixmap;
    QPixmap mThumbnail;
};

typedef QList<TPixmap*> TPixmaps;

#endif // DOCUMENT_PIXMAP_H

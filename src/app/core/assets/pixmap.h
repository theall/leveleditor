#ifndef DOCUMENT_PIXMAP_H
#define DOCUMENT_PIXMAP_H

#include <QObject>
#include <QSize>
#include <QList>
#include <QPixmap>

class TPixmap : public QObject
{
    Q_OBJECT

public:
    TPixmap(QObject *parent = nullptr);
    TPixmap(const QSize &size, QObject *parent = nullptr);
    TPixmap(const QString &file, QObject *parent = nullptr);
    ~TPixmap();

    void load(const QString &file);
    void reload();

    QString fileName() const;
    QString fileFullName() const;
    void setFileFullName(const QString &fileFullName);

    QPixmap pixmap() const;
    QPixmap content();
    QPixmap thumbnail() const;
    TPixmap &operator=(const TPixmap &pixmap);

    int width() const;
    int height() const;
    QSize size() const;

    bool isValid() const;

    QSize pixmapFixedSize() const;
    void setPixmapFixedSize(const QSize &pixmapFixedSize);

    QSize thumbnailFixedSize() const;
    void setThumbnailFixedSize(const QSize &thumbnailFixedSize);

    void setPixmap(const QPixmap &pixmap);
    void save();

private:
    bool mIsValid;
    QSize mPixmapFixedSize;
    QSize mThumbnailFixedSize;
    QString mFileFullName;
    QString mFileName;
    QPixmap mPixmap;
    QPixmap mThumbnail;

    void createMaskOnPixmap();
    void updateThumbnail();
};

typedef QList<TPixmap*> TPixmapList;

#endif // DOCUMENT_PIXMAP_H

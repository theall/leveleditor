#ifndef TMAPS_H
#define TMAPS_H

#include <QList>
#include <QObject>
#include <QPixmap>

class TDocument;
class TMap : public QObject
{
    Q_OBJECT

public:
    enum Type {
        ADV,
        CTF,
        VS
    };
    TMap(const Type &type, QObject *parent = Q_NULLPTR);
    ~TMap();

    QString name() const;
    void setName(const QString &name);

    QPixmap thumbnail() const;
    void setThumbnail(const QPixmap &thumbnail);

    bool isOpened() const;

    Type type() const;
    void setType(const Type &type);

    int id() const;
    void setId(int id);

signals:
    void thumbChanged(const QPixmap &newThumb);

private:
    Type mType;
    int mId;
    QString mName;
    QPixmap mThumbnail;
    TDocument *mDocument;
};
typedef QList<TMap*> TMapList;

class TMapBundle : public QObject
{
    Q_OBJECT

public:
    explicit TMapBundle(QObject *parent = Q_NULLPTR);
    ~TMapBundle();

    TMapList mapList() const;
    void setMapList(const TMapList &mapList);

    int add(TMap *map, int index = -1);
    int remove(TMap *map);
    int remove(int index);

signals:
    void mapAdded(TMap *map, int index);
    void mapRemoved(TMap *map, int index);

private:
    TMapList mMapList;
};

class TModule : public QObject
{
    Q_OBJECT

public:
    explicit TModule(QObject *parent = Q_NULLPTR);
    ~TModule();

    QString name() const;
    void setName(const QString &name);

    TMapBundle *getMapBundle(const TMap::Type &type) const;
    TMapBundle *getAdvBundle() const;
    TMapBundle *getVsBundle() const;
    TMapBundle *getCtfBundle() const;

private:
    QString mName;
    TMapBundle *mAdvBundle;
    TMapBundle *mVsBundle;
    TMapBundle *mCtfBundle;
};
typedef QList<TModule*> TModuleList;

#endif // TMAPS_H

#ifndef TMAPSVIEWMODEL_H
#define TMAPSVIEWMODEL_H

#include <QList>
#include <QObject>
#include <QPixmap>

class TMap : public QObject
{
    Q_OBJECT

public:
    explicit TMap(QObject *parent = Q_NULLPTR);
    ~TMap();

    QString name() const;
    void setName(const QString &name);

    QPixmap thumbnail() const;
    void setThumbnail(const QPixmap &thumbnail);

    bool dirty() const;
    void setDirty(bool dirty);

signals:
    void dirtyChanged(bool);
    void thumbnailChanged(const QPixmap &newThumb);

private:
    bool mDirty;
    QString mName;
    QPixmap mThumbnail;
};
typedef QList<TMap*> TMapList;

class TMapBundle : public QObject
{
    Q_OBJECT

public:
    enum Type {
        ADV,
        CTF,
        VS
    };

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

    TMapBundle *getMapBundle(const TMapBundle::Type &type) const;
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

class TMapsViewModel : public QObject
{
    Q_OBJECT

public:
    explicit TMapsViewModel(QObject *parent = Q_NULLPTR);
    ~TMapsViewModel();

    TModuleList moduleList() const;
    void setModuleList(const TModuleList &moduleList);

    int add(TModule *module, int index = -1);
    int remove(int index);
    int remove(TModule *module);

signals:
    void moduleAdded(TModule *module, int index);
    void moduleRemoved(TModule *module, int index);

private:
    TModuleList mModuleList;
};

#endif // TMAPSVIEWMODEL_H

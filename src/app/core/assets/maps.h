#ifndef TMAPS_H
#define TMAPS_H

#include <QList>
#include <QObject>
#include <QPixmap>

class TPixmap;
class TDocument;
class TMapBundle;
class TMap : public QObject
{
    Q_OBJECT

public:
    enum Type {
        ADV,
        CTF,
        VS
    };
    TMap(const Type &type, TMapBundle *parent);
    ~TMap();

    QString name() const;
    TPixmap *thumbnail() const;
    void setThumbnail(TPixmap *thumbnail);
    QPixmap thumbnailPixmap() const;

    static Type stringToType(const QString &typeName);

    bool isOpened() const;
    bool isDirty() const;

    Type type() const;
    void setType(const Type &type);

    int id() const;
    void setId(int id);

    TMapBundle *mapBundle() const;

    int indexInMapBundle() const;
    void setIndexInMapBundle(int indexInMapBundle);

    QString fullFilePath() const;
    void setFullFilePath(const QString &fullFilePath);

    TDocument *document() const;
    void setDocument(TDocument *document);

    TDocument *open();
    void close();
    bool save();

signals:
    void thumbChanged(const QPixmap &newThumb);

private:
    Type mType;
    int mId;
    QString mName;
    QString mFileFullPath;
    TPixmap *mThumbnail;
    TDocument *mDocument;
    TMapBundle *mMapBundle;
    int mIndexInMapBundle;
};
typedef QList<TMap*> TMapList;

class TModule;
class TMapBundle : public QObject
{
    Q_OBJECT

public:
    explicit TMapBundle(TModule *parent);
    ~TMapBundle();

    TMap *newMap(const TMap::Type &mapType);
    TMapList mapList() const;
    void setMapList(const TMapList &mapList);

    int add(TMap *map, int index = -1);
    int remove(TMap *map);
    int remove(int index);

    QString name() const;
    void setName(const QString &name);

    bool hasOpenedMap() const;
    bool hasDirtyMap() const;

    TMap *getMap(int index) const;

    TModule *getModule() const;

    int size() const;

    int getIndexInModule() const;
    void setIndexInModule(int indexInModule);
    int getNextId();

    void sort();

    TMap *find(const QString &mapFilePath) const;
    TMap *find(TDocument *document) const;

signals:
    void mapAdded(TMap *map, int index);
    void mapRemoved(TMap *map, int index);

private:
    QString mName;
    int mIndexInModule;
    bool mHasOpenedMap;
    bool mHasDirtyMap;
    TMapList mMapList;
    TModule *mModule;
    bool mSorted;
};
typedef QList<TMapBundle*> TMapBundleList;

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

    int size() const;
    bool hasOpenedMap() const;
    bool hasDirtyMap() const;

    int getIndexInModel() const;
    void setIndexInModel(int indexInModel);

    void sort();
    void getAvailableIds(int &adv, int &vs, int &ctf) const;

    TMap *find(const QString &mapFilePath) const;
    TMap *find(TDocument *document) const;

private:
    QString mName;
    bool mHasOpenedMap;
    bool mHasDirtyMap;
    int mIndexInModel;
    TMapBundle *mAdvBundle;
    TMapBundle *mVsBundle;
    TMapBundle *mCtfBundle;
    TMapBundleList mMapBundleList;
};
typedef QList<TModule*> TModuleList;

#endif // TMAPS_H

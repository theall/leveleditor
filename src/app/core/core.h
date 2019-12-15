#ifndef TCORE_H
#define TCORE_H

#include <QList>
#include <QString>
#include <QStringList>

#include "document/document.h"
#include "model/tilesetmodel.h"
#include "assets/maps.h"

class TItemModel;
class TMapsModel;
class TCharacterModel;
class TChunkModel;
class TShotModel;

class TCore : public QObject
{
    Q_OBJECT

public:
    TCore(QObject *parent=nullptr);
    ~TCore();

    bool loadResource(const QString &path, bool asynLoad = true) const;
    TDocument *open(const QString &file);
    TDocument *open(TMap *map);
    TDocument *newMap(const QString &moduleName, const TMap::Type &mapType, int mapId);

    TDocument *find(const QString &file);
    void closeDocument(TDocument *document);

    bool saveMap(TDocument *document);
    void saveAllMaps();
    bool hasDirtyDocument();

    QString getResourcePath() const;
    QStringList getModuleNames() const;
    void getModuleNameIds(QStringList &names, QList<int> &advList, QList<int> &vsList, QList<int> &ctfList) const;

    QList<TDocument *> documents() const;

    TTilesetModelList tilesetModelList() const;

    TCharacterModel *characterModel() const;

    TChunkModel *chunkModel() const;

    TShotModel *shotModel() const;

    TMapsModel *mapsModel() const;

    TTilesetModelManager *tilesetModelManager() const;

    TItemModel *getItemModel() const;

signals:
    void documentFileChanged(const QString &file);
    void ready();

private slots:
    void slotOnResourceLoadCompleted();

private:
    TMapsModel *mMapsModel;
    TFileSystemWatcher *mFileWatcher;
    TCharacterModel *mCharacterModel;
    TItemModel *mItemModel;
    TTilesetModelManager *mTilesetModelManager;
    TChunkModel *mChunkModel;
    TShotModel *mShotModel;
    QList<TDocument*> mDocuments;

    void addDocument(TDocument *document);
};

#endif // TCORE_H

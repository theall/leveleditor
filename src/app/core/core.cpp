#include "core.h"
#include "../utils/preferences.h"
#include "shared/filesystemwatcher.h"
#include "assets/assetsmanager.h"

TCore::TCore(QObject *parent) :
    QObject(parent)
  , mMapsModel(new TMapsModel(this))
  , mFileWatcher(new TFileSystemWatcher(this))
  , mCharacterModel(new TCharacterModel(this))
  , mTilesetModelManager(new TTilesetModelManager(this))
{
    TPreferences::instance();

    connect(mFileWatcher, SIGNAL(fileChanged(QString)), this, SIGNAL(documentFileChanged(QString)));
    connect(TAssetsManager::getInstance(), SIGNAL(loadCompleted()), this, SLOT(slotOnResourceLoadCompleted()));
}

TCore::~TCore()
{

}

bool TCore::loadResource(const QString &path, bool asynLoad) const
{
    return TAssetsManager::getInstance()->load(path, asynLoad);
}

TDocument *TCore::open(const QString &file)
{
    if(file.isEmpty())
        return nullptr;

    TDocument *document = find(file);
    if(!document)
    {
        TMap *map = mMapsModel->find(file);
        Q_ASSERT(map);
        document = map->open();
        addDocument(document);
    }
    return document;
}

TDocument *TCore::open(TMap *map)
{
    if(!map)
        return nullptr;

    TDocument *document = map->open();
    addDocument(document);
    return document;
}

TDocument *TCore::newMap(const QString &moduleName, const TMap::Type &mapType, int mapId)
{
    TMap *map = mMapsModel->createMap(moduleName, mapType, mapId);

    return open(map);
}

TDocument *TCore::find(const QString &file)
{
    for(TDocument *document : mDocuments)
    {
        if(document->fileName()==file)
            return document;
    }
    return nullptr;
}

void TCore::closeDocument(TDocument *document)
{
    if(document)
    {
        TMap *map = mMapsModel->find(document);
        if(!map)
            throw("Invalid map with unbind document!");

        mFileWatcher->removePath(document->fileName());
        mDocuments.removeAll(document);

        // Close at end.
        map->close();
    }
}

bool TCore::saveMap(TDocument *document)
{
    if(!document)
        return false;

    TMap *map = mMapsModel->find(document);
    if(!map)
        return false;

    return map->save();
}

void TCore::saveAllMaps()
{
    for(TDocument *d : mDocuments)
    {
        if(d->isDirty())
            d->save();
    }
}

bool TCore::hasDirtyDocument()
{
    for(TDocument *d : mDocuments)
    {
        if(d->isDirty())
            return true;
    }
    return false;
}

QString TCore::getResourcePath() const
{
    return TAssetsManager::getInstance()->getPath();
}

QStringList TCore::getModuleNames() const
{
    QStringList moduleNames;
    for(TModule *module : TAssetsManager::getInstance()->getModuleList()) {
        moduleNames.append(module->name());
    }
    return moduleNames;
}

void TCore::getModuleNameIds(QStringList &names, QList<int> &advList, QList<int> &vsList, QList<int> &ctfList) const
{
    names.clear();
    advList.clear();
    vsList.clear();
    ctfList.clear();
    for(TModule *module : TAssetsManager::getInstance()->getModuleList()) {
        int advId, vsId, ctfId;
        module->getAvailableIds(advId, vsId, ctfId);
        names.append(module->name());
        advList.append(advId);
        vsList.append(vsId);
        ctfList.append(ctfId);
    }
}

QList<TDocument *> TCore::documents() const
{
    return mDocuments;
}

void TCore::slotOnResourceLoadCompleted()
{
    TAssetsManager *assetsManager = TAssetsManager::getInstance();

    // Create tileset models
    TTilesetModelList tilesetModelList;
    TilesetList tilesetList = assetsManager->getTilesetList();
    for(TTileset *tileset : tilesetList) {
        TTilesetModel *tilesetModel = new TTilesetModel(tileset, this);
        tilesetModelList.append(tilesetModel);
    }

    mTilesetModelManager->setTilsetModelList(tilesetModelList);
    mCharacterModel->setFaceList(assetsManager->getFaceList());
    mMapsModel->setModuleList(assetsManager->getModuleList());
    emit ready();
}

TTilesetModelManager *TCore::tilesetModelManager() const
{
    return mTilesetModelManager;
}

TMapsModel *TCore::mapsModel() const
{
    return mMapsModel;
}

TCharacterModel *TCore::characterModel() const
{
    return mCharacterModel;
}

TTilesetModelList TCore::tilesetModelList() const
{
    return mTilesetModelManager->tilsetModelList();
}

void TCore::addDocument(TDocument *document)
{
    if(!document)
        return;

    mDocuments.append(document);
    mFileWatcher->addPath(document->fileName());
}

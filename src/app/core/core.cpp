#include "core.h"
#include "../utils/preferences.h"
#include "shared/filesystemwatcher.h"
#include "assets/assetsmanager.h"

TCore::TCore(QObject *parent) :
    QObject(parent)
  , mFileWatcher(new TFileSystemWatcher(this))
{
    TPreferences::instance();

    connect(mFileWatcher,
            SIGNAL(fileChanged(QString)),
            this,
            SIGNAL(documentFileChanged(QString)));
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
    TDocument *document = find(file);
    if(!document)
    {
        document = new TDocument(file);
        addDocument(document);
    }
    return document;
}

TDocument *TCore::newDocument(const QString &projectRoot, const QString &projectName)
{
    TDocument *document = TDocument::create(projectRoot, projectName);
    addDocument(document);
    return document;
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
        mFileWatcher->removePath(document->fileName());
        mDocuments.removeAll(document);
        delete document;
    }
}

void TCore::saveAllDocuments()
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

QList<TDocument *> TCore::documents() const
{
    return mDocuments;
}

void TCore::addDocument(TDocument *document)
{
    if(!document)
        return;

    mDocuments.append(document);
    mFileWatcher->addPath(document->fileName());
}

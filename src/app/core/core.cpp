#include "core.h"
#include "../utils/preferences.h"
#include "document/base/filesystemwatcher.h"

TCore::TCore(QObject *parent) :
    QObject(parent)
  , mPreferences(TPreferences::instance())
  , mFileWatcher(new TFileSystemWatcher(this))
{

}

TCore::~TCore()
{

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

TFileSystemWatcher *TCore::fileWatcher() const
{
    return mFileWatcher;
}

void TCore::addDocument(TDocument *document)
{
    if(!document)
        return;

    mDocuments.append(document);
    mFileWatcher->addPath(document->fileName());
}

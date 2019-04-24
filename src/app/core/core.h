#ifndef TCORE_H
#define TCORE_H

#include <QList>
#include <QString>
#include "document/document.h"
#include "model/tilesetmodel.h"
#include "model/charactermodel.h"
#include "model/mapsmodel.h"

class TCore : public QObject
{
    Q_OBJECT

public:
    TCore(QObject *parent=nullptr);
    ~TCore();

    bool loadResource(const QString &path, bool asynLoad = true) const;
    TDocument *open(const QString &file);    
    TDocument *newDocument(const QString &projectRoot, const QString &projectName);

    TDocument *find(const QString &file);
    void closeDocument(TDocument *document);

    void saveAllDocuments();
    bool hasDirtyDocument();

    QList<TDocument *> documents() const;

    TTilesetModelList tilesetModelList() const;

    TCharacterModel *characterModel() const;

    TMapsModel *mapsModel() const;

signals:
    void documentFileChanged(const QString &file);
    void ready();

private slots:
    void slotOnResourceLoadCompleted();

private:
    QList<TDocument*> mDocuments;
    TTilesetModelList mTilesetModelList;
    TFileSystemWatcher *mFileWatcher;
    TCharacterModel *mCharacterModel;
    TMapsModel *mMapsModel;

    void addDocument(TDocument *document);
};

#endif // TCORE_H

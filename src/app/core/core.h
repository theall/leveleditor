#ifndef TCORE_H
#define TCORE_H

#include "document/document.h"

class TPreferences;

class TCore : public QObject
{
public:
    TCore(QObject *parent=nullptr);
    ~TCore();

    TDocument *open(const QString &file);    
    TDocument *newDocument(const QString &projectRoot, const QString &projectName);

    TDocument *find(const QString &file);
    void closeDocument(TDocument *document);

    void saveAllDocuments();
    bool hasDirtyDocument();

    QList<TDocument *> documents() const;

    TFileSystemWatcher *fileWatcher() const;

private:
    TPreferences *mPreferences;
    QList<TDocument*> mDocuments;
    TFileSystemWatcher *mFileWatcher;

    void addDocument(TDocument *document);
};

#endif // TCORE_H

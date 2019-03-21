#ifndef TCORE_H
#define TCORE_H

#include <QList>
#include <QString>
#include "document/document.h"

class TCore : public QObject
{
    Q_OBJECT

public:
    TCore(QObject *parent=nullptr);
    ~TCore();

    void loadResource(const QString &path);
    TDocument *open(const QString &file);    
    TDocument *newDocument(const QString &projectRoot, const QString &projectName);

    TDocument *find(const QString &file);
    void closeDocument(TDocument *document);

    void saveAllDocuments();
    bool hasDirtyDocument();

    QList<TDocument *> documents() const;

signals:
    void documentFileChanged(const QString &file);

private:
    QList<TDocument*> mDocuments;
    TFileSystemWatcher *mFileWatcher;

    void addDocument(TDocument *document);
};

#endif // TCORE_H

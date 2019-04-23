#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QDir>
#include <QDateTime>
#include <QUndoStack>
#include <QGraphicsScene>

#include "model/scenemodel.h"
#include "undocommand/propertyundocommand.h"
#include "../assets/tileid.h"
#include "graphics/graphicsscene.h"

class TPropertyObject;
class TFileSystemWatcher;

class TDocument : public TPropertyObject
{
    Q_OBJECT

public:
    TDocument(const QString &file=QString(), QObject *parent=nullptr);
    ~TDocument();

    static TDocument *create(const QString &projectRoot, const QString &projectName);

    QUndoStack *undoStack() const;
    void addUndoCommand(QUndoCommand *command);

    QDir projectDir() const;

    bool save(const QString &fileName = QString());
    void reload();

    QString fileName() const;

    QString baseName() const;
    void setBaseName(const QString &baseName);

    TPropertySheet *propertySheet() const;

    QString projectRoot() const;
    void setProjectRoot(const QString &projectRoot);

    QString projectName() const;
    void setProjectName(const QString &projectName);

    bool isDirty() const;
    void setDirty(bool isDirty);

    QDateTime lastSaveTime() const;

    TTileId *getTileId(int tileSet, int tile);
    TGraphicsScene *graphicsScene() const;
    TSceneModel *getSceneModel() const;

signals:
    void projectFileChanged();
    void dirtyFlagChanged(bool isDirty);
    void saved();
    void resourceChanged();
    void iconChanged(TPixmap *newPixmap);

private slots:
    void slotModificationChanged(bool isClean);
    void slotFileChanged(const QString &file);
    void slotDirectoryChanged(const QString &dir);

private:
    bool mIsDirty;
    QDateTime mLastSaveTime;
    QString mLastExportFileName;
    QUndoStack *mUndoStack;
    QDir mProjectDir;
    QString mProjectRoot;
    QString mProjectName;
    QString mFileName;
    QString mBaseName;

    TFileSystemWatcher *mFileWatcher;
    TSceneModel *mSceneModel;
    TGraphicsScene *mGraphicsScene;

    void load(const QString &file);
    void setFileName(const QString &fileName);
    void initPropertySheet();
};

#endif // DOCUMENT_H

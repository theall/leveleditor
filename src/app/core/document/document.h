#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QDir>
#include <QDateTime>
#include <QUndoStack>
#include <QGraphicsScene>

#include "model/scenemodel.h"
#include "graphics/graphicsscene.h"
#include "undocommand/propertyundocommand.h"
#include "../assets/tileid.h"

enum EditMode {
    DEFAULT,
    INSERT
};

class TPropertyObject;
class TFileSystemWatcher;

class TDocument : public TPropertyObject
{
    Q_OBJECT

public:
    TDocument(const QString &file=QString(), QObject *parent=nullptr);
    ~TDocument();

    QUndoStack *undoStack() const;
    void addUndoCommand(QUndoCommand *command);

    QDir projectDir() const;

    bool save(const QString &fileName = QString());
    void reload();

    QString fileName() const;

    QString baseName() const;
    void setBaseName(const QString &baseName);

    TPropertySheet *propertySheet() const;

    bool isDirty() const;
    void setDirty(bool isDirty);

    QDateTime lastSaveTime() const;

    TTileId *getTileId(int tileSet, int tile);
    TGraphicsScene *graphicsScene() const;
    TSceneModel *getSceneModel() const;

    void setTileStamp(TTileId *tileStamp);

    EditMode getEditMode() const;
    void setEditMode(const EditMode &editMode);

signals:
    void projectFileChanged();
    void dirtyFlagChanged(bool isDirty);
    void saved();
    void resourceChanged();
    void iconChanged(TPixmap *newPixmap);
    // Send to external
    void editModeChanged(const EditMode &current, const EditMode &prev);

private slots:
    void slotModificationChanged(bool isClean);
    void slotFileChanged(const QString &file);
    void slotDirectoryChanged(const QString &dir);
    void slotUndoStackIndexChanged(int index);

private:
    bool mIsDirty;
    QDateTime mLastSaveTime;
    QUndoStack *mUndoStack;
    QString mFileName;
    QString mBaseName;

    TFileSystemWatcher *mFileWatcher;
    TSceneModel *mSceneModel;
    TGraphicsScene *mGraphicsScene;
    TTileId *mTileStamp;
    EditMode mEditMode;
    int mLastUndoStackIndex;
    QUndoCommand *mLastUndoCommand;

    void load(const QString &file);
    void setFileName(const QString &fileName);
    void initPropertySheet();
};

#endif // DOCUMENT_H

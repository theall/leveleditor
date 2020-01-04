#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QDir>
#include <QDateTime>
#include <QUndoStack>
#include <QGraphicsScene>

#include "model/scenemodel.h"
#include "graphics/graphicsscene.h"
#include "undocommand/propertyundocommand.h"
#include "undocommand/objectaddcommand.h"
#include "../assets/maps.h"

enum EditMode {
    DEFAULT,
    INSERT
};

class TFaceId;
class TItemId;
class TChunkId;
class TShotId;
class TTileId;
class TPixmap;
class TPropertyObject;
class TFileSystemWatcher;

class TDocument : public TPropertyObject
{
    Q_OBJECT

public:
    TDocument(const TMap::Type &mapType, QObject *parent=nullptr);
    TDocument(const TMap::Type &mapType, const QString &file, QObject *parent=nullptr);
    ~TDocument();

    QUndoStack *undoStack() const;
    void addUndoCommand(QUndoCommand *command);

    QDir projectDir() const;

    bool save(const QString &fileName = QString());
    void reload();

    QString fileName() const;
    void setFileName(const QString &fileName);

    QString baseName() const;
    void setBaseName(const QString &baseName);

    TPropertySheet *propertySheet() const;

    bool isDirty() const;
    void setDirty(bool isDirty);

    QDateTime lastSaveTime() const;

    TTileId *getTileId(int tileSet, int tile);
    TGraphicsScene *graphicsScene() const;
    TSceneModel *getSceneModel() const;

    void setTileStamp(TTileId *tileId);
    void setFaceStamp(TFaceId *faceId);
    void setItemStamp(TItemId *itemId);
    void setChunkStamp(TChunkId *chunkId);
    void setShotStamp(TShotId *shotId);
    
    EditMode getEditMode() const;
    void setEditMode(const EditMode &editMode);

    void cmdAddObject(const TObject *object, TBaseModel *baseModel);
    void cmdAddObject(const TObjectList &objectList, TBaseModel *baseModel);
    void cmdRemoveObject(const TObject *object, TBaseModel *baseModel);
    void cmdRemoveObject(const TObjectList &objectList, TBaseModel *baseModel);

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

    void load(const QString &file);
    void initPropertySheet();
    void connetSignalsToSlots();
    void internalAddRemoveObjectCommand(TObjectAddCommand::Command stamp,
                                        TBaseModel *baseModel,
                                        const TObjectList &objectList
                                        );
};

#endif // DOCUMENT_H

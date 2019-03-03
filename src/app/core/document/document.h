#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QDir>
#include <QDateTime>
#include <QUndoStack>
#include <QGraphicsScene>

#include "model/scenemodel.h"
#include "base/propertyundocommand.h"

class TPixmap;
class TSound;
class TPropertyObject;
class TCachedPixmap;
class TCachedSound;
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

    void cmdAddLayer(const QString &name);
    void cmdRemoveLayer(TLayer *layer);
    void cmdRemoveLayer(int layerIndex);

    TPixmap *getPixmap(const QString &file) const;
    QString getPixmapRelativePath(const QString &file) const;
    TSound *getSound(const QString &file) const;
    QString getSoundRelativePath(const QString &file) const;

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

    TLayersModel *layersModel() const;
    TGraphicsScene *graphicsScene() const;

    TCachedPixmap *getCachedPixmaps() const;
    TCachedSound *getCachedSounds() const;

    QPixmap getIcon() const;
    void setIcon(const QPixmap &icon);

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
    void slotIconPropertyItemChanged(const QVariant &oldValue);

private:
    bool mIsDirty;
    QDateTime mLastSaveTime;
    QString mLastExportFileName;
    QUndoStack *mUndoStack;
    QDir mProjectDir;
    QDir mSoundDir;
    QString mProjectRoot;
    QString mProjectName;
    QString mFileName;
    QString mBaseName;
    QPixmap mIcon;

    TFileSystemWatcher *mFileWatcher;
    TCachedPixmap *mCachedPixmaps;
    TCachedSound *mCachedSounds;
    TSceneModel *mSceneModel;

    void load(const QString &file);
    void setFileName(const QString &fileName);
    void initPropertySheet();
};

#endif // DOCUMENT_H

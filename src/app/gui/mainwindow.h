#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QShortcut>
#include <QActionGroup>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class TZoomComboBox;
class TAboutDialog;
class TSelectRootDialog;
class TUndoDock;
class TMapsDock;
class TMiniSceneDock;
class TPropertiesDock;
class TTabWidget;
class TCentralWidget;
class TLoadingDialog;
class TTilesetDock;
class TCharacterDock;
class TLayerDock;
class TNewMapDialog;

class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TMainWindow(QWidget *parent = nullptr);
    ~TMainWindow();

    void enableUndoAction(bool enabled = true);
    void enableRedoAction(bool enabled = true);
    void enableSaveAction(bool enabled = true);
    void enableSaveAllAction(bool enabled = true);
    void enableCloseAction(bool enabled = true);
    void enableCloseAllAction(bool enabled = true);
    void enableRunAction(bool enabled = true);

    void checkSelectAction();
    void checkInsertAction();

    void triggerCurrentSelectedAction();

    void addRecentFile(const QString &file);
    void setStatusMessage(const QString &message, int timeOut = 3000);
    void asShow();

    TUndoDock *getUndoDock() const;
    TMapsDock *getMapsDock() const;
    TPropertiesDock *getPropertyDock() const;
    TTabWidget *getTabWidget() const;
    TLoadingDialog *getLoadingDialog() const;
    TMiniSceneDock *getMiniSceneDock() const;
    TZoomComboBox *getZoomComboBox() const;
    TTilesetDock *getTilesetDock() const;
    TCharacterDock *getCharacterDock() const;
    TLayerDock *getLayerDock() const;
    TNewMapDialog *getNewMapDialog() const;

signals:
    void requestOpenGame(const QString &gameRoot);
    void requestCreateNewMap();
    void requestOpenMap(const QString &mapName);
    void requestSaveCurrentMap();
    void requestSaveAllMaps();
    void requestUndo();
    void requestRedo();
    void requestExitApp(bool &approved);
    void requestCloseCurrentMap();
    void requestCloseAllMaps();
    void requestDisplayMapProperties();
    void requestRunCurrentMap();
    void requestShowBorder(bool);
    void onActionSelectPushed();
    void onActionInsertPushed();

private slots:
    // From TTabWidget
    void slotOnTabCountChanged(int count);
    void slotOnActionSaveTriggered();
    void slotOnTabIndexChanged(int index);

    // From self
    void slotOpenRecentFile();
    void slotSceneScaleChanged(qreal scale);

    // From TPreferences
    void slotHideMenuBarChanged(bool checked);
    void slotToolbarIconSizeChanged(int size);
    void slotHideStatusBarChanged(bool checked);
    void slotStyleChanged(const QString &style);

    void on_actionNewMap_triggered();
    void on_actionOpenGame_triggered();
    void on_actionClearRecentFiles_triggered();
    void on_actionAboutQt_triggered();
    void on_actionSaveMap_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionSaveAllMaps_triggered();
    void on_actionExit_triggered();
    void on_actionCloseMap_triggered();
    void on_actionCloseAllMaps_triggered();
    void on_actionExport_triggered();
    void on_actionExportAs_triggered();
    void on_actionSettings_triggered();
    void on_actionDocumentProperties_triggered();
    void on_actionSelectMode_triggered();
    void on_actionInsertMode_triggered();
    void on_actionAbout_triggered();
    void on_actionRun_triggered();
    void on_actionShowBorder_triggered(bool arg1);
    void on_actionAlwaysOnTop_triggered(bool arg1);
    void on_actionCloseGame_triggered();

private:
    Ui::MainWindow *ui;

    QAction *mViewsAndToolbarsMenu;
    QList<QAction*> mRecentFilesAction;

    TCentralWidget *mCentralWidget;
    TUndoDock *mUndoDock;
    TMapsDock *mMapsDock;
    TMiniSceneDock *mMiniSceneDock;
    TPropertiesDock *mPropertyDock;
    TTilesetDock *mTilesetDock;
    TCharacterDock *mCharacterDock;
    TLayerDock *mLayerDock;

    TAboutDialog *mAboutDialog;
    TLoadingDialog *mLoadingDialog;
    TNewMapDialog *mNewMapDialog;
    TZoomComboBox *mZoomComboBox;

    bool mHideMenu;
    QActionGroup *mActionGroup;

    void updateRecentFiles();
    void loadConfig();
    void saveConfig();
    void raiseLoadingDialog();
    void checkActionWithoutEmitSignal(QAction *action, bool checked);

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
};

#endif

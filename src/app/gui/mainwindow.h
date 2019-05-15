#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QShortcut>
#include <QActionGroup>
#include <QMainWindow>

enum SelectedAction
{
    SA_Default,
    SA_AddCollideArea,
    SA_AddAttackArea,
    SA_AddUndertakeArea,
    SA_AddTerrianArea,
    SA_AddFireObject,
    SA_COUNT
};

enum AreaType
{
    AT_COLLIDE,
    AT_ATTACK,
    AT_TERRIAN,
    AT_UNDERTAKE,
    AT_COUNT
};

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

    SelectedAction getSelectedAction();
    void triggerCurrentSelectedAction();
    void setSelectedAction(SelectedAction action);

    void addRecentFile(const QString &file);
    void setStatusMessage(const QString &message, int timeOut = 3000);
    void show();

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

signals:
    void requestCreateProject();
    void requestOpenProject(const QString &file);
    void requestSaveCurrentProject();
    void requestSaveAllProjects();
    void requestUndo();
    void requestRedo();
    void requestExitApp(bool &approved);
    void requestCloseCurrentProject();
    void requestCloseAllProjects();
    void requestDisplayProjectProperties();
    void requestShowFrameSceneArea(AreaType areaType, bool visible);
    void onFrameSceneActionSelected(SelectedAction selectedAction);
    void requestRunCurrentProject();
    void requestShowBorder(bool);

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

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionClearRecentFiles_triggered();
    void on_actionAboutQt_triggered();
    void on_actionSave_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionSaveAll_triggered();
    void on_actionExit_triggered();
    void on_actionClose_triggered();
    void on_actionCloseAll_triggered();
    void on_actionExport_triggered();
    void on_actionExportAs_triggered();
    void on_actionPreferences_triggered();
    void on_actionDocumentProperties_triggered();
    void on_actionShowCollideArea_triggered(bool checked);
    void on_actionShowTerrianArea_triggered(bool checked);
    void on_actionShowAttackArea_triggered(bool checked);
    void on_actionShowUndertakeArea_triggered(bool checked);
    void on_actionAddCollideArea_triggered(bool checked);
    void on_actionAddFireObject_triggered(bool checked);
    void on_actionAddAttackArea_triggered(bool checked);
    void on_actionAddUndertakeArea_triggered(bool checked);
    void on_actionAddTerrianArea_triggered(bool checked);
    void on_actionSelect_triggered(bool checked);
    void on_actionAbout_triggered();
    void on_actionRun_triggered();

    void on_actionShowBorder_toggled(bool arg1);

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

    TZoomComboBox *mZoomComboBox;

    bool mHideMenu;
    QActionGroup *mActionGroup;

    void updateRecentFiles();
    void loadConfig();
    void saveConfig();
    void raiseLoadingDialog();

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

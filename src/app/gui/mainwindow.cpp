#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogs/aboutdialog.h"
#include "dialogs/preferencesdialog.h"
#include "dialogs/selectrootdialog.h"
#include "dialogs/loadingdialog.h"

#include "component/centralwidget.h"
#include "component/undodock/undodock.h"
#include "component/mapsdock/mapsdock.h"
#include "component/miniscenedock/miniscenedock.h"
#include "component/layerdock/layerdock.h"
#include "component/tabwidget/tabwidget.h"
#include "component/characterdock/characterdock.h"
#include "component/propertydock/propertiesdock.h"
#include "component/tilesetdock/tilesetdock.h"

#include "widgets/zoomcombobox.h"

#include "../utils/preferences.h"

#include <QUrl>
#include <QMimeData>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyleFactory>

TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mCentralWidget(new TCentralWidget(this))
  , mUndoDock(new TUndoDock(this))
  , mMapsDock(new TMapsDock(this))
  , mMiniSceneDock(new TMiniSceneDock(this))
  , mPropertyDock(new TPropertiesDock(this))
  , mTilesetDock(new TTilesetDock(this))
  , mCharacterDock(new TCharacterDock(this))
  , mLayerDock(new TLayerDock(this))
  , mAboutDialog(new TAboutDialog(this))
  , mLoadingDialog(new TLoadingDialog(this))
  , mZoomComboBox(new TZoomComboBox(this))
  , mHideMenu(false)
  , mActionGroup(new QActionGroup(this))
{
    ui->setupUi(this);

    // Initialize menu
    ui->actionNew->setShortcuts(QKeySequence::New);
    ui->actionOpen->setShortcuts(QKeySequence::Open);
    ui->actionSave->setShortcuts(QKeySequence::Save);
    ui->actionSaveAs->setShortcuts(QKeySequence::SaveAs);
    ui->actionClose->setShortcuts(QKeySequence::Close);
    ui->actionQuit->setShortcuts(QKeySequence::Quit);
    ui->actionCut->setShortcuts(QKeySequence::Cut);
    ui->actionCopy->setShortcuts(QKeySequence::Copy);
    ui->actionPaste->setShortcuts(QKeySequence::Paste);
    ui->actionDelete->setShortcuts(QKeySequence::Delete);
    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionSaveAll->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionCloseAll->setEnabled(false);
    ui->actionClearRecentFiles->setEnabled(false);

    // Frame menu
    mActionGroup->addAction(ui->actionSelect);
    mActionGroup->addAction(ui->actionAddAttackArea);
    mActionGroup->addAction(ui->actionAddUndertakeArea);
    ui->actionSelect->setChecked(true);

    // Add recent file actions to the recent files menu
    for(int i=0;i<TPreferences::MAX_RECENT_FILES;i++)
    {
        QAction* action = new QAction(this);
        ui->menuRecentFiles->insertAction(ui->actionClearRecentFiles, action);
        action->setVisible(false);
        connect(action, SIGNAL(triggered()), this, SLOT(slotOpenRecentFile()));
        mRecentFilesAction.append(action);
    }
    ui->menuRecentFiles->insertSeparator(ui->actionClearRecentFiles);

    // Make sure Ctrl+= also works for zooming in
    QList<QKeySequence> keys = QKeySequence::keyBindings(QKeySequence::ZoomIn);
    keys += QKeySequence(tr("Ctrl+="));
    keys += QKeySequence(tr("+"));
    ui->actionZoomIn->setShortcuts(keys);
    keys = QKeySequence::keyBindings(QKeySequence::ZoomOut);
    keys += QKeySequence(tr("-"));
    ui->actionZoomOut->setShortcuts(keys);
    ui->menuEdit->insertSeparator(ui->actionCut);
    ui->menuEdit->insertSeparator(ui->actionPreferences);
    ui->MainToolBar->addSeparator();
    // Add the 'Views and Toolbars' submenu.This needs to happen after all
    // the dock widgets and toolbars have been added to the main window
    mViewsAndToolbarsMenu = new QAction(tr("Views and Toolbars"), this);
    ui->menuView->insertAction(ui->actionShowGrid, mViewsAndToolbarsMenu);
    ui->menuView->insertSeparator(ui->actionShowGrid);

    addDockWidget(Qt::LeftDockWidgetArea, mMapsDock);
    addDockWidget(Qt::RightDockWidgetArea, mTilesetDock);
    addDockWidget(Qt::RightDockWidgetArea, mCharacterDock);
    addDockWidget(Qt::LeftDockWidgetArea, mUndoDock);
    addDockWidget(Qt::RightDockWidgetArea, mMiniSceneDock);
    addDockWidget(Qt::RightDockWidgetArea, mPropertyDock);
    addDockWidget(Qt::LeftDockWidgetArea, mLayerDock);
    tabifyDockWidget(mMapsDock, mTilesetDock);
    tabifyDockWidget(mTilesetDock, mCharacterDock);

    mViewsAndToolbarsMenu->setMenu(createPopupMenu());

    setCentralWidget(mCentralWidget);
    connect(mCentralWidget->tabWidget(), SIGNAL(currentChanged(int)), this, SLOT(slotOnTabIndexChanged(int)));
    connect(mCentralWidget->tabWidget(), SIGNAL(onTabCountChanged(int)), this, SLOT(slotOnTabCountChanged(int)));
    connect(mCentralWidget->tabWidget(), SIGNAL(onActionSaveTriggered()), this, SLOT(slotOnActionSaveTriggered()));

    // Status bar
    connect(mZoomComboBox, SIGNAL(scaleChanged(qreal)), this, SLOT(slotSceneScaleChanged(qreal)));
    ui->statusBar->addPermanentWidget(mZoomComboBox);

    setAcceptDrops(true);

    loadConfig();
}

TMainWindow::~TMainWindow()
{
    saveConfig();

    delete ui;
}

void TMainWindow::enableUndoAction(bool enabled)
{
    ui->actionUndo->setEnabled(enabled);
}

void TMainWindow::enableRedoAction(bool enabled)
{
    ui->actionRedo->setEnabled(enabled);
}

void TMainWindow::enableSaveAction(bool enabled)
{
    ui->actionSave->setEnabled(enabled);
}

void TMainWindow::enableSaveAllAction(bool enabled)
{
    ui->actionSaveAll->setEnabled(enabled);
}

void TMainWindow::enableCloseAction(bool enabled)
{
    ui->actionClose->setEnabled(enabled);
}

void TMainWindow::enableCloseAllAction(bool enabled)
{
    ui->actionCloseAll->setEnabled(enabled);
}

void TMainWindow::enableRunAction(bool enabled)
{
    ui->actionRun->setEnabled(enabled);
}

SelectedAction TMainWindow::getSelectedAction()
{
    SelectedAction selectedAction = SA_Default;
    QAction *checkedAction = mActionGroup->checkedAction();
    if(checkedAction==ui->actionAddAttackArea)
        selectedAction = SA_AddAttackArea;
    else if(checkedAction==ui->actionAddCollideArea)
        selectedAction = SA_AddCollideArea;
    else if(checkedAction==ui->actionAddTerrianArea)
        selectedAction = SA_AddTerrianArea;
    else if(checkedAction==ui->actionAddUndertakeArea)
        selectedAction = SA_AddUndertakeArea;

    return selectedAction;
}

void TMainWindow::triggerCurrentSelectedAction()
{
    QAction *checkedAction = mActionGroup->checkedAction();
    if(checkedAction)
        checkedAction->trigger();
}

void TMainWindow::setSelectedAction(SelectedAction action)
{
    if(action==SA_AddAttackArea)
        ui->actionAddAttackArea->setChecked(true);
    else if(action==SA_AddCollideArea)
        ui->actionAddCollideArea->setChecked(true);
    else if(action==SA_AddTerrianArea)
        ui->actionAddTerrianArea->setChecked(true);
    else if(action==SA_AddUndertakeArea)
        ui->actionAddUndertakeArea->setChecked(true);
    else
        ui->actionSelect->setChecked(true);
}

void TMainWindow::addRecentFile(const QString &file)
{
    QStringList recentFiles = TPreferences::instance()->recentFiles();
    recentFiles.removeAll(file);
    recentFiles.prepend(file);
    TPreferences::instance()->setRecentFiles(recentFiles);
    updateRecentFiles();
}

void TMainWindow::setStatusMessage(const QString &message, int timeOut)
{
    statusBar()->showMessage(message, timeOut);
}

void TMainWindow::show()
{
    QMainWindow::show();

#ifndef GUI_STAND_ALONE
    raiseLoadingDialog();
#endif
}

void TMainWindow::on_actionOpen_triggered()
{
    QString filter = tr("All Files (*);;");
    QString selectedFilter = tr("Maps (*.dat)");
    filter += selectedFilter;
    TPreferences *pref = TPreferences::instance();
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                tr("Select scenes"),
                pref->lastOpenPath(),
                filter,
                &selectedFilter);

    if(!fileNames.isEmpty())
        pref->setLastOpenPath(QDir(fileNames.at(0)).absolutePath());

    for(QString file : fileNames) {
        emit requestOpenProject(file);
    }
}

void TMainWindow::on_actionClearRecentFiles_triggered()
{
    TPreferences::instance()->setRecentFiles(QStringList());
    updateRecentFiles();
}
    
void TMainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (!mimeData->hasUrls())
        return;

    event->accept();
}
    
void TMainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void TMainWindow::dropEvent(QDropEvent *event)
{
    event->accept();
    const QMimeData *mimeData = event->mimeData();
    for(QUrl url : mimeData->urls())
    {
        emit requestOpenProject(url.toLocalFile());
    }
}

void TMainWindow::slotOpenRecentFile()
{
    QAction *action = dynamic_cast<QAction*>(sender());
    if(action)
    {
        emit requestOpenProject(action->data().toString());
    }
}

void TMainWindow::slotSceneScaleChanged(qreal scale)
{
    if(TTabContainer *tabContainer = getTabWidget()->currentContainer())
        if(TGraphicsView *graphicsView = tabContainer->graphicsView())
            graphicsView->setScale(scale);
}

void TMainWindow::slotHideMenuBarChanged(bool checked)
{
    ui->mainMenu->setVisible(!checked);
}

void TMainWindow::slotToolbarIconSizeChanged(int newSize)
{
    QSize size(newSize, newSize);
    for(QObject *o : children())
    {
        if(QToolBar* tb = qobject_cast<QToolBar*>(o))
            tb->setIconSize(size);
    }
}

void TMainWindow::slotHideStatusBarChanged(bool checked)
{
    statusBar()->setVisible(!checked);
}

void TMainWindow::slotStyleChanged(const QString &style)
{
    qApp->setStyle(QStyleFactory::create(style));
}

void TMainWindow::on_actionNew_triggered()
{
    emit requestCreateProject();
}

TMapsDock *TMainWindow::getMapsDock() const
{
    return mMapsDock;
}

TUndoDock *TMainWindow::getUndoDock() const
{
    return mUndoDock;
}
        
// Updates the recent files menu.
void TMainWindow::updateRecentFiles()
{
    QStringList files = TPreferences::instance()->recentFiles();
    int numRecentFiles = qMin(files.count(), TPreferences::MAX_RECENT_FILES);
    for(int i=0;i<numRecentFiles;i++)
    {
        mRecentFilesAction[i]->setText(QString("%1: %2").arg(i+1).arg(files[i]));
        mRecentFilesAction[i]->setData(files[i]);
        mRecentFilesAction[i]->setVisible(true);
    }

    for(int j=numRecentFiles;j<TPreferences::MAX_RECENT_FILES;j++)
        mRecentFilesAction[j]->setVisible(false);

    ui->menuRecentFiles->setEnabled(numRecentFiles > 0);
    ui->actionClearRecentFiles->setEnabled(numRecentFiles > 0);
}

void TMainWindow::saveConfig()
{
    TPreferences *preferences = TPreferences::instance();
    preferences->setWindowGeometryState(saveGeometry(), saveState());
    preferences->setSceneScale(mZoomComboBox->scaleValue());
}

void TMainWindow::raiseLoadingDialog()
{
    if(mLoadingDialog->isEnd())
        return;

    int retCode = mLoadingDialog->exec();
    if(retCode == QDialog::Rejected) {
        close();
    }
}

void TMainWindow::closeEvent(QCloseEvent *event)
{
#ifdef GUI_STAND_ALONE
    event->accept();
#else
    bool approve = false;
    emit requestExitApp(approve);
    if(approve)
        event->accept();
    else
        event->ignore();
#endif
}

void TMainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key==Qt::Key_F10 || key==Qt::Key_Alt)
    {
        TPreferences *pref = TPreferences::instance();
        mHideMenu = pref->hideMenuBar();
        if(!ui->mainMenu->isVisible())
        {
            pref->setHideMenuBar(false);
        }
    }
    QMainWindow::keyPressEvent(event);
}

void TMainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key==Qt::Key_F10 || key==Qt::Key_Alt)
    {
        TPreferences *pref = TPreferences::instance();
        if(ui->mainMenu->isVisible() && mHideMenu)
        {
            pref->setHideMenuBar(true);
        }
    }
    QMainWindow::keyReleaseEvent(event);
}

void TMainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

TPropertiesDock *TMainWindow::getPropertyDock() const
{
    return mPropertyDock;
}

TTabWidget *TMainWindow::getTabWidget() const
{
    return mCentralWidget->tabWidget();
}

void TMainWindow::slotOnTabCountChanged(int count)
{
    ui->actionClose->setEnabled(count>0);
    ui->actionCloseAll->setEnabled(count>0);
}

void TMainWindow::slotOnActionSaveTriggered()
{
    ui->actionSave->trigger();
}

void TMainWindow::slotOnTabIndexChanged(int)
{
    TGraphicsView *graphicsView = mCentralWidget->tabWidget()->currentGraphicsView();
    if(graphicsView) {
        mZoomComboBox->setScaleValue(graphicsView->scale(), false);
    }
}

void TMainWindow::on_actionSave_triggered()
{
    emit requestSaveCurrentProject();
}

void TMainWindow::on_actionRedo_triggered()
{
    emit requestRedo();
}

void TMainWindow::on_actionUndo_triggered()
{
    emit requestUndo();
}

void TMainWindow::on_actionSaveAll_triggered()
{
    emit requestSaveAllProjects();
}

void TMainWindow::on_actionExit_triggered()
{
    close();
}

void TMainWindow::loadConfig()
{
    TPreferences *prefs = TPreferences::instance();
    connect(prefs, SIGNAL(toolbarIconSizeChanged(int)), this, SLOT(slotToolbarIconSizeChanged(int)));
    connect(prefs, SIGNAL(hideMenuBarChanged(bool)), this, SLOT(slotHideMenuBarChanged(bool)));
    connect(prefs, SIGNAL(hideStatusBarChanged(bool)), this, SLOT(slotHideStatusBarChanged(bool)));
    connect(prefs, SIGNAL(styleChanged(QString)), this, SLOT(slotStyleChanged(QString)));

    QByteArray geometry, state;
    prefs->windowGeometryState(&geometry, &state);
    if(geometry.isEmpty())
        showMaximized();
    else
        restoreGeometry(geometry);

    if(!state.isEmpty())
        restoreState(state);

    //    ui->actionShowGrid->setChecked(preferences->showGrid());

    if(prefs->hideMenuBar())
        ui->mainMenu->setVisible(false);

    if(prefs->hideStatusBar())
    {
        statusBar()->setVisible(false);
    }
    slotToolbarIconSizeChanged(prefs->toolbarIconSize());

    if(prefs->alwaysOnTop())
        ui->actionAlwaysOnTop->trigger();

    mZoomComboBox->setScaleValue(prefs->sceneScale());

    slotStyleChanged(prefs->style());
    updateRecentFiles();
}

void TMainWindow::on_actionClose_triggered()
{
    emit requestCloseCurrentProject();
}

void TMainWindow::on_actionCloseAll_triggered()
{
    emit requestCloseAllProjects();
}

void TMainWindow::on_actionExport_triggered()
{

}

void TMainWindow::on_actionExportAs_triggered()
{

}

void TMainWindow::on_actionPreferences_triggered()
{
    TPreferencesDialog::showPreferences(this);
}

void TMainWindow::on_actionDocumentProperties_triggered()
{
    emit requestDisplayProjectProperties();
}

void TMainWindow::on_actionAddAttackArea_triggered(bool checked)
{
    if(checked)
        emit onFrameSceneActionSelected(SA_AddAttackArea);
}

void TMainWindow::on_actionAddUndertakeArea_triggered(bool checked)
{
    if(checked)
        emit onFrameSceneActionSelected(SA_AddUndertakeArea);
}

void TMainWindow::on_actionAddTerrianArea_triggered(bool checked)
{
    if(checked)
        emit onFrameSceneActionSelected(SA_AddTerrianArea);
}

void TMainWindow::on_actionAddCollideArea_triggered(bool checked)
{
    if(checked)
        emit onFrameSceneActionSelected(SA_AddCollideArea);
}

void TMainWindow::on_actionAddFireObject_triggered(bool checked)
{
    if(checked)
        emit onFrameSceneActionSelected(SA_AddFireObject);
}

void TMainWindow::on_actionSelect_triggered(bool checked)
{
    if(checked)
        emit onFrameSceneActionSelected(SA_Default);
}

void TMainWindow::on_actionShowCollideArea_triggered(bool checked)
{
    requestShowFrameSceneArea(AT_COLLIDE, checked);
}

void TMainWindow::on_actionShowTerrianArea_triggered(bool checked)
{
    requestShowFrameSceneArea(AT_TERRIAN, checked);
}

void TMainWindow::on_actionShowAttackArea_triggered(bool checked)
{
    requestShowFrameSceneArea(AT_ATTACK, checked);
}

void TMainWindow::on_actionShowUndertakeArea_triggered(bool checked)
{
    requestShowFrameSceneArea(AT_UNDERTAKE, checked);
}

void TMainWindow::on_actionAbout_triggered()
{
    mAboutDialog->exec();
}

void TMainWindow::on_actionRun_triggered()
{
    QString enginePath = TPreferences::instance()->enginePath();
    if(QFile(enginePath).exists()) {
        emit requestRunCurrentProject();
        return;
    }

    QString tipInfo;
    if(enginePath.isEmpty())
    {
        tipInfo = tr("Engine path is not set, do you want to set it now?");
    } else {
        tipInfo = tr("Engine executable file is not exists, do you want to set it now?");
    }

    if(QMessageBox::critical(this, tr("Information"), tipInfo, QMessageBox::Yes|QMessageBox::No)==QMessageBox::No)
        return;

    TPreferencesDialog::showPreferences(this, TPreferencesDialog::DEBUG);
}

TLayerDock *TMainWindow::getLayerDock() const
{
    return mLayerDock;
}

TCharacterDock *TMainWindow::getCharacterDock() const
{
    return mCharacterDock;
}

TTilesetDock *TMainWindow::getTilesetDock() const
{
    return mTilesetDock;
}

TZoomComboBox *TMainWindow::getZoomComboBox() const
{
    return mZoomComboBox;
}

TMiniSceneDock *TMainWindow::getMiniSceneDock() const
{
    return mMiniSceneDock;
}

TLoadingDialog *TMainWindow::getLoadingDialog() const
{
    return mLoadingDialog;
}

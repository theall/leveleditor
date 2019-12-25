#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogs/aboutdialog.h"
#include "dialogs/preferencesdialog.h"
#include "dialogs/selectrootdialog.h"
#include "dialogs/loadingdialog.h"
#include "dialogs/newmapdialog.h"
#include "dialogs/exceptiondialog.h"
#include "dialogs/debugdialog.h"

#include "component/centralwidget.h"
#include "component/undodock/undodock.h"
#include "component/mapsdock/mapsdock.h"
#include "component/miniscenedock/miniscenedock.h"
#include "component/layerdock/layerdock.h"
#include "component/tabwidget/tabwidget.h"
#include "component/characterdock/characterdock.h"
#include "component/propertydock/propertiesdock.h"
#include "component/tilesetdock/tilesetdock.h"
#include "component/animationdock/animationdock.h"
#include "component/objectdock/objectdock.h"

#include "widgets/zoomcombobox.h"
#include "../utils/preferences.h"

#include <QUrl>
#include <QIcon>
#include <QMimeData>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyleFactory>

TMainWindow::TMainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mCentralWidget(new TCentralWidget(this)) //集中 中心窗口
  , mUndoDock(new TUndoDock(this))//History
  , mMapsDock(new TMapsDock(this))//maps
  , mMiniSceneDock(new TMiniSceneDock(this))//miniscene
  , mPropertyDock(new TPropertiesDock(this))//Properties 不看
  , mTilesetDock(new TTilesetDock(this))//tileset
  , mCharacterDock(new TCharacterDock(this))//Character
  , mLayerDock(new TLayerDock(this))//layerDock
  , mAnimationDock(new TAnimationDock(this))//Animation
  , mObjectDock(new TObjectDock(this))
  , mAboutDialog(new TAboutDialog(this))    //关于
  , mLoadingDialog(new TLoadingDialog(this)) //加载
  , mNewMapDialog(new TNewMapDialog(this))//新的快捷键窗口
  , mZoomComboBox(new TZoomComboBox(this))//缩放 滑轮
  , mHideMenu(false)
  , mActionGroup(new QActionGroup(this))
{
    ui->setupUi(this);
    mLoadingDialog->setWindowIcon(windowIcon());

#ifdef QT_NO_DEBUG
    ui->actionOpenDebugDialog->setVisible(false);
#endif

    // Initialize menu
    //设置快捷键
    ui->actionNewMap->setShortcuts(QKeySequence::New);
    ui->actionOpenGame->setShortcuts(QKeySequence::Open);
    ui->actionSaveMap->setShortcuts(QKeySequence::Save);
    ui->actionSaveAs->setShortcuts(QKeySequence::SaveAs);
    ui->actionCloseMap->setShortcuts(QKeySequence::Close);
    ui->actionQuit->setShortcuts(QKeySequence::Quit);
    ui->actionCut->setShortcuts(QKeySequence::Cut);
    ui->actionCopy->setShortcuts(QKeySequence::Copy);
    ui->actionPaste->setShortcuts(QKeySequence::Paste);
    ui->actionDelete->setShortcuts(QKeySequence::Delete);
    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    //设置状态为不可按(Set the status to not press)
    ui->actionSaveMap->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionSaveAllMaps->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionCloseGame->setEnabled(false);
    ui->actionCloseMap->setEnabled(false);
    ui->actionCloseAllMaps->setEnabled(false);
    ui->actionClearRecentFiles->setEnabled(false);

    // Toolbar action list
    mActionGroup->addAction(ui->actionSelectMode);
    mActionGroup->addAction(ui->actionInsertMode);
    //默认选择(Default choice)
    ui->actionSelectMode->setChecked(true);

    // Add recent file actions to the recent files menu
    //将最近的文件操作添加到最近的文件菜单
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
    //确保Ctrl+=也适用于放大
    QList<QKeySequence> keys = QKeySequence::keyBindings(QKeySequence::ZoomIn);
    keys += QKeySequence(tr("Ctrl+="));
    keys += QKeySequence(tr("+"));
    ui->actionZoomIn->setShortcuts(keys);
    keys = QKeySequence::keyBindings(QKeySequence::ZoomOut);
    keys += QKeySequence(tr("-"));
    ui->actionZoomOut->setShortcuts(keys);
    ui->menuEdit->insertSeparator(ui->actionCut);
    ui->menuEdit->insertSeparator(ui->actionSettings);
    ui->MainToolBar->addSeparator();
    // Add the 'Views and Toolbars' submenu.This needs to happen after all
    // the dock widgets and toolbars have been added to the main window
    mViewsAndToolbarsMenu = new QAction(tr("Views and Toolbars"), this);
    ui->menuView->insertAction(ui->actionShowBorder, mViewsAndToolbarsMenu);
    ui->menuView->insertSeparator(ui->actionShowBorder);

    addDockWidget(Qt::LeftDockWidgetArea, mMapsDock);
    addDockWidget(Qt::RightDockWidgetArea, mTilesetDock);
    addDockWidget(Qt::RightDockWidgetArea, mCharacterDock);
    addDockWidget(Qt::LeftDockWidgetArea, mUndoDock);
    addDockWidget(Qt::RightDockWidgetArea, mMiniSceneDock);
    addDockWidget(Qt::RightDockWidgetArea, mPropertyDock);
    addDockWidget(Qt::LeftDockWidgetArea, mLayerDock);
    addDockWidget(Qt::BottomDockWidgetArea, mAnimationDock);
    addDockWidget(Qt::RightDockWidgetArea, mObjectDock);

    tabifyDockWidget(mCharacterDock, mTilesetDock);
    tabifyDockWidget(mObjectDock, mMiniSceneDock);
    tabifyDockWidget(mMiniSceneDock, mPropertyDock);

    mViewsAndToolbarsMenu->setMenu(createPopupMenu());

    setCentralWidget(mCentralWidget);
    connect(mCentralWidget->tabWidget(), SIGNAL(currentChanged(int)), this, SLOT(slotOnTabIndexChanged(int)));
    connect(mCentralWidget->tabWidget(), SIGNAL(onTabCountChanged(int)), this, SLOT(slotOnTabCountChanged(int)));
    connect(mCentralWidget->tabWidget(), SIGNAL(onActionSaveTriggered()), this, SLOT(slotOnActionSaveTriggered()));

    // Status bar
    connect(mZoomComboBox, SIGNAL(scaleChanged(qreal)), this, SLOT(slotSceneScaleChanged(qreal)));
    ui->statusBar->addPermanentWidget(mZoomComboBox);

    setAcceptDrops(true);

    TPreferences *prefs = TPreferences::instance();
    connect(prefs, SIGNAL(toolbarIconSizeChanged(int)), this, SLOT(slotToolbarIconSizeChanged(int)));
    connect(prefs, SIGNAL(hideMenuBarChanged(bool)), this, SLOT(slotHideMenuBarChanged(bool)));
    connect(prefs, SIGNAL(hideStatusBarChanged(bool)), this, SLOT(slotHideStatusBarChanged(bool)));
    connect(prefs, SIGNAL(styleChanged(QString)), this, SLOT(slotStyleChanged(QString)));
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
    ui->actionSaveMap->setEnabled(enabled);
}

void TMainWindow::enableSaveAllAction(bool enabled)
{
    ui->actionSaveAllMaps->setEnabled(enabled);
}

void TMainWindow::enableCloseAction(bool enabled)
{
    ui->actionCloseMap->setEnabled(enabled);
}

void TMainWindow::enableCloseAllAction(bool enabled)
{
    ui->actionCloseAllMaps->setEnabled(enabled);
}

void TMainWindow::enableRunAction(bool enabled)
{
    ui->actionRun->setEnabled(enabled);
}

void TMainWindow::checkSelectAction()
{
    for(QAction *action : mActionGroup->actions()) {
        checkActionWithoutEmitSignal(action, false);
    }
    checkActionWithoutEmitSignal(ui->actionSelectMode, true);
}

void TMainWindow::checkInsertAction()
{
    for(QAction *action : mActionGroup->actions()) {
        checkActionWithoutEmitSignal(action, false);
    }
    checkActionWithoutEmitSignal(ui->actionInsertMode, true);
}

void TMainWindow::triggerCurrentSelectedAction()
{
    QAction *checkedAction = mActionGroup->checkedAction();
    if(checkedAction)
        checkedAction->trigger();
}

void TMainWindow::addRecentFile(const QString &file)
{
    TPreferences *prefs = TPreferences::instance();
    QStringList recentFiles = prefs->recentFiles();
    recentFiles.removeAll(file);
    recentFiles.prepend(file);
    prefs->setRecentFiles(recentFiles);
    updateRecentFiles();
}

void TMainWindow::setStatusMessage(const QString &message, int timeOut)
{
    statusBar()->showMessage(message, timeOut);
}

void TMainWindow::asShow()
{
#ifndef GUI_STAND_ALONE
    raiseLoadingDialog();
#endif

    loadConfig();
    show();
}

void TMainWindow::on_actionOpenGame_triggered()
{
    TPreferences *pref = TPreferences::instance();
    QString existDirectory = QFileDialog::getExistingDirectory(
                this,
                tr("Select game root"),
                pref->gameRoot());

    if(!existDirectory.isEmpty())
        pref->setLastOpenPath(existDirectory);
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
        emit requestOpenMap(url.toLocalFile());
    }
}

void TMainWindow::slotOpenRecentFile()
{
    QAction *action = dynamic_cast<QAction*>(sender());
    if(action)
    {
        emit requestOpenMap(action->data().toString());
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

void TMainWindow::on_actionNewMap_triggered()
{
    emit requestCreateNewMap();
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

void TMainWindow::checkActionWithoutEmitSignal(QAction *action, bool checked)
{
    action->blockSignals(true);//阻塞信号
    action->setChecked(checked);
    action->blockSignals(false);
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

TGraphicsView *TMainWindow::getCurrentGraphicsView() const
{
    return mCentralWidget->tabWidget()->currentGraphicsView();
}

QGraphicsScene *TMainWindow::getCurrentGraphicsScene() const
{
    return mCentralWidget->tabWidget()->currentGraphicsScene();
}

void TMainWindow::slotOnTabCountChanged(int count)
{
    ui->actionCloseMap->setEnabled(count>0);
    ui->actionCloseAllMaps->setEnabled(count>0);
}

void TMainWindow::slotOnActionSaveTriggered()
{
    ui->actionSaveMap->trigger();
}

void TMainWindow::slotOnTabIndexChanged(int)
{
    TGraphicsView *graphicsView = mCentralWidget->tabWidget()->currentGraphicsView();
    if(graphicsView) {
        mZoomComboBox->setScaleValue(graphicsView->scale(), false);
    }
}

void TMainWindow::on_actionSaveMap_triggered()
{
    emit requestSaveCurrentMap();
}

void TMainWindow::on_actionRedo_triggered()
{
    emit requestRedo();
}

void TMainWindow::on_actionUndo_triggered()
{
    emit requestUndo();
}

void TMainWindow::on_actionSaveAllMaps_triggered()
{
    emit requestSaveAllMaps();
}

void TMainWindow::on_actionExit_triggered()
{
    close();
}

void TMainWindow::loadConfig()
{
    TPreferences *prefs = TPreferences::instance();
    QByteArray geometry, state;
    prefs->windowGeometryState(&geometry, &state);
    if(!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }

    if(!state.isEmpty())
        restoreState(state);

    if(prefs->hideMenuBar())
        ui->mainMenu->setVisible(false);

    if(prefs->hideStatusBar())
    {
        statusBar()->setVisible(false);
    }
    slotToolbarIconSizeChanged(prefs->toolbarIconSize());
    mZoomComboBox->setScaleValue(prefs->sceneScale());
    updateRecentFiles();
    slotStyleChanged(prefs->style());
    ui->actionShowBorder->triggered(prefs->showTileBorder());
    ui->actionAlwaysOnTop->triggered(prefs->alwaysOnTop());
}

void TMainWindow::on_actionCloseMap_triggered()
{
    emit requestCloseCurrentMap();
}

void TMainWindow::on_actionCloseAllMaps_triggered()
{
    emit requestCloseAllMaps();
}

void TMainWindow::on_actionExport_triggered()
{

}

void TMainWindow::on_actionExportAs_triggered()
{

}

void TMainWindow::on_actionSettings_triggered()
{
    TPreferencesDialog::showPreferences(this);
}

void TMainWindow::on_actionDocumentProperties_triggered()
{
    emit requestDisplayMapProperties();
}

void TMainWindow::on_actionSelectMode_triggered()
{
    emit onActionSelectPushed();
}

void TMainWindow::on_actionInsertMode_triggered()
{
    emit onActionInsertPushed();
}

void TMainWindow::on_actionAbout_triggered()
{
    mAboutDialog->exec();
}

void TMainWindow::on_actionRun_triggered()
{
    QString enginePath = TPreferences::instance()->enginePath();
    if(QFile(enginePath).exists()) {
        emit requestRunCurrentMap();
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

void TMainWindow::on_actionShowBorder_triggered(bool arg1)
{
    emit requestShowBorder(arg1);
}

void TMainWindow::on_actionAlwaysOnTop_triggered(bool)
{
//    if(checked) {
//        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
//    } else {
//        setWindowFlags(windowFlags() ^ Qt::WindowStaysOnTopHint);
//    }
//    TPreferences::instance()->setAlwaysOnTop(checked);
//    show();
}

void TMainWindow::on_actionCloseGame_triggered()
{

}

TAnimationDock *TMainWindow::getAnimationDock() const
{
    return mAnimationDock;
}

TObjectDock *TMainWindow::getObjectDock() const
{
    return mObjectDock;
}

TNewMapDialog *TMainWindow::getNewMapDialog() const
{
    return mNewMapDialog;
}

void TMainWindow::showExceptionDialog(const QString &msg, const QString &trace)
{
    TExceptionDialog dlg(this);
    dlg.setInformation(msg, trace);
    dlg.exec();
}

void TMainWindow::on_actionOpenDebugDialog_triggered()
{
    TDebugDialog debugDialog(this);
    debugDialog.exec();
}

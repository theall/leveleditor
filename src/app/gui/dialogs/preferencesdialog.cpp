#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "../../utils/preferences.h"

#include <QFileDialog>
#include <QStyleFactory>

void blockObjectSignal(QWidget *widget, bool block)
{
    if(!widget)
        return;

    widget->blockSignals(block);
    QObjectList objectList = widget->children();
    foreach (QObject *obj, objectList) {
        QWidget *w = dynamic_cast<QWidget*>(obj);
        if(w)
            blockObjectSignal(w, block);
    }
}

TPreferencesDialog::TPreferencesDialog(QWidget* parent):
    TAbstractDialog(parent)
  , ui(new Ui::PreferencesDialog)
  , mModel(new TShortcutModel(this))
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    blockObjectSignal(this, true);

    //Add language items
    ui->cmbLanguage->blockSignals(true);
    foreach (const QString &name, TLanguageManager::instance()->languages()) {
        QLocale locale(name);
        QString string = QString(QLatin1String("%1 (%2)"))
            .arg(QLocale::languageToString(locale.language()))
            .arg(QLocale::countryToString(locale.country()));
        ui->cmbLanguage->addItem(string, name);
    }
    ui->cmbLanguage->model()->sort(0);
    ui->cmbLanguage->insertItem(0, tr("System default"));
    ui->cmbLanguage->blockSignals(false);

    //Add styles
    ui->cmbStyle->blockSignals(true);
    ui->cmbStyle->addItems(QStyleFactory::keys());
    ui->cmbStyle->blockSignals(false);

    connect(ui->tvShortcut, SIGNAL(onActionSelected(QAction*)), this, SLOT(slotActionSelected(QAction*)));
    ui->tvShortcut->setModel(mModel);

    ui->ckbMultiInstances->setVisible(false);

    retranslateUi();

    blockObjectSignal(this, false);
}

void TPreferencesDialog::showPreferences(QWidget* parent, int locatePageIndex)
{
    TPreferences* prefs = TPreferences::instance();
    TPreferencesDialog dialog(parent);

    blockObjectSignal(&dialog, true);

    // general
    dialog.ui->ckbSaveFile->setChecked(prefs->saveBeforeExit());
    dialog.ui->ckbOpenLastFiles->setChecked(prefs->openLastFile());

    // Not found (-1) ends up at index 0, system default
    int languageIndex =  dialog.ui->cmbLanguage->findData(prefs->language());
    if (languageIndex == -1)
        languageIndex = 0;
     dialog.ui->cmbLanguage->setCurrentIndex(languageIndex);

    // Style index
     dialog.ui->cmbStyle->setCurrentText(prefs->style());

    int iconSize = prefs->toolbarIconSize();
    if(iconSize==TPreferences::ICON_SIZE_SMALL)
        dialog.ui->rbSmall->setChecked(true);
    else if(iconSize==TPreferences::ICON_SIZE_MEDIUM)
        dialog.ui->rbMedium->setChecked(true);
    else if(iconSize==TPreferences::ICON_SIZE_LARGE)
        dialog.ui->rbLarge->setChecked(true);

    dialog.ui->ckbHideMenuBar->setChecked(prefs->hideMenuBar());
    dialog.ui->ckbHideStatusBar->setChecked(prefs->hideStatusBar());

    // Debug page
    dialog.ui->leEnginePath->setText(prefs->enginePath());
    dialog.ui->ckbMultiInstances->setChecked(prefs->enableDebugMultiInstances());

    blockObjectSignal(&dialog, false);

    if(locatePageIndex > 0)
        dialog.ui->tabWidget->setCurrentIndex(locatePageIndex);

    dialog.exec();
}

void TPreferencesDialog::on_ckbSaveFile_toggled(bool checked)
{
    TPreferences::instance()->setSaveBeforeExit(checked);
}

void TPreferencesDialog::on_ckbOpenLastFiles_toggled(bool checked)
{
    TPreferences::instance()->setOpenLastFile(checked);
}

void TPreferencesDialog::on_cmbLanguage_currentIndexChanged(int p0)
{
    const QString language = ui->cmbLanguage->itemData(p0).toString();
    TPreferences::instance()->setLanguage(language);
    TLanguageManager::instance()->installTranslators(language);
}

void TPreferencesDialog::on_ckbHideMenuBar_toggled(bool checked)
{
    TPreferences::instance()->setHideMenuBar(checked);
}

void TPreferencesDialog::on_ckbHideStatusBar_toggled(bool checked)
{
    TPreferences::instance()->setHideStatusBar(checked);
}

void TPreferencesDialog::on_rbSmall_toggled(bool checked)
{
    if(checked)
        TPreferences::instance()->setToolbarIconSize(TPreferences::ICON_SIZE_SMALL);
}

void TPreferencesDialog::on_rbMedium_toggled(bool checked)
{
    if(checked)
        TPreferences::instance()->setToolbarIconSize(TPreferences::ICON_SIZE_MEDIUM);
}

void TPreferencesDialog::on_rbLarge_toggled(bool checked)
{
    if(checked)
        TPreferences::instance()->setToolbarIconSize(TPreferences::ICON_SIZE_LARGE);
}

void TPreferencesDialog::slotActionSelected(QAction *action)
{
    ui->ksShortcut->setKeySequence(action->shortcut());
}

void TPreferencesDialog::retranslateUi()
{
    blockObjectSignal(this, true);
    ui->retranslateUi(this);//update ui
    ui->cmbLanguage->setItemText(0, tr("System default"));
    mModel->setFilter(QString());

    blockObjectSignal(this, false);
}

void TPreferencesDialog::on_btnClose_clicked()
{
    close();
}

void TPreferencesDialog::on_btnShortcutSet_clicked()
{
    QModelIndexList selectedIndex = ui->tvShortcut->selectionModel()->selectedIndexes();
    if(selectedIndex.size() != 2)
        return;

    if(mModel)
    {
        QModelIndex index = selectedIndex[1];
        QStandardItem *item = mModel->item(index.row(), index.column());
        QAction *action = qvariant_cast<QAction*>(item->data());
        if(action)
        {
            action->setShortcut(ui->ksShortcut->keySequence());
            item->setText(action->shortcut().toString());
            TShortKeyManager::instance()->saveAction(action);
            mModel->updateShortcut();
        }
    }
}

void TPreferencesDialog::on_leFilter_textChanged(const QString &arg1)
{
    if(mModel)
        mModel->setFilter(arg1);
}

void TPreferencesDialog::on_cmbStyle_currentTextChanged(const QString &arg1)
{
    TPreferences::instance()->setStyle(arg1);
}

void TPreferencesDialog::on_btnOpenDir_clicked()
{
    QString filter = tr("Executable file (*.%1)");
#ifdef Q_OS_WIN32
    filter = filter.arg("exe");
#elif Q_OS_MAC
    filter = filter.arg("dmg");
#else
    filter = filter.arg("elf");
#endif
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Choose engine executable file."),
                                                    ui->leEnginePath->text(),
                                                    filter);
    if (filePath.isNull())
        return;

    TPreferences::instance()->setEnginePath(filePath);
    ui->leEnginePath->setText(filePath);
}

void TPreferencesDialog::on_leEnginePath_textEdited(const QString &arg1)
{
    TPreferences::instance()->setEnginePath(arg1);
}

void TPreferencesDialog::on_ckbMultiInstances_toggled(bool checked)
{
    TPreferences::instance()->setEnableDebugMultiInstances(checked);
}

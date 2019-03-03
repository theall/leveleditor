#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include "abstractdialog.h"

#include "preferencesdialog/shortcutmodel.h"
#include "preferencesdialog/module/languagemanager.h"

namespace Ui {
class PreferencesDialog;
}

class TPreferencesDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    enum PreferencesPage
    {
        GENERAL = 0,
        SHORTCUT,
        DEBUG,
        AUTHOR,
        MISC
    };
    Ui::PreferencesDialog *ui;

public:
    TPreferencesDialog(QWidget* parent=NULL);
    static void showPreferences(QWidget* parent=NULL, int locatePageIndex = 0);

private slots:
    void slotActionSelected(QAction *action);
    void on_ckbSaveFile_toggled(bool checked);
    void on_ckbOpenLastFiles_toggled(bool checked);
    void on_cmbLanguage_currentIndexChanged(int p0);
    void on_ckbHideMenuBar_toggled(bool checked);
    void on_ckbHideStatusBar_toggled(bool checked);
    void on_rbSmall_toggled(bool checked);
    void on_rbMedium_toggled(bool checked);
    void on_rbLarge_toggled(bool checked);
    void on_btnClose_clicked();
    void on_btnShortcutSet_clicked();
    void on_leFilter_textChanged(const QString &arg1);
    void on_cmbStyle_currentTextChanged(const QString &arg1);
    void on_btnOpenDir_clicked();
    void on_leEnginePath_textEdited(const QString &arg1);
    void on_ckbMultiInstances_toggled(bool checked);

private:
    TShortcutModel *mModel;

    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // PREFERENCESDIALOG_H

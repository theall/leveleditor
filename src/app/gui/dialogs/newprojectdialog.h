#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include "abstractdialog.h"

namespace Ui {
class NewProjectDialog;
}

class TNewProjectDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    TNewProjectDialog(QWidget *parent = nullptr, QStringList recentFiles = QStringList());
    ~TNewProjectDialog();

    QString getProjectName() const;
    QString getProjectPath() const;
    QString getProjectType() const;
    QString getProjectVersion() const;
    QString getProjectAuthor() const;
    QString getProjectContact() const;
    QString getProjectComment() const;

protected:

private slots:
    void on_btnDir_clicked();
    void on_leName_textChanged(const QString &arg1);
    void on_cbbType_currentIndexChanged(const QString &arg1);
    void on_btnCancel_clicked();
    void on_btnOk_clicked();

    void on_leDir_textChanged(const QString &arg1);

private:
    bool mNameEdited;
    Ui::NewProjectDialog *ui;
    QString mErrorString;

    void retranslateUi();
    void displayError(const QString &error);
    void checkProject();
    bool isProjectFileExist();
};

#endif

#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include "abstractdialog.h"

namespace Ui {
class SelectRootDialog;
}

class TSelectRootDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    TSelectRootDialog(QWidget *parent = nullptr);
    ~TSelectRootDialog();

    static QString getSelectedRoot(QWidget *parent = nullptr);

    QString getRoot() const;

protected:

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_leRootPath_textChanged(const QString &arg1);
    void on_btnSelectDir_clicked();

private:
    bool mNameEdited;
    Ui::SelectRootDialog *ui;
    QString mErrorString;

    void retranslateUi();
    void displayError(const QString &error);
    bool checkRootPath();
};

#endif

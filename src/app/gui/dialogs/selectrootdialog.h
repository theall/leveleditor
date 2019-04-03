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

    QString getRoot() const;

protected:

private slots:
    void on_btnDir_clicked();
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_leRootPath_textChanged(const QString &arg1);

private:
    bool mNameEdited;
    Ui::SelectRootDialog *ui;
    QString mErrorString;

    void retranslateUi();
    void displayError(const QString &error);
    void checkRootPath();
};

#endif

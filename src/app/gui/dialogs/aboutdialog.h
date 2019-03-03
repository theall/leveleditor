#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "abstractdialog.h"

namespace Ui {
class AboutDialog;
}

class TAboutDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    TAboutDialog(QWidget* parent = nullptr);
    ~TAboutDialog();

protected:

private slots:
    void on_btnOk_clicked();
    void on_btnDonate_clicked();

private:
    Ui::AboutDialog *ui;
    void retranslateUi();
};

#endif // ABOUTDIALOG_H

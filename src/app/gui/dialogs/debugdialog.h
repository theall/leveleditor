#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include "abstractdialog.h"

namespace Ui {
class TDebugDialog;
}

class TDebugDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    explicit TDebugDialog(QWidget *parent = 0);
    ~TDebugDialog();

private slots:
    void on_sbIOHookFrom_valueChanged(int arg1);
    void on_sbIOHookTo_valueChanged(int arg1);

private:
    Ui::TDebugDialog *ui;

    // TAbstractDialog interface
private:
    void retranslateUi();
};

#endif // DEBUGDIALOG_H

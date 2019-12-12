#include "debugdialog.h"
#include "ui_debugdialog.h"

#include <utils/debug.h>

TDebugDialog::TDebugDialog(QWidget *parent) :
    TAbstractDialog(parent),
    ui(new Ui::TDebugDialog)
{
    ui->setupUi(this);

    ui->sbIOHookFrom->setValue(THookBuffer::hookFrom());
    ui->sbIOHookTo->setValue(THookBuffer::hookTo());
}

TDebugDialog::~TDebugDialog()
{
    delete ui;
}

void TDebugDialog::retranslateUi()
{

}

void TDebugDialog::on_sbIOHookFrom_valueChanged(int arg1)
{
    THookBuffer::setHookFrom(arg1);
    ui->sbIOHookTo->setValue(arg1+8);
}

void TDebugDialog::on_sbIOHookTo_valueChanged(int arg1)
{
    THookBuffer::setHookTo(arg1);
}

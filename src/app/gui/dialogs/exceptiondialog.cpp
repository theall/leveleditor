#include "exceptiondialog.h"
#include "ui_exceptiondialog.h"

TExceptionDialog::TExceptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TExceptionDialog)
{
    ui->setupUi(this);
}

TExceptionDialog::~TExceptionDialog()
{
    delete ui;
}

void TExceptionDialog::setInformation(const QString &msg, const QString &trace)
{
    ui->lblError->setText(msg);
    ui->txtTraceInfo->setPlainText(trace);
    ui->txtTraceInfo->setVisible(!trace.isEmpty());
}

void TExceptionDialog::on_btnOk_clicked()
{
    close();
}

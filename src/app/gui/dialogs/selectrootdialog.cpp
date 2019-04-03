#include "selectrootdialog.h"
#include "ui_selectrootdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

TSelectRootDialog::TSelectRootDialog(QWidget *parent) :
    TAbstractDialog(parent)
  , mNameEdited(false)
  , ui(new Ui::SelectRootDialog)
{
    ui->setupUi(this);

    ui->lblError->setVisible(false);
    retranslateUi();
}

TSelectRootDialog::~TSelectRootDialog()
{

}

QString TSelectRootDialog::getRoot() const
{
    return ui->leRootPath->text();
}

void TSelectRootDialog::on_btnDir_clicked()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(
                this,
            tr("Choose root directory"),
            ui->leRootPath->text(), options);
    if(!directory.isEmpty())
        ui->leRootPath->setText(directory);
}

void TSelectRootDialog::displayError(const QString &error)
{
    ui->lblError->setVisible(true);
    ui->lblError->setText(error);
    ui->btnOk->setEnabled(false);
    mErrorString = error;
}

void TSelectRootDialog::checkRootPath()
{
    QString root = ui->leRootPath->text().trimmed();
    if(root.isEmpty())
    {
        displayError(tr("Must choose multihero's root!"));
        ui->btnSelectDir->setFocus();
        return;
    }

    QDir dir(root);
    if(!dir.isReadable())
    {
        displayError(tr("Invalid directory!"));
        ui->leRootPath->setFocus();
        return;
    }
    ui->btnOk->setEnabled(true);
}

void TSelectRootDialog::on_btnCancel_clicked()
{
    reject();
}

void TSelectRootDialog::on_btnOk_clicked()
{
    checkRootPath();
    accept();
}

void TSelectRootDialog::retranslateUi()
{
    ui->retranslateUi(this);

    ui->lblError->setText(mErrorString);
}

void TSelectRootDialog::on_leRootPath_textChanged(const QString &arg1)
{
    checkRootPath();
}

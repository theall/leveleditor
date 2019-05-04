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
    ui->btnOk->setEnabled(false);
    retranslateUi();
}

TSelectRootDialog::~TSelectRootDialog()
{

}

QString TSelectRootDialog::getSelectedRoot(QWidget *parent)
{
    TSelectRootDialog dlg(parent);
    int code = dlg.exec();
    if(code == QDialog::Accepted)
        return dlg.getRoot();
    return QString();
}

QString TSelectRootDialog::getRoot() const
{
    return ui->leRootPath->text();
}

void TSelectRootDialog::displayError(const QString &error)
{
    ui->lblError->setVisible(true);
    ui->lblError->setText(error);
    ui->btnOk->setEnabled(false);
    mErrorString = error;
}

bool TSelectRootDialog::checkRootPath()
{
    QString root = ui->leRootPath->text().trimmed();
    if(root.isEmpty())
    {
        displayError(tr("Must choose multihero's root!"));
        ui->btnSelectDir->setFocus();
        return false;
    }

    QDir dir(root);
    if(!dir.isReadable())
    {
        displayError(tr("Invalid directory!"));
        ui->leRootPath->setFocus();
        return false;
    }
    ui->btnOk->setEnabled(true);
    return true;
}

void TSelectRootDialog::on_btnCancel_clicked()
{
    reject();
}

void TSelectRootDialog::on_btnOk_clicked()
{
    if(checkRootPath())
        accept();
}

void TSelectRootDialog::retranslateUi()
{
    ui->retranslateUi(this);

    ui->lblError->setText(mErrorString);
}

void TSelectRootDialog::on_leRootPath_textChanged(const QString &)
{
    checkRootPath();
}

void TSelectRootDialog::on_btnSelectDir_clicked()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(
                this,
            tr("Choose root directory"),
            ui->leRootPath->text(), options);
    if(!directory.isEmpty())
        ui->leRootPath->setText(directory);
}

#include "loadingdialog.h"
#include "ui_loadingdialog.h"

#include <QCloseEvent>

TLoadingDialog::TLoadingDialog(QWidget *parent) :
    QDialog(parent)
  , mIsEnd(false)
  , ui(new Ui::TLoadingDialog)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0xffff);
    ui->progressBar->setValue(0);

    setWindowTitle(tr("Loading..."));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowModality(Qt::WindowModal);
}

TLoadingDialog::~TLoadingDialog()
{
    delete ui;
}

void TLoadingDialog::setProgress(int progress, int total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(progress);
    if(progress >= total) {
        mIsEnd = true;
        accept();
    }
}

bool TLoadingDialog::isEnd() const
{
    return mIsEnd;
}

void TLoadingDialog::closeEvent(QCloseEvent *)
{
    reject();
}

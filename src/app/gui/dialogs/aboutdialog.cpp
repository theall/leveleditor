#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDate>
#include <QDesktopServices>

TAboutDialog::TAboutDialog(QWidget* parent) :
    TAbstractDialog(parent)
  , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    retranslateUi();
}


TAboutDialog::~TAboutDialog()
{
    delete ui;
}

void TAboutDialog::on_btnOk_clicked()
{
    close();
}

void TAboutDialog::on_btnDonate_clicked()
{
    QDesktopServices::openUrl(QUrl("http://github.com/theall/leveleditor/", QUrl::TolerantMode));
}

void TAboutDialog::retranslateUi()
{
//    QString html = tr(
//            "<p align=\"center\"><h1>Team</h1><br>"
//            "Theall<br>ZhangJunxue<br>HuXin<br>YanHongzhou<br><br>"
//            "<h1>Credits</h1><br></p>"
//            );
//    ui->textBrowser->setHtml(html);
}

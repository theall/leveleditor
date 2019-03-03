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
    setMaximumSize(432, 460);

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
    QDesktopServices::openUrl(QUrl("https://www.2dcombat.org/", QUrl::TolerantMode));
}

void TAboutDialog::retranslateUi()
{
    QString html = tr(
            "<p align=\"center\"><font size=\"+2\"><b>2D Combat Character Editor</b></font><br><i>Version %1</i></p><br>"
            "<p align=\"center\">Copyright 2015-%2 Bilge Theall</p><br>"
            "<p align=\"center\"><a href=\"http://www.2dcombat.org/\">http://www.2dcombat.org/</a></p>")
            .arg(QApplication::applicationVersion()).arg(QDate::currentDate().year());
    ui->textBrowser->setHtml(html);
}

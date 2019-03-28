#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

TNewProjectDialog::TNewProjectDialog(QWidget *parent, QStringList recentFiles) :
    TAbstractDialog(parent)
  , mNameEdited(false)
  , ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);

    ui->lblError->setVisible(false);
    if(recentFiles.size() > 0)
    {
        QString filePath = recentFiles.at(0);
        ui->leDir->setText(QFileInfo(filePath).absolutePath());
    } else {
        ui->leDir->setText(QDir::currentPath());
    }

    QDir dir(ui->leDir->text());
    QString nameBase = "New Scene";
    QString nameWithExt = nameBase + ".dat";
    if(QFile::exists(dir.absoluteFilePath(nameWithExt)))
    {
        for(int i=1;i<100;i++)
        {
            QString name = nameBase + QString::number(i);
            nameWithExt = name + ".dat";
            if(!QFile::exists(dir.absoluteFilePath(nameWithExt)))
            {
                nameBase = name;
                break;
            }
        }
    }
    ui->leName->setText(nameBase);

    ui->leVersion->setText("1.0.0.0");
    ui->leAuthor->setText("anonymous");


    ui->leName->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9\\. _-]+")));
    ui->leVersion->setValidator(new QRegExpValidator(QRegExp("\\d+\\.\\d+\\.\\d+\\.\\d+")));

    retranslateUi();
}

TNewProjectDialog::~TNewProjectDialog()
{

}

QString TNewProjectDialog::getProjectName() const
{
    return ui->leName->text();
}

QString TNewProjectDialog::getProjectPath() const
{
    return ui->leDir->text();
}

QString TNewProjectDialog::getProjectType() const
{
    return ui->cbbType->currentText();
}

QString TNewProjectDialog::getProjectVersion() const
{
    return ui->leVersion->text();
}

QString TNewProjectDialog::getProjectAuthor() const
{
    return ui->leAuthor->text();
}

QString TNewProjectDialog::getProjectContact() const
{
    return ui->leContact->text();
}

QString TNewProjectDialog::getProjectComment() const
{
    return ui->edtDescription->toPlainText();
}

void TNewProjectDialog::on_btnDir_clicked()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(
                this,
            tr("Choose project directory"),
            ui->leDir->text(), options);
    if(!directory.isEmpty())
        ui->leDir->setText(directory);
}

void TNewProjectDialog::displayError(const QString &error)
{
    ui->lblError->setVisible(true);
    ui->lblError->setText(error);
    mErrorString = error;
}

void TNewProjectDialog::checkProject()
{
    if(isProjectFileExist())
    {
        displayError(tr("Project is exists!"));
        ui->btnOk->setEnabled(false);
    } else {
        ui->btnOk->setEnabled(true);
        ui->lblError->setVisible(false);
    }
}

bool TNewProjectDialog::isProjectFileExist()
{
    QDir dir(ui->leDir->text());
    QString projectFile = dir.absoluteFilePath(ui->leName->text() + ".dat");
    return QFile::exists(projectFile);
}

void TNewProjectDialog::on_leName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    mNameEdited = true;
    checkProject();
}

void TNewProjectDialog::on_cbbType_currentIndexChanged(const QString &arg1)
{
    if(!mNameEdited)
    {
        ui->leName->setText("New " + arg1);
        mNameEdited = false;
    }
}

void TNewProjectDialog::on_btnCancel_clicked()
{
    reject();
}

void TNewProjectDialog::on_btnOk_clicked()
{
    if(ui->leName->text().trimmed().isEmpty())
    {
        displayError(tr("Sprite name can not be empty!"));
        ui->leName->setFocus();
        return;
    }
    if(!QFileInfo(ui->leDir->text()).isDir())
    {
        displayError(tr("Invalid directory!"));
        ui->leDir->setFocus();
        return;
    }
    QString fileName = ui->leDir->text() + "/" + ui->leName->text() + ".chr";
    if(QFile::exists(fileName))
    {
        if(QMessageBox::question(
            this, tr("Question."),
            tr("File already exists, do you want to overwrite it?"),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            return;
    }
    accept();
}

void TNewProjectDialog::retranslateUi()
{
    ui->retranslateUi(this);

    ui->lblError->setText(mErrorString);
}

void TNewProjectDialog::on_leDir_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    checkProject();
}

#include "newmapdialog.h"
#include "ui_newmapdialog.h"

TNewMapDialog::TNewMapDialog(QWidget *parent) :
    TAbstractDialog(parent),
    ui(new Ui::TNewMapDialog)
{
    ui->setupUi(this);

    ui->cmbMapType->setEditable(false);
    ui->cmbMapType->setCurrentIndex(0);
    ui->cmbModule->setEditable(false);
    ui->cmbModule->setMaxVisibleItems(99);
    ui->sbId->setReadOnly(true);
    ui->leFileName->setReadOnly(true);

    updateMapFileName();
}

TNewMapDialog::~TNewMapDialog()
{
    delete ui;
}

QString TNewMapDialog::getModuleName() const
{
    return ui->cmbModule->currentText();
}

QString TNewMapDialog::getMapTypeName() const
{
    return ui->cmbMapType->currentText();
}

int TNewMapDialog::getMapId() const
{
    return ui->sbId->value();
}

QString TNewMapDialog::getMapName() const
{
    return ui->leFileName->text();
}

void TNewMapDialog::setModuleNameIds(
        const QStringList &moduleNames,
        const QList<int> &advIdList,
        const QList<int> &vsIdList,
        const QList<int> &ctfIdList)
{
    Q_ASSERT(moduleNames.size()==advIdList.size());
    Q_ASSERT(moduleNames.size()==vsIdList.size());
    Q_ASSERT(moduleNames.size()==ctfIdList.size());

    mAdvIdList = advIdList;
    mVsIdList = vsIdList;
    mCtfIdList = ctfIdList;

    ui->cmbModule->clear();
    ui->cmbModule->addItems(moduleNames);

    ui->cmbModule->setCurrentIndex(0);
}

void TNewMapDialog::retranslateUi()
{
    ui->retranslateUi(this);
}

void TNewMapDialog::on_cmbMapType_currentTextChanged(const QString &)
{
    updateMapId();
}

void TNewMapDialog::updateMapFileName()
{
    QString tpl("%1map%2.dat");
    QString mapTypeName = ui->cmbMapType->currentText().toLower();
    QString prefix = "";
    if(mapTypeName == "adv")
        prefix = "a";
    else if(mapTypeName == "ctf")
        prefix = "CTF";
    ui->leFileName->setText(tpl.arg(prefix).arg(ui->sbId->value()));
}

void TNewMapDialog::on_cmbModule_currentIndexChanged(int index)
{
    updateMapId();
}

void TNewMapDialog::updateMapId()
{
    int moduleIndex = ui->cmbModule->currentIndex();
    QString mapTypeName = ui->cmbMapType->currentText().toLower();
    int id = 9999;
    if(mapTypeName == "adv")
        id = mAdvIdList.at(moduleIndex);
    else if(mapTypeName == "ctf")
        id = mCtfIdList.at(moduleIndex);
    else if(mapTypeName == "vs")
        id = mVsIdList.at(moduleIndex);
    ui->sbId->setValue(id);
}

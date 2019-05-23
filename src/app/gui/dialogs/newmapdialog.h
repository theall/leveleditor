#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include "abstractdialog.h"

namespace Ui {
class TNewMapDialog;
}
class TAbstractDialog;
class TNewMapDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    explicit TNewMapDialog(QWidget *parent = 0);
    ~TNewMapDialog();

    QString getModuleName() const;
    QString getMapTypeName() const;
    int getMapId() const;
    QString getMapName() const;

    void setModuleNameIds(
            const QStringList &moduleNames,
            const QList<int> &advIdList,
            const QList<int> &vsIdList,
            const QList<int> &ctfIdList);

private slots:
    void on_cmbMapType_currentTextChanged(const QString &arg1);
    void on_cmbModule_currentIndexChanged(int index);

private:
    Ui::TNewMapDialog *ui;
    QList<int> mAdvIdList;
    QList<int> mVsIdList;
    QList<int> mCtfIdList;

    void updateMapId();
    void updateMapFileName();

    // TAbstractDialog interface
private:
    void retranslateUi();
};

#endif // NEWMAPDIALOG_H

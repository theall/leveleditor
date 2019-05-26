#ifndef EXCEPTIONDIALOG_H
#define EXCEPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TExceptionDialog;
}

class TExceptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TExceptionDialog(QWidget *parent = 0);
    ~TExceptionDialog();

    void setInformation(const QString &msg, const QString &trace);

private slots:
    void on_btnOk_clicked();

private:
    Ui::TExceptionDialog *ui;
};

#endif // EXCEPTIONDIALOG_H

#ifndef TABSTRACTDIALOG_H
#define TABSTRACTDIALOG_H

#include <QEvent>
#include <QDialog>

class TAbstractDialog : public QDialog
{
public:
    TAbstractDialog(QWidget *parent = 0, bool resizable = false);
    ~TAbstractDialog();

private:
    virtual void retranslateUi() = 0;

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // TABSTRACTDIALOG_H

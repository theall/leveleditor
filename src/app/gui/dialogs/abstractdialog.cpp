#include "abstractdialog.h"

TAbstractDialog::TAbstractDialog(QWidget *parent, bool resizable) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    flags ^= Qt::WindowContextHelpButtonHint;
    if(!resizable)
        flags |= Qt::MSWindowsFixedSizeDialogHint;
    else
        flags |= Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;

    setWindowFlags(flags);
}

TAbstractDialog::~TAbstractDialog()
{

}

void TAbstractDialog::changeEvent(QEvent *event)
{
    if (event->type()==QEvent::LanguageChange)
    {
        retranslateUi();//update ui
    }
    QDialog::changeEvent(event);
}

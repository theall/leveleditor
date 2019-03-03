#include "plaintexteditor.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QDialogButtonBox>

TPlainTextEditor::TPlainTextEditor(QWidget *parent)  :
    QDialog(parent)
  , mEditor(new QPlainTextEdit)
{
    setWindowTitle(tr("Edit property"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(3);
    vlayout->setMargin(1);
    vlayout->addWidget(mEditor);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);
    QPushButton *btnOk = buttonBox->button(QDialogButtonBox::Ok);
    btnOk->setDefault(true);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    vlayout->addWidget(buttonBox);
}

TPlainTextEditor::~TPlainTextEditor()
{

}

int TPlainTextEditor::showDialog()
{
    mEditor->setFocus();
    return exec();
}

void TPlainTextEditor::setDefaultFont(const QFont &font)
{
    mEditor->setFont(font);
}

void TPlainTextEditor::setText(const QString &text)
{
    mEditor->setPlainText(text);
}

QString TPlainTextEditor::text() const
{
    return mEditor->toPlainText();
}

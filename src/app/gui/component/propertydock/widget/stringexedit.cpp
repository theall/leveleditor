#include "stringexedit.h"
#include "plaintexteditor.h"

#include <QHBoxLayout>
#include <QToolButton>

TStringExEdit::TStringExEdit(QWidget *parent) :
    QWidget(parent)
  , mLineEdit(new QLineEdit(this))
{
    mLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    QToolButton *button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setFixedWidth(20);
    button->setText(QLatin1String("..."));
    layout->addWidget(mLineEdit);
    layout->addWidget(button);

    setFocusProxy(mLineEdit);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);

    connect(mLineEdit, SIGNAL(textChanged(QString)),
            this, SIGNAL(textChanged(QString)));

    connect(button, SIGNAL(clicked()),
            this, SLOT(slotButtonClicked()));
}

TStringExEdit::~TStringExEdit()
{

}

void TStringExEdit::focusInEvent(QFocusEvent *e)
{
    mLineEdit->event(e);
    if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason) {
        mLineEdit->selectAll();
    }
    QWidget::focusInEvent(e);
}

void TStringExEdit::focusOutEvent(QFocusEvent *e)
{
    mLineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void TStringExEdit::keyPressEvent(QKeyEvent *e)
{
    mLineEdit->event(e);
}

void TStringExEdit::keyReleaseEvent(QKeyEvent *e)
{
    mLineEdit->event(e);
}

void TStringExEdit::slotButtonClicked()
{
    TPlainTextEditor plainTextEditor(this);
    plainTextEditor.setText(mLineEdit->text());
    if(plainTextEditor.showDialog() == QDialog::Accepted)
    {
        QString text = plainTextEditor.text();
        mLineEdit->setText(text);
        emit textChanged(text);
    }
}

QString TStringExEdit::text() const
{
    return mLineEdit->text();
}

void TStringExEdit::setText(const QString &text)
{
    mLineEdit->setText(text);
}

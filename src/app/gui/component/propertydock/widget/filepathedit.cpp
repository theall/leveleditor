#include "filepathedit.h"

#include <QFileDialog>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

TFilePathEdit::TFilePathEdit(QWidget *parent)
    : QWidget(parent)
    , mErrorTextColor(Qt::red)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mLineEdit = new QLineEdit(this);
    mLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    mOkTextColor = mLineEdit->palette().color(QPalette::Active, QPalette::Text);

    QToolButton *button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setFixedWidth(20);
    button->setText(QLatin1String("..."));
    layout->addWidget(mLineEdit);
    layout->addWidget(button);

    setFocusProxy(mLineEdit);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);

    connect(mLineEdit, SIGNAL(textEdited(QString)),
            this, SIGNAL(filePathChanged(QString)));
    connect(mLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(slotValidate(QString)));
    connect(button, SIGNAL(clicked()),
            this, SLOT(slotButtonClicked()));
}

TFilePathEdit::~TFilePathEdit()
{

}

void TFilePathEdit::setFilePath(const QString &filePath)
{
     if (mLineEdit->text() != filePath)
         mLineEdit->setText(filePath);
}

QString TFilePathEdit::filePath() const
{
    return mLineEdit->text();
}

void TFilePathEdit::focusInEvent(QFocusEvent *e)
{
    mLineEdit->event(e);
    if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason) {
        mLineEdit->selectAll();
    }
    QWidget::focusInEvent(e);
}

void TFilePathEdit::focusOutEvent(QFocusEvent *e)
{
    mLineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void TFilePathEdit::keyPressEvent(QKeyEvent *e)
{
    mLineEdit->event(e);
}

void TFilePathEdit::keyReleaseEvent(QKeyEvent *e)
{
    mLineEdit->event(e);
}

void TFilePathEdit::slotValidate(const QString &text)
{
    QColor textColor = QFile::exists(text) ? mOkTextColor : mErrorTextColor;

    QPalette palette = mLineEdit->palette();
    palette.setColor(QPalette::Active, QPalette::Text, textColor);
    mLineEdit->setPalette(palette);
}

void TFilePathEdit::slotButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(window(),
                                                    tr("Choose a File"),
                                                    mLineEdit->text(),
                                                    mFilter);
    if (filePath.isNull())
        return;
    mLineEdit->setText(filePath);
    emit filePathChanged(filePath);
}

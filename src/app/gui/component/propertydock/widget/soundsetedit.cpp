#include "soundsetedit.h"

#include <QEvent>
#include <QHBoxLayout>

TSoundSetEdit::TSoundSetEdit(QWidget *parent) :
    QWidget(parent)
  , mText(new QLabel(this))
  , mAddButton(new QToolButton(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mText->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
    mAddButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    mAddButton->setFixedWidth(20);
    mAddButton->setIcon(QIcon(":/actionsdock/images/add.png"));
    layout->addWidget(mText);
    layout->addWidget(mAddButton);

    connect(mAddButton, SIGNAL(clicked()), this, SLOT(slotAddButtonClicked()));
    retranslateUi();
}

TSoundSetEdit::~TSoundSetEdit()
{

}

QString TSoundSetEdit::text() const
{
    return mText->text();
}

void TSoundSetEdit::setText(const QString &text)
{
    mText->setText(text);
}

void TSoundSetEdit::slotAddButtonClicked()
{
    emit requestAddSoundItem();
}

void TSoundSetEdit::retranslateUi()
{
    mAddButton->setToolTip(tr("Add sound item."));
}

bool TSoundSetEdit::event(QEvent *event)
{
    if(event->type()==QEvent::LanguageChange)
    {
        retranslateUi();
    }
    return QWidget::event(event);
}

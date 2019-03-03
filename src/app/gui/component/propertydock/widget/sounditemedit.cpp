#include "sounditemedit.h"

#include <QEvent>
#include <QHBoxLayout>

TSoundItemEdit::TSoundItemEdit(QWidget *parent) :
    QWidget(parent)
  , mText(new QLabel(this))
  , mRemoveButton(new QToolButton(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mText->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
    mRemoveButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    mRemoveButton->setFixedWidth(20);
    mRemoveButton->setIcon(QIcon(":/actionsdock/images/remove.png"));
    layout->addWidget(mText);
    layout->addWidget(mRemoveButton);

    connect(mRemoveButton, SIGNAL(clicked()), this, SLOT(slotRemoveButtonClicked()));
    retranslateUi();
}

TSoundItemEdit::~TSoundItemEdit()
{

}

QString TSoundItemEdit::text() const
{
    return mText->text();
}

void TSoundItemEdit::setText(const QString &text)
{
    mText->setText(text);
}

void TSoundItemEdit::slotRemoveButtonClicked()
{
    emit requestRemoveProperty(mContext);
}

void *TSoundItemEdit::context() const
{
    return mContext;
}

void TSoundItemEdit::setContext(void *context)
{
    mContext = context;
}

void TSoundItemEdit::retranslateUi()
{
    mRemoveButton->setToolTip(tr("Remove this sound item."));
}

bool TSoundItemEdit::event(QEvent *event)
{
    if(event->type()==QEvent::LanguageChange)
    {
        retranslateUi();
    }
    return QWidget::event(event);
}

#include "sounditemsourceedit.h"

#include <QEvent>
#include <QHBoxLayout>

TSoundItemSourceEdit::TSoundItemSourceEdit(QWidget *parent) :
    QWidget(parent)
  , mText(new QLabel(this))
  , mPlayIcon(QIcon(":/actionsdock/images/play.png"))
  , mStopIcon(QIcon(":/actionsdock/images/stop_play.png"))
  , mPlayButton(new QToolButton(this))
  , mMediaContent(nullptr)
  , mMediaPlayer(new QMediaPlayer(this))
  , mChangeSourceButton(new QToolButton(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mText->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));
    mPlayButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    mPlayButton->setFixedWidth(20);
    mPlayButton->setIcon(mPlayIcon);
    mChangeSourceButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    mChangeSourceButton->setFixedWidth(20);
    mChangeSourceButton->setText("...");
    layout->addWidget(mText);
    layout->addWidget(mPlayButton);
    layout->addWidget(mChangeSourceButton);
    connect(mPlayButton, SIGNAL(clicked()), this, SLOT(slotPlayButtonClicked()));
    connect(mChangeSourceButton, SIGNAL(clicked()), this, SLOT(slotChangeSourceButtonClicked()));
    connect(mMediaPlayer,
                SIGNAL(stateChanged(QMediaPlayer::State)),
                this,
                SLOT(slotMediaStateChanged(QMediaPlayer::State)));

    setMediaContent(nullptr);
    retranslateUi();
}

TSoundItemSourceEdit::~TSoundItemSourceEdit()
{

}

QString TSoundItemSourceEdit::text() const
{
    return mText->text();
}

void TSoundItemSourceEdit::setText(const QString &text)
{
    mText->setText(text);
}

void TSoundItemSourceEdit::slotChangeSourceButtonClicked()
{
    QString soundFile;
    QMediaContent *mediaContent = nullptr;
    emit getSelectedSound(soundFile, mediaContent);
    if(mediaContent)
    {
        QMediaContent *oldMediaContent = mMediaContent;
        setMediaContent(mediaContent);
        mText->setText(soundFile);

        if(mediaContent != oldMediaContent)
            emit soundSourceChanged(soundFile, mediaContent);
    }
}

void TSoundItemSourceEdit::slotPlayButtonClicked()
{
    if(!mMediaContent)
        return;

    if(mMediaPlayer->state()==QMediaPlayer::PlayingState)
    {
        // There is something playing, stop it
        mMediaPlayer->stop();
    } else {
        mMediaPlayer->setMedia(*mMediaContent);
        mMediaPlayer->play();
    }
}

void TSoundItemSourceEdit::slotMediaStateChanged(QMediaPlayer::State state)
{
    if(!mMediaContent)
        return;

    if(state==QMediaPlayer::PlayingState)
    {
        mPlayButton->setIcon(mStopIcon);
    } else if(state==QMediaPlayer::StoppedState) {
        mPlayButton->setIcon(mPlayIcon);
    }
}

QMediaContent *TSoundItemSourceEdit::mediaContent() const
{
    return mMediaContent;
}

void TSoundItemSourceEdit::setMediaContent(QMediaContent *mediaContent)
{
    mMediaContent = mediaContent;
    if(mMediaPlayer->state()==QMediaPlayer::PlayingState)
        mMediaPlayer->stop();
    mPlayButton->setEnabled(mMediaContent!=nullptr);
}

void TSoundItemSourceEdit::retranslateUi()
{
    mChangeSourceButton->setToolTip(tr("Click to change sound source."));
}

bool TSoundItemSourceEdit::event(QEvent *event)
{
    if(event->type()==QEvent::LanguageChange)
    {
        retranslateUi();
    }
    return QWidget::event(event);
}

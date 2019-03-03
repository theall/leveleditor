#ifndef SOUNDITEMSOURCEEDIT_H
#define SOUNDITEMSOURCEEDIT_H

#include <QLabel>
#include <QToolButton>
#include <QMediaPlayer>
#include <QMediaContent>

class TSoundItemSourceEdit : public QWidget
{
    Q_OBJECT

public:
    TSoundItemSourceEdit(QWidget *parent = nullptr);
    ~TSoundItemSourceEdit();

    QString text() const;
    void setText(const QString &text);

    QMediaContent *mediaContent() const;
    void setMediaContent(QMediaContent *mediaContent);

signals:
    void getSelectedSound(QString &soundFile, QMediaContent *&mediaContent);
    void soundSourceChanged(const QString &newFile, const QMediaContent *newMediaContent);

private slots:
    void slotChangeSourceButtonClicked();
    void slotPlayButtonClicked();
    void slotMediaStateChanged(QMediaPlayer::State state);

private:
    QLabel *mText;
    QIcon mPlayIcon;
    QIcon mStopIcon;
    QToolButton *mPlayButton;
    QMediaContent *mMediaContent;
    QMediaPlayer *mMediaPlayer;
    QToolButton *mChangeSourceButton;
    QToolButton *mClearButton;

    void retranslateUi();

    // QObject interface
public:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // SOUNDITEMSOURCEEDIT_H

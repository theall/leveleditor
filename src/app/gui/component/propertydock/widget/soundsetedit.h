#ifndef SOUNDSETEDIT_H
#define SOUNDSETEDIT_H

#include <QLabel>
#include <QToolButton>

class TSoundSetEdit : public QWidget
{
    Q_OBJECT

public:
    TSoundSetEdit(QWidget *parent = nullptr);
    ~TSoundSetEdit();

    QString text() const;
    void setText(const QString &text);

signals:
    void requestAddSoundItem();

private slots:
    void slotAddButtonClicked();

private:
    QLabel *mText;
    QToolButton *mAddButton;

    void retranslateUi();

    // QObject interface
public:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // SOUNDSETEDIT_H

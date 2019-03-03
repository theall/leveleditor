#ifndef SOUNDITEMEDIT_H
#define SOUNDITEMEDIT_H

#include <QLabel>
#include <QToolButton>

class TSoundItemEdit : public QWidget
{
    Q_OBJECT

public:
    TSoundItemEdit(QWidget *parent = nullptr);
    ~TSoundItemEdit();

    QString text() const;
    void setText(const QString &text);

    void *context() const;
    void setContext(void *context);

signals:
    void requestRemoveProperty(void *context);

private slots:
    void slotRemoveButtonClicked();

private:
    QLabel *mText;
    void *mContext;
    QToolButton *mRemoveButton;

    void retranslateUi();

    // QObject interface
public:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // SOUNDITEMEDIT_H

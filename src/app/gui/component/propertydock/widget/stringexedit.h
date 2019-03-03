#ifndef STRINGEXEDIT_H
#define STRINGEXEDIT_H

#include <QLineEdit>

/**
 * A widget that combines a line edit with a button to edit in plain text editor.
 */
class TStringExEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TStringExEdit(QWidget *parent = nullptr);
    ~TStringExEdit();

    QString text() const;
    void setText(const QString &text);

signals:
    void textChanged(const QString &text);

protected:
    void focusInEvent(QFocusEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private slots:
    void slotButtonClicked();

private:
    QLineEdit *mLineEdit;
};

#endif // STRINGEXEDIT_H

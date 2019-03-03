#ifndef PLAINTEXTEDITOR_H
#define PLAINTEXTEDITOR_H

#include <QDialog>
#include <QPlainTextEdit>

class TPlainTextEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TPlainTextEditor(QWidget *parent = 0);
    ~TPlainTextEditor();

    int showDialog();

    void setDefaultFont(const QFont &font);

    void setText(const QString &text);
    QString text() const;

private:
    QPlainTextEdit *mEditor;
};

#endif // PLAINTEXTEDITOR_H

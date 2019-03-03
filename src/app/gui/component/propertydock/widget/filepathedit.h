#ifndef FILEPATHEDIT_H
#define FILEPATHEDIT_H

#include <QValidator>
#include <QLineEdit>

/**
 * A widget that combines a line edit with a button to choose a file.
 */
class TFilePathEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TFilePathEdit(QWidget *parent = nullptr);
    ~TFilePathEdit();

    void setFilePath(const QString &filePath);
    QString filePath() const;

    void setFilter(const QString &filter) { mFilter = filter; }
    QString filter() const { return mFilter; }

signals:
    void filePathChanged(const QString &filePath);

protected:
    void focusInEvent(QFocusEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private slots:
    void slotValidate(const QString &);
    void slotButtonClicked();

private:
    QLineEdit *mLineEdit;
    QString mFilter;
    QColor mOkTextColor;
    QColor mErrorTextColor;
};

#endif // FILEPATHEDIT_H

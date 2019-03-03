#ifndef PIXMAPEDIT_H
#define PIXMAPEDIT_H

#include <QLabel>

class TPixmapEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TPixmapEdit(QWidget *parent = nullptr);
    ~TPixmapEdit();

    QString text() const;
    void setText(const QString &text);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap);

signals:
    void getSelectedPixmap(QString &text, QPixmap &pixmap);
    void pixmapChanged(const QString &name, const QPixmap &pixmap);

protected:

private slots:
    void slotButtonClicked();

private:
    QLabel *mPixmap;
    QLabel *mText;
};

#endif // PIXMAPEDIT_H

#ifndef TCHARACTERVIEW_H
#define TCHARACTERVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>

class TCharacterView : public QListWidget
{
    Q_OBJECT

public:
    explicit TCharacterView(QWidget *parent = 0);
    ~TCharacterView();

    int add(const QPixmap &face);
    void setPixmapSet(const QList<QPixmap> &pixmapSet);

signals:
    void characterToggled(int index, bool toggled);

private:
    int mIconSize;
    QPushButton *mLastPushedButton;
    QList<QPushButton*> mButtonList;

    void clear();

private slots:
    void slotOnFaceButtonToggled(bool);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
};

#endif // TCHARACTERVIEW_H

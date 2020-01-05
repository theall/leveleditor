#ifndef TCHARACTERVIEW_H
#define TCHARACTERVIEW_H

#include <QWidget>
#include <QMenu>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <QAction>
#include <QTableView>

class TCharacterView : public QListWidget
{
    Q_OBJECT

public:
    explicit TCharacterView(QWidget *parent = 0);
    ~TCharacterView();

    int add(const QPixmap &face, int id);
    void setPixmapSet(const QList<QPixmap> &pixmapSet, const QList<int> &idList);
    void pushButton(int index);
    int getCurrentPushButtonIndex() const;

signals:
    void buttonPushed(int index);
    void setCharaterEnabled(QPushButton *button);
private:
    int mIconSize;
    QPushButton *mLastPushedButton;
    QList<QPushButton*> mButtonList;
    QMap<QPushButton*, int> mButtonValueMap;
    QList<void*> mChiaractersets;
    QMenu *mContextMenu;
    TCharacterView *mCharacterButton;
    //void setCharacterEnabled(bool enabled);
    void retranslateUi();
    void clear();

private slots:
    void slotOnFaceButtonToggled(bool);
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
};

#endif // TCHARACTERVIEW_H

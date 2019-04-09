#ifndef TCHARACTERVIEW_H
#define TCHARACTERVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QSpacerItem>
class TCharacterView : public QWidget
{
    Q_OBJECT

public:
    explicit TCharacterView(QWidget *parent = 0);
    ~TCharacterView();

    int add(const QPixmap &face);

signals:
    void characterToggled(int index, bool toggled);

private:
    int mCols;
    int mIconSize;
    QPushButton *mLastPushedButton;
    QSpacerItem *mBottomSpacer;
    QSpacerItem *mLeftSpacer;
    QSpacerItem *mRightSpacer;
    QList<QPushButton*> mButtonList;
    void calcRowsAndCols();
    void reArrange();

private slots:
    void slotOnFaceButtonToggled(bool);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
};

#endif // TCHARACTERVIEW_H

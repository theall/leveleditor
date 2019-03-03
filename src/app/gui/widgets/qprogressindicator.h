#ifndef QPROGRESSINDICATOR_H
#define QPROGRESSINDICATOR_H

#include <QWidget>

class QProgressIndicator : public QWidget
{
    Q_OBJECT

public:
    QProgressIndicator(QWidget* parent=NULL);
    ~QProgressIndicator();

    static QProgressIndicator* getWaitIcon(QWidget* parent=NULL, int delayTime=1500);

    void updatePos();
    bool isAnimated();
    int animationDelay();
    void setColor(QColor color);
    QColor getColor();
    void setDisplayWhenStop(bool display);
    bool isDisplayWhenStop();
    void start(int delayTime=1500);
    void startAnimation(int delayTime=1500);

    void stop();
    void setTerminate();
    void stopAnimation();
    void setAnimationDelay(int delayTime);

private slots:
    void delayStart();

protected:
    void timerEvent(QTimerEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QWidget* mParent;
    int mAngle;
    int mTimerId;
    int mDelayTime;
    QColor mColor;
    bool mDisplay;
    int mSecElispse;
    int mDelayShowSec;
    bool bTerminate;
};

#endif // QPROGRESSINDICATOR_H

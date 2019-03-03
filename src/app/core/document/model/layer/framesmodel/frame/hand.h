#ifndef DOCUMENT_HAND_H
#define DOCUMENT_HAND_H

#include <gameutils.h>

#include <QObject>
#include <QRect>

class THand : public QObject
{
    Q_OBJECT

public:
    THand(QObject *parent=nullptr);
    ~THand();

    void loadFromModel(const Model::THand &hand, void *context=nullptr);

signals:
    void rectChanged(const QRect &rect);

private:
    HandDirection mPalmDirection;
    float mFlatAngle;
    QRect mRect;
};

#endif // DOCUMENT_HAND_H

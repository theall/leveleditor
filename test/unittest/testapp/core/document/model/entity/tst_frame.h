#ifndef TESTFRAME_H
#define TESTFRAME_H

#include <QObject>

class TestFrame : public QObject
{
    Q_OBJECT

public:
    explicit TestFrame(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTFRAME_H
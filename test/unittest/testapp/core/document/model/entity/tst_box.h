#ifndef TESTBOX_H
#define TESTBOX_H

#include <QObject>

class TestBox : public QObject
{
    Q_OBJECT

public:
    explicit TestBox(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTBOX_H
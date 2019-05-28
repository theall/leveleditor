#ifndef TESTOBJECTITEM_H
#define TESTOBJECTITEM_H

#include <QObject>

class TestObjectItem : public QObject
{
    Q_OBJECT

public:
    explicit TestObjectItem(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTOBJECTITEM_H
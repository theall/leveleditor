#ifndef TESTENEMY_H
#define TESTENEMY_H

#include <QObject>

class TestEnemy : public QObject
{
    Q_OBJECT

public:
    explicit TestEnemy(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTENEMY_H
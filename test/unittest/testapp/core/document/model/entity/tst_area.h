#ifndef TESTAREA_H
#define TESTAREA_H

#include <QObject>

class TestArea : public QObject
{
    Q_OBJECT

public:
    explicit TestArea(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTAREA_H
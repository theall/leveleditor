#ifndef TESTSOUND_H
#define TESTSOUND_H

#include <QObject>

class TestSound : public QObject
{
    Q_OBJECT

public:
    explicit TestSound(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTSOUND_H
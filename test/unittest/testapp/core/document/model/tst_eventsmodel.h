#ifndef TESTEVENTSMODEL_H
#define TESTEVENTSMODEL_H

#include <QObject>

class TestEventsModel : public QObject
{
    Q_OBJECT

public:
    explicit TestEventsModel(QObject *parent = 0);
private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTEVENTSMODEL_H

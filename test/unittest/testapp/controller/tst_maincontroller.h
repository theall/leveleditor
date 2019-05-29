#ifndef TESTMAINCONTROLLER_H
#define TESTMAINCONTROLLER_H

#include <QObject>

class TestMainController : public QObject
{
    Q_OBJECT

public:
    explicit TestMainController(QObject *parent = 0);

private Q_SLOTS:
    void testJoint();
    void testSetCurrentDocument();
};

#endif // TESTMAINCONTROLLER_H

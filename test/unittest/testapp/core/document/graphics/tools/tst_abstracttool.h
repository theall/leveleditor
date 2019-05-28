#ifndef TESTABSTRACTTOOL_H
#define TESTABSTRACTTOOL_H

#include <QObject>

class TestAbstractTool : public QObject
{
    Q_OBJECT

public:
    explicit TestAbstractTool(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTABSTRACTTOOL_H
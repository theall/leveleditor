#ifndef TESTOBJECTUNDOCOMMAND_H
#define TESTOBJECTUNDOCOMMAND_H

#include <QObject>

class TestObjectUndoCommand : public QObject
{
    Q_OBJECT

public:
    explicit TestObjectUndoCommand(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTOBJECTUNDOCOMMAND_H
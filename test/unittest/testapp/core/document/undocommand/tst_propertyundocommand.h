#ifndef TESTPROPERTYUNDOCOMMAND_H
#define TESTPROPERTYUNDOCOMMAND_H

#include <QObject>

class TestPropertyUndoCommand : public QObject
{
    Q_OBJECT

public:
    explicit TestPropertyUndoCommand(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTPROPERTYUNDOCOMMAND_H
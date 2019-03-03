#ifndef DOCUMENTPROPERTYCOMMAND_H
#define DOCUMENTPROPERTYCOMMAND_H

#include <QVariant>
#include <QUndoCommand>
#include "../base/property.h"

class TPropertyItem;

class TPropertyUndoCommand : public QUndoCommand
{
public:
    TPropertyUndoCommand(
            TPropertyItem *propertyItem,
            PropertyID command,
            const QVariant &newValue,
            QUndoCommand *parent = Q_NULLPTR);
    TPropertyUndoCommand(
            const QList<TPropertyItem*> &propertyItems,
            TPropertyItem *propertyItem,
            const QVariant &newValue,
            QUndoCommand *parent = Q_NULLPTR);
    ~TPropertyUndoCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    int id() const Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *command) Q_DECL_OVERRIDE;

    QList<TPropertyItem*> propertyItems() const;

    QVariant newValue() const;

private:
    PropertyID mCommand;
    QVariant mNewValue;
    QVariant mOldValue;
    QList<TPropertyItem*> mPropertyItems;
};

#endif // DOCUMENTPROPERTYCOMMAND_H

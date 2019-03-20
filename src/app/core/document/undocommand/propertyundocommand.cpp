#include "propertyundocommand.h"

#include "../property/property.h"
#include "../property/propertyitem.h"

#include <QCoreApplication>

#define tr(x) QCoreApplication::translate("UndoCommand", x)

const QString g_commandText[PID_COUNT] = {
    tr(""),
    tr("Change name"),
    tr("Change author"),
    tr("Change email"),
    tr("Change version"),
    tr("Change comment"),
    tr("Change background color"),
    tr("Rename action"),
    tr("Change action vector"),
    tr("Change frame image"),
    tr("Change frame vector"),
    tr("Change frame anti-gravity"),
    tr("Change frame interrupt type"),
    tr("Change frame duration"),
    tr("Change frame anchor"),
    tr("Adjust area"),
    tr("Rotate buckle"),
    tr("Change sound set auto play"),
    tr("Change sound set play method"),
    tr("Change sound item source"),
    tr("Change sound item loop"),
    tr("Change sound item delay"),
    tr("Change vector item type"),
    tr("Change vector item vector")
};

TPropertyUndoCommand::TPropertyUndoCommand(TPropertyItem *propertyItem,
                                           PropertyID command,
                                           const QVariant &newValue,
                                           QUndoCommand *parent) :
    QUndoCommand(parent)
  , mCommand(command)
  , mNewValue(newValue)
  , mOldValue(propertyItem->value())
{
    mPropertyItems.append(propertyItem);
    setText(g_commandText[command]);
}

TPropertyUndoCommand::TPropertyUndoCommand(
        const QList<TPropertyItem *> &propertyItems,
        TPropertyItem *propertyItem,
        const QVariant &value,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mCommand(propertyItem->propertyId())
  , mNewValue(value)
  , mOldValue(propertyItem->value())
  , mPropertyItems(propertyItems)
{
    setText(g_commandText[mCommand]);
}

TPropertyUndoCommand::~TPropertyUndoCommand()
{

}

void TPropertyUndoCommand::undo()
{
    for(TPropertyItem *item : mPropertyItems)
        item->setValue(mOldValue);
}

void TPropertyUndoCommand::redo()
{
    for(TPropertyItem *item : mPropertyItems)
        item->setValue(mNewValue);
}

int TPropertyUndoCommand::id() const
{
    return mCommand;
}

bool TPropertyUndoCommand::mergeWith(const QUndoCommand *command)
{
    if (command->id() != mCommand)
        return false;

    const TPropertyUndoCommand *other = static_cast<const TPropertyUndoCommand*>(command);
    if(!other || mPropertyItems!=other->propertyItems())
        return false;

    mNewValue = other->newValue();
    return true;
}

QList<TPropertyItem *> TPropertyUndoCommand::propertyItems() const
{
    return mPropertyItems;
}

QVariant TPropertyUndoCommand::newValue() const
{
    return mNewValue;
}

#include "shortcutmodel.h"

TShortcutModel::TShortcutModel(QObject *parent) :
    QStandardItemModel(parent)
{
    setHorizontalHeaderItem(0, new QStandardItem(tr("Command")));
    setHorizontalHeaderItem(1, new QStandardItem(tr("Shortcut")));
}

void TShortcutModel::setFilter(const QString &filter)
{
    load(filter);
}

void TShortcutModel::setShortcutList(QStringList shortcuts)
{
    mDuplicatedShortcuts.clear();

    while(shortcuts.size()>0)
    {
        QString shortcut = shortcuts.takeFirst();
        if(shortcuts.contains(shortcut))
        {
            mDuplicatedShortcuts.append(shortcut);
            shortcuts.removeAll(shortcut);
        }
    }
}

QVariant TShortcutModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::TextColorRole && index.column()==1)
    {
        QString s = QStandardItemModel::data(index, Qt::DisplayRole).toString();
        if(mDuplicatedShortcuts.contains(s))
            return QColor(Qt::red);
    }
    return QStandardItemModel::data(index, role);
}


void TShortcutModel::updateShortcut()
{
    QStringList shortcuts;
    TActionMap *actionMap = TShortKeyManager::instance()->actionMap();
    for(TActionMap::iterator i=actionMap->begin();i!=actionMap->end();i++)
    {
        TActionList *actionList = i.value();
        for(auto action : *actionList)
        {
            QString text = action->text();
            if(text.indexOf(mFilter, 0, Qt::CaseInsensitive)>-1)
            {
                QString shortcut = action->shortcut().toString();
                shortcuts.append(shortcut);
            }
        }
    }

    setShortcutList(shortcuts);
}

void TShortcutModel::load(const QString &filter)
{
    TActionMap *actionMap = TShortKeyManager::instance()->actionMap();
    clear();

    QStringList shortcuts;
    int index = 0;
    for(TActionMap::iterator i=actionMap->begin();i!=actionMap->end();i++)
    {
        TActionList *actionList = i.value();

        for(auto action : *actionList)
        {
            QString text = action->text();
            if(text.indexOf(filter, 0, Qt::CaseInsensitive)>-1)
            {
                QString shortcut = action->shortcut().toString();
                QStandardItem *actionName = new QStandardItem(text);
                QStandardItem *actionShortcut = new QStandardItem(shortcut);
                actionShortcut->setData(QVariant::fromValue(action));
                setItem(index, 0, actionName);
                setItem(index++, 1, actionShortcut);
                shortcuts.append(shortcut);
            }
        }
    }

    setShortcutList(shortcuts);
    mFilter = filter;
}


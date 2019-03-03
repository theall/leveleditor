#include "qcomboboxex.h"

#include <QCompleter>

QComboBoxEx::QComboBoxEx(QWidget* parent) :
    QComboBox(parent)
{
    setEditable(true);
    setDuplicatesEnabled(false);
    setInsertPolicy(QComboBox::InsertAtTop);
    setMaxCount(20);
    setMaxVisibleItems(20);

    completer()->setCaseSensitivity(Qt::CaseSensitive);
}

QComboBoxEx::~QComboBoxEx()
{

}

void QComboBoxEx::setDefault(QList<QString> items)
{
    mDefaultList = items;
}

void QComboBoxEx::setDefault(QSet<QString> items)
{
    mDefaultList = items.toList();
}

void QComboBoxEx::setDefault(QString item)
{
    mDefaultList.clear();
    mDefaultList.append(item);
}

void QComboBoxEx::setDefault(QStringList items)
{
    mDefaultList = items;
}

void QComboBoxEx::initialize(QStringList _list, QString currentText)
{
    insertItems(-1, _list);
    setCurrentText(currentText);
}

QStringList QComboBoxEx::items()
{
    QStringList items;
    int itemCount = count();
    for(int i=0;i<itemCount;i++)
        items.append(itemText(i));
    return items;
}

void QComboBoxEx::save()
{
    QString item = currentText();
    if(item.isEmpty())
        return;

    QStringList _items = items();
    blockSignals(true);
    if(!_items.contains(item))
        _items.insert(0, item);
    clear();
    addItems(_items);

    setCurrentText(item);
    blockSignals(false);
    emit itemsChanged(_items, item);
}

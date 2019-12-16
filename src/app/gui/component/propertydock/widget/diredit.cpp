#include "diredit.h"

int fleeDirToEnumIndex(int value)
{
    int index = 0;
    if(value == 2)
        index = 1;
    else if(value == 4)
        index = 2;
    return index;
}

int enumIndexToFleeDirValue(int index)
{
    int value = 0;
    if(index == 1)
        value = 2;
    else if(index == 2)
        value = 4;
    return value;
}

TDirEdit::TDirEdit(QWidget *parent) :
    QComboBox(parent)
{
    QStringList dirs;
    dirs.append(tr("Left"));
    dirs.append(tr("Right"));
    addItems(dirs);
}

void TDirEdit::setValue(int value)
{
    if(mValue == value)
        return;

    mValue = value;
    setCurrentIndex(fleeDirToEnumIndex(value));
}

int TDirEdit::value() const
{
    return enumIndexToFleeDirValue(currentIndex());
}


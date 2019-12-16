#ifndef TDIREDIT_H
#define TDIREDIT_H

#include <QComboBox>

class TDirEdit : public QComboBox
{
public:
    explicit TDirEdit(QWidget *parent = Q_NULLPTR);

    void setValue(int value);
    int value() const;

    static QString valueToString(int value);

private:
    int mValue;
};

#endif // TDIREDIT_H

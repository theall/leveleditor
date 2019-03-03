#ifndef QCOMBOBOXEX_H
#define QCOMBOBOXEX_H

#include <QSet>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QStringList>

class QComboBoxEx : public QComboBox
{
    Q_OBJECT

public:
    explicit QComboBoxEx(QWidget* parent=NULL);
    ~QComboBoxEx();

    void setDefault(QList<QString> items);
    void setDefault(QSet<QString> items);
    void setDefault(QString item);
    void setDefault(QStringList items);
    void initialize(QStringList _list=QStringList(), QString currentText="");
    QStringList items();
    void save();

signals:
    void itemsChanged(QStringList, QString);

private:
    QStringList mDefaultList;

};

#endif // QCOMBOBOXEX_H

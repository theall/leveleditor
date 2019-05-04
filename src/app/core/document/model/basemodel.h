#ifndef TBASEMODEL_H
#define TBASEMODEL_H

#include <QAbstractTableModel>

class TBaseModel : public QAbstractTableModel
{
public:
    explicit TBaseModel(QObject *parent = Q_NULLPTR);

    QString name() const;
    void setName(const QString &name);

private:
    QString mName;
};

#endif // TBASEMODEL_H

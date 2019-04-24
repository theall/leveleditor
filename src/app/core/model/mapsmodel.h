#ifndef TMAPSMODEL_H
#define TMAPSMODEL_H

#include <QObject>
#include "../assets/maps.h"

class TMapsModel : public QObject
{
    Q_OBJECT

public:
    explicit TMapsModel(QObject *parent = Q_NULLPTR);
    ~TMapsModel();

    TModuleList moduleList() const;
    void setModuleList(const TModuleList &moduleList);

    int add(TModule *module, int index = -1);
    int remove(int index);
    int remove(TModule *module);

signals:
    void moduleAdded(TModule *module, int index);
    void moduleRemoved(TModule *module, int index);

private:
    TModuleList mModuleList;
};

#endif // TMAPSMODEL_H

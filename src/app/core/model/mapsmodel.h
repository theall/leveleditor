#ifndef TMAPSMODEL_H
#define TMAPSMODEL_H

#include <QAbstractItemModel>
#include "../assets/maps.h"

class TMapsModel : public QAbstractItemModel
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

    TModule *currentModule() const;
    QColor openedColor() const;
    void setOpenedColor(const QColor &openedColor);
    QColor dirtyColor() const;
    void setDirtyColor(const QColor &dirtyColor);

    TMap *find(const QString &mapFilePath) const;
    TMap *find(TDocument *document) const;
    TMap *createMap(const QString &moduleName, const TMap::Type &mapType, int mapId);

signals:
    void moduleAdded(TModule *module, int index);
    void moduleRemoved(TModule *module, int index);

private:
    QColor mOpenedColor;
    QColor mDirtyColor;
    TModule *mCurrentModule;
    TModuleList mModuleList;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TMAPSMODEL_H

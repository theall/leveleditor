#ifndef VECTORTABLEMODEL_H
#define VECTORTABLEMODEL_H

#include <QAbstractTableModel>
#include "vectoritem.h"

class TVectorTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TVectorTableModel(QObject *parent = nullptr);
    ~TVectorTableModel();

    void clear();
    std::vector<Model::TVectorItem*> toModel() const;
    void loadFromModel(const std::vector<Model::TVectorItem*> &vectorItemList, void *context=nullptr);

    TVectorItemList vectorItemList() const;
    TVectorItem *getVectorItem(int index) const;
    int vectorItemsCount() const;
    void setVectorItemList(const TVectorItemList &vectorItemList);

    int addVectorItem(TVectorItem *vectorItem, int index = -1);
    QList<int> addVectorItemList(const TVectorItemList &vectorItemList, const QList<int> &indexList = QList<int>());
    int removeVectorItem(TVectorItem *vectorItem);
    QList<int> removeVectorItemList(const TVectorItemList &vectorItemList);

    void cmdAddVector(TVectorItem *vectorItem);
    void cmdAddVectorList(const QList<QPointF> &vectorList);
    void cmdAddVectorList(const TVectorItemList &vectorItemList);
    void cmdRemoveVector(TVectorItem *vectorItem);
    void cmdRemoveVectorList(const TVectorItemList &vectorItemList);

    bool hasVector() const;
    bool hasValidVector() const;

    QPointF vectorAt(int index) const;

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

signals:
    void vectorPropertyChanged(TPropertyItem *propertyItem, const QVariant &value);
    void vectorItemsAdded(const TVectorItemList &vectorItemList, const QList<int> indexList);
    void vectorItemsRemoved(const TVectorItemList &vectorItemList, const QList<int> indexList);
    void vectorItemsCountChanged(int oldCount, int currentCount);

private slots:
    void slotVectorItemPropertyChanged(TPropertyItem *propertyItem, const QVariant &value);

private:
    TDocument *mDocument;
    TVectorItemList mVectorItemList;

    int internalAddVectorItem(TVectorItem *vectorItem, int index = -1);
    int internalRemoveVectorItem(TVectorItem *vectorItem);
};

QDataStream &operator<<(QDataStream& out, const TVectorTableModel& vectorTableModel);
QDataStream &operator>>(QDataStream& in, TVectorTableModel& vectorTableModel);

#endif // VECTORTABLEMODEL_H

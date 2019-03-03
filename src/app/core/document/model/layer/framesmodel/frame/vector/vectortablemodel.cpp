#include "vectortablemodel.h"

#include "vectortableundocommand.h"
#include "../../../../../document.h"
#include "../../../../../../../../../../../utils/base/utils.h"

static const int COLUMN_INDEX = 0;
static const int COLUMN_VECTOR = 1;
static const int COLUMN_VECTOR_SUM = 2;

TVectorTableModel::TVectorTableModel(QObject *parent) :
    QAbstractTableModel(parent)
  , mDocument(nullptr)
{
    QObject *obj = parent;
    while (obj) {
        mDocument = qobject_cast<TDocument*>(obj);
        if(mDocument)
            break;
        obj = obj->parent();
    }
    if(!mDocument)
        throw QString("File:%1, Line:%2: Parent must be document.").arg(__FILE__).arg(__LINE__);
}

TVectorTableModel::~TVectorTableModel()
{
    clear();
}

void TVectorTableModel::clear()
{
    FREE_CONTAINER(mVectorItemList);
}

std::vector<Model::TVectorItem *> TVectorTableModel::toModel() const
{
    std::vector<Model::TVectorItem *> vectorItemsList;
    for(TVectorItem *vectorItem : mVectorItemList)
    {
        vectorItemsList.emplace_back(vectorItem->toModel());
    }
    return vectorItemsList;
}

void TVectorTableModel::loadFromModel(const std::vector<Model::TVectorItem *> &vectorItemList, void *context)
{
    Q_UNUSED(context);

    clear();
    for(Model::TVectorItem *vectorItemModel : vectorItemList)
    {
        TVectorItem *vectorItem = new TVectorItem(this);
        vectorItem->loadFromModel(*vectorItemModel, this);
        internalAddVectorItem(vectorItem);
    }
}

TVectorItemList TVectorTableModel::vectorItemList() const
{
    return mVectorItemList;
}

TVectorItem *TVectorTableModel::getVectorItem(int index) const
{
    if(index>=0 && index<mVectorItemList.size())
        return mVectorItemList.at(index);

    return nullptr;
}

int TVectorTableModel::vectorItemsCount() const
{
    return mVectorItemList.size();
}

void TVectorTableModel::setVectorItemList(const TVectorItemList &vectorItemList)
{
    FREE_CONTAINER(mVectorItemList);
    mVectorItemList = vectorItemList;
}

int TVectorTableModel::internalAddVectorItem(TVectorItem *vectorItem, int index)
{
    if(!vectorItem)
        return -1;

    int ret = index;
    int itemCount = mVectorItemList.size();
    if(ret<0 || ret>itemCount)
        ret = itemCount;

    connect(vectorItem,
            SIGNAL(propertyChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotVectorItemPropertyChanged(TPropertyItem*,QVariant)));
    beginInsertRows(QModelIndex(), ret, ret);
    mVectorItemList.insert(ret, vectorItem);
    endInsertRows();
    return ret;
}

int TVectorTableModel::internalRemoveVectorItem(TVectorItem *vectorItem)
{
    int ret = mVectorItemList.indexOf(vectorItem);
    if(ret != -1) {
        vectorItem->disconnect(this);
        beginRemoveRows(QModelIndex(), ret, ret);
        mVectorItemList.removeAt(ret);
        endRemoveRows();
    }
    return ret;
}

int TVectorTableModel::addVectorItem(TVectorItem *vectorItem, int index)
{
    if(!vectorItem)
        return -1;

    TVectorItemList vectorItemList;
    vectorItemList.append(vectorItem);

    QList<int> indexList;
    indexList.append(index);
    QList<int> ret = addVectorItemList(vectorItemList, indexList);
    if(ret.isEmpty())
        return -1;

    return ret.at(0);
}

QList<int> TVectorTableModel::addVectorItemList(const TVectorItemList &vectorItemList, const QList<int> &indexList)
{
    QList<int> ret = indexList;
    int vectorItemSize = vectorItemList.size();
    if(vectorItemSize != indexList.size())
    {
        ret.clear();
        for(int i=0;i<vectorItemSize;i++)
        {
            ret.append(-1);
        }
    }
    int oldVectorItemSize = mVectorItemList.size();
    for(int i=0;i<vectorItemSize;i++)
    {
        internalAddVectorItem(vectorItemList[i], ret[i]);
    }
    if(vectorItemSize > 0) {
        emit layoutChanged();
        emit vectorItemsAdded(vectorItemList, ret);
        emit vectorItemsCountChanged(oldVectorItemSize, mVectorItemList.size());
    }
    return indexList;
}

int TVectorTableModel::removeVectorItem(TVectorItem *vectorItem)
{
    if(!vectorItem)
        return -1;

    TVectorItemList vectorItemList;
    vectorItemList.append(vectorItem);
    QList<int> ret = removeVectorItemList(vectorItemList);
    if(ret.isEmpty())
        return -1;

    return ret.at(0);
}

QList<int> TVectorTableModel::removeVectorItemList(const TVectorItemList &vectorItemList)
{
    QList<int> ret;
    TVectorItemList vectorItemsRet;
    int oldVectorItemSize = mVectorItemList.size();
    for(TVectorItem *vectorItem : vectorItemList)
    {
        if(!vectorItem)
            continue;

        int t = internalRemoveVectorItem(vectorItem);
        if(t < 0)
            continue;

        ret.append(t);
        vectorItemsRet.append(vectorItem);
    }
    if(ret.size() > 0) {
        emit layoutChanged();
        emit vectorItemsRemoved(vectorItemsRet, ret);
        emit vectorItemsCountChanged(oldVectorItemSize, mVectorItemList.size());
    }
    return ret;
}

void TVectorTableModel::cmdAddVector(TVectorItem *vectorItem)
{
    TVectorItemList vectorItemList;
    vectorItemList.append(vectorItem);
    cmdAddVectorList(vectorItemList);
}

void TVectorTableModel::cmdAddVectorList(const QList<QPointF> &vectorList)
{
    TVectorItemList vectorItemList;
    for(QPointF vector : vectorList)
    {
        TVectorItem *vectorItem = new TVectorItem(this);
        vectorItem->setVector(vector);
        vectorItemList.append(vectorItem);
    }
    cmdAddVectorList(vectorItemList);
}

void TVectorTableModel::cmdAddVectorList(const TVectorItemList &vectorItemList)
{
    if(!mDocument || vectorItemList.size()<=0)
        return;

    TVectorTableUndoCommand *undoCommand = new TVectorTableUndoCommand(VTUC_ADD, this, vectorItemList);
    mDocument->addUndoCommand(undoCommand);
}

void TVectorTableModel::cmdRemoveVector(TVectorItem *vectorItem)
{
    if(!vectorItem || !mDocument)
        return;

    TVectorTableUndoCommand *undoCommand = new TVectorTableUndoCommand(VTUC_REMOVE, this, vectorItem);
    mDocument->addUndoCommand(undoCommand);
}

void TVectorTableModel::cmdRemoveVectorList(const TVectorItemList &vectorItemList)
{
    if(!mDocument || vectorItemList.size()<=0)
        return;

    TVectorTableUndoCommand *undoCommand = new TVectorTableUndoCommand(VTUC_REMOVE, this, vectorItemList);
    mDocument->addUndoCommand(undoCommand);
}

bool TVectorTableModel::hasVector() const
{
    return mVectorItemList.size()>0;
}

bool TVectorTableModel::hasValidVector() const
{
    for(TVectorItem *vectorItem : mVectorItemList)
    {
        if(!vectorItem->vector().isNull())
            return true;
    }
    return false;
}

QPointF TVectorTableModel::vectorAt(int index) const
{
    if(index>=0 && index<mVectorItemList.size())
    {
        return mVectorItemList.at(index)->vector();
    }
    return QPointF(0.0,0.0);
}

int TVectorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mVectorItemList.size();
}

int TVectorTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TVectorTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int row = index.row();
        if(row>=0 && row<mVectorItemList.size())
        {
            int col = index.column();
            if(col==COLUMN_INDEX)
                return row+1;
            else if(col==COLUMN_VECTOR) {
                QPointF vector = mVectorItemList.at(row)->vector();
                return QString("(%1, %2)").arg(vector.x()).arg(vector.y());
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags TVectorTableModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index);
}

QVariant TVectorTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(role == Qt::DisplayRole)
    {
        switch (section) {
        case COLUMN_INDEX:
            return tr("No");
            break;
        case COLUMN_VECTOR:
            return tr("Vector");
            break;
        default:
            break;
        }
    }
    return QVariant();
}

void TVectorTableModel::slotVectorItemPropertyChanged(TPropertyItem *propertyItem, const QVariant &value)
{
    if(!propertyItem)
        return;

    PropertyID id = propertyItem->propertyId();
    if(id==PID_VECTOR_ITEM_VECTOR || id==PID_VECTOR_ITEM_TYPE)
    {
        emit vectorPropertyChanged(propertyItem, value);
        emit layoutChanged();
    }
}

QDataStream &operator<<(QDataStream &out, const TVectorTableModel &vectorTableModel)
{
    TVectorItemList vectorItemList = vectorTableModel.vectorItemList();
    out << vectorItemList.size();
    for(TVectorItem *vectorItem : vectorItemList)
    {
        out << *vectorItem;
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, TVectorTableModel &vectorTableModel)
{
    int vectorItemSize = 0;
    TVectorItemList vectorItemList;
    in >> vectorItemSize;
    for(int i=0;i<vectorItemSize;i++)
    {
        TVectorItem *vectorItem = new TVectorItem(&vectorTableModel);
        in >> *vectorItem;
        vectorItemList.append(vectorItem);
    }
    vectorTableModel.setVectorItemList(vectorItemList);
    return in;
}

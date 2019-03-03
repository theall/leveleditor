#include "framesmodel.h"
#include "frame/frame.h"

TFramesModel::TFramesModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

TFramesModel::~TFramesModel()
{

}

TFrame *TFramesModel::frameAt(int row, int column)
{
    return frameAt(row*columnCount()+column);
}

TFrame *TFramesModel::frameAt(const QModelIndex &index)
{
    return frameAt(index.row(), index.column());
}

TFrame *TFramesModel::frameAt(int index)
{
    if(index>=0 && index<mFramesList.size())
        return mFramesList.at(index);

    return nullptr;
}

TFrame *TFramesModel::getFrame(int index)
{
    if(index>=0 && index<mFramesList.size())
        return mFramesList.at(index);

    return nullptr;
}

int TFramesModel::count()
{
    return mFramesList.size();
}

int TFramesModel::addFrame(TFrame *frame, int index)
{
    index = internalAddFrame(frame, index);
    updateAndFire();
    return index;
}

int TFramesModel::removeFrame(TFrame *frame)
{
    int i = internalRemoveFrame(frame);
    if(i != -1)
        updateAndFire();
    return i;
}

int TFramesModel::removeFrame(int index)
{
    TFrame *frame = getFrame(index);
    if(!frame)
        return -1;

    return removeFrame(frame);
}

QList<int> TFramesModel::addFrames(const QList<TFrame *> &frames, const QList<int> &indexes)
{
    QList<int> indexList = indexes;
    int frameSize = frames.size();
    if(frameSize != indexList.size())
    {
        indexList.clear();
        for(int i=0;i<frameSize;i++)
        {
            indexList.append(-1);
        }
    }
    for(int i=0;i<frameSize;i++)
    {
        internalAddFrame(frames[i], indexList[i]);
    }
    if(frameSize > 0)
        updateAndFire();

    return indexList;
}

QList<int> TFramesModel::removeFrames(const QList<TFrame *> &frames)
{
    QList<int> removedIndex;
    for(TFrame *frame : frames)
    {
        int i = internalRemoveFrame(frame);
        if(i != -1)
            removedIndex.append(i);
    }
    if(removedIndex.size() > 0) {
        updateAndFire();
    }

    return removedIndex;
}

QList<int> TFramesModel::removeFrames(const QList<int> &frameList)
{
    QList<int> removedIndex;
    for(int index : frameList)
    {
        int i = internalRemoveFrame(frameAt(index));
        if(i != -1)
            removedIndex.append(i);
    }
    if(removedIndex.size() > 0) {
        updateAndFire();
    }
    return removedIndex;
}

QList<int> TFramesModel::moveFrames(const QList<int> &frameIndexList, int pos)
{
    QList<int> indexList = frameIndexList;
    QList<int> posList;
    if(pos < 0)
        pos = mFramesList.size();
    for(int i=0;i<indexList.size();i++)
    {
        posList.append(pos+i);
    }
    return moveFrames(indexList, posList);
}

QList<int> TFramesModel::moveFrames(const QList<TFrame *> &frameList, int pos)
{
    QList<int> indexList;
    for(TFrame *frame : frameList)
    {
        int i = mFramesList.indexOf(frame);
        if(i >= 0)
            indexList.append(i);
    }
    return moveFrames(indexList, pos);
}

QList<int> TFramesModel::moveFrames(const QList<TFrame *> &frameList, const QList<int> &posList)
{
    QList<int> indexList;
    for(TFrame *frame : frameList)
    {
        int i = mFramesList.indexOf(frame);
        if(i >= 0)
            indexList.append(i);
    }
    return moveFrames(indexList, posList);
}

QList<int> TFramesModel::moveFrames(const QList<int> &frameIndexList, const QList<int> &posList)
{
    QList<int> indexList = frameIndexList;
    QList<int> newPosList = posList;
    int indexListSize = indexList.size();
    if(indexListSize<1 || indexListSize!=newPosList.size())
        return frameIndexList;

    int listSize = mFramesList.size();
    for(int &pos : newPosList)
    {
        if(pos<0 || pos>listSize)
            pos = listSize;
    }

    TFramesList frames;
    for (int i=0;i<indexListSize;i++) {
        if(i<0 || i>=mFramesList.size())
            Q_ASSERT(false);

        int currentIndex = indexList[i];
        frames.append(mFramesList.takeAt(currentIndex));
        // Update rest index
        for(int j=i;j<indexListSize;j++)
        {
            if(currentIndex < indexList[j])
                indexList[j] = indexList[j] - 1;
        }
        // Update pos list
        for(int k=0;k<indexListSize;k++)
        {
            if(currentIndex < newPosList[k])
                newPosList[k] = newPosList[k] - 1;
        }
    }
    QList<int> indexesMoved;
    for(int i=0;i<indexListSize;i++)
    {
        int currentIndex = newPosList[i];
        mFramesList.insert(currentIndex, frames[i]);
        for(int j=i;j<indexListSize;j++)
        {
            if(currentIndex < newPosList[j])
                newPosList[j] = newPosList[j] + 1;
        }
        indexesMoved.append(newPosList[i]);
    }
    updateFramesBuddy();
    updateAndFire();
    return indexesMoved;
}

Model::TFramesList TFramesModel::toFrameList() const
{
    Model::TFramesList framesList;
    for(TFrame *frame : mFramesList)
    {
        framesList.emplace_back(frame->toModel());
    }
    return framesList;
}

void TFramesModel::loadFromModel(const Model::TFramesList framesList, void *context)
{
    FREE_CONTAINER(mFramesList);
    for(Model::TFrame *frameModel : framesList)
    {
        TFrame *frame = new TFrame(this);
        frame->loadFromModel(*frameModel, context);
        internalAddFrame(frame);
    }
    if(framesList.size() > 0)
        updateAndFire();
}

void TFramesModel::slotFramePropertyChanged(TPropertyItem *item, const QVariant &value)
{
    TFrame *frame = static_cast<TFrame*>(sender());
    if(frame) {
        emit framePropertyChanged(frame, item->propertyId(), value);
    }
}

void TFramesModel::slotFrameChanged()
{
    TFrame *frame = static_cast<TFrame*>(sender());
    if(frame)
    {
        emit frameChanged(frame);
    }
    emit layoutChanged();
}

QList<TFrame *> TFramesModel::getFramesList() const
{
    return mFramesList;
}

QList<int> TFramesModel::getFramesIndexList(const QList<TFrame *> &frames)
{
    QList<int> ret;
    for(TFrame *frame : frames)
    {
        int i = mFramesList.indexOf(frame);
        ret.append(i);
    }
    return ret;
}

QList<TFrame *> TFramesModel::getFramesList(const QList<int> &frameList)
{
    QList<TFrame *> framesList;
    for(int i : frameList)
    {
        framesList.append(getFrame(i));
    }
    return framesList;
}

int TFramesModel::frameIndexAt(const QModelIndex &index)
{
    return index.column() + index.row() * columnCount();
}

void TFramesModel::updateAndFire()
{
    updateFramesBuddy();
    emit framesChanged();
    emit layoutChanged();
}

void TFramesModel::updateFramesBuddy()
{
    int frameCount = mFramesList.size();
    if(frameCount < 1)
        return;

    mFramesList[0]->setPrevBuddy(TFrame::standardFrame());
    for(int i=1;i<frameCount;i++)
    {
        mFramesList[i]->setPrevBuddy(mFramesList[i-1]);
    }
}

int TFramesModel::internalAddFrame(TFrame *frame, int index)
{
    if(!frame)
        return -1;

    if(index < 0)
        index = mFramesList.size();

    beginInsertColumns(QModelIndex(), index, index);
    mFramesList.insert(index, frame);
    endInsertColumns();

    connect(frame,
            SIGNAL(propertyChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotFramePropertyChanged(TPropertyItem*,QVariant)));

    connect(frame,
            SIGNAL(frameChanged()),
            this,
            SLOT(slotFrameChanged()));

    return index;
}

int TFramesModel::internalRemoveFrame(TFrame *frame)
{
    int i = mFramesList.indexOf(frame);
    if(i != -1) {
        beginRemoveColumns(QModelIndex(), i, i);
        mFramesList.removeAt(i);
        endRemoveColumns();
        frame->disconnect(this);
        frame->setPrevBuddy(nullptr);
    }
    return i;
}

int TFramesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

int TFramesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return mFramesList.size();
}

QVariant TFramesModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole)
    {
        int i = index.column() + index.row() * columnCount();
        if(i>-1 && i<mFramesList.size())
        {
            return mFramesList.at(i)->pixmap()->pixmap();
        }
    }
    return QVariant();
}

Qt::ItemFlags TFramesModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index)
            | Qt::ItemIsDragEnabled
            | Qt::ItemIsDropEnabled;
}

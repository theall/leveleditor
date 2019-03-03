#ifndef FRAMESMODEL_H
#define FRAMESMODEL_H

#include <QAbstractTableModel>

#include <gameutils.h>
#include "../../../base/property.h"

class TFrame;
class TPropertyItem;

class TFramesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TFramesModel(QObject *parent = nullptr);
    ~TFramesModel();

    TFrame *frameAt(int row, int column);
    TFrame *frameAt(const QModelIndex &index);
    TFrame *frameAt(int index);
    TFrame *getFrame(int index);
    int count();

    QList<TFrame *> getFramesList() const;
    QList<int> getFramesIndexList(const QList<TFrame *> &frames);
    QList<TFrame *> getFramesList(const QList<int> &frameList);

    int addFrame(TFrame *frame, int index=-1);
    int removeFrame(TFrame *frame);
    int removeFrame(int index);
    QList<int> addFrames(const QList<TFrame *> &frames, const QList<int> &indexList=QList<int>());
    QList<int> removeFrames(const QList<TFrame *> &frames);
    QList<int> removeFrames(const QList<int> &frameList);
    QList<int> moveFrames(const QList<int> &frameIndexList, int pos);
    QList<int> moveFrames(const QList<TFrame *> &frameList, int pos);
    QList<int> moveFrames(const QList<TFrame *> &frameList, const QList<int> &posList);
    QList<int> moveFrames(const QList<int> &frameIndexList, const QList<int> &posList);

    QJsonArray toJson() const;
    Model::TFramesList toFrameList() const;
    void loadFromModel(const Model::TFramesList framesList, void *context);
    void updateFramesBuddy();

signals:
    void framesChanged();
    void frameChanged(TFrame *frame);
    void framePropertyChanged(TFrame *frame, int propertyId, const QVariant &value);

private slots:
    void slotFramePropertyChanged(TPropertyItem *item, const QVariant &value);
    void slotFrameChanged();

private:
    QList<TFrame*> mFramesList;

    int frameIndexAt(const QModelIndex &index);
    void updateAndFire();
    int internalAddFrame(TFrame *frame, int index=-1);
    int internalRemoveFrame(TFrame *frame);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // FRAMESMODEL_H

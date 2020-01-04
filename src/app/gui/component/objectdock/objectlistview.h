#ifndef OBJECTLISTVIEW_H
#define OBJECTLISTVIEW_H

#include <QMenu>
#include <QAction>
#include <QTableView>

class TModsTree;

class TObjectListView : public QTableView
{
     Q_OBJECT

public:
    TObjectListView(QWidget *parent=nullptr);
    ~TObjectListView();

    QList<int> getSelectedIndexes();
    int getCurrentIndex();
    void selectRow(int row, QModelIndex &parent);
    void selectItems(QList<int> posList, bool locate = true);
    QString getCheckMimeType() const;
    void setCheckMimeType(const QString &checkMimeType);
    void setModel(QAbstractItemModel *model);

signals:
    void indexSelected(int index);
    void indexPressed(const QModelIndex &index);

private:
    QString mCheckMimeType;
    QRect mHighlightRect;

    inline int getIndex(const QModelIndex &index);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // OBJECTLISTVIEW_H

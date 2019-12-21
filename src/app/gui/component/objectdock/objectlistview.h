#ifndef OBJECTLISTVIEW_H
#define OBJECTLISTVIEW_H

#include <QMenu>
#include <QAction>
#include <QTreeView>

class TModsTree;

class TObjectListView : public QTreeView
{
     Q_OBJECT

public:
    TObjectListView(QWidget *parent=nullptr);
    ~TObjectListView();

    QList<int> getSelectedIndexes();
    int getCurrentIndex();
    void selectRow(int row);
    void selectItems(QList<int> posList, bool locate = true);
    QString getCheckMimeType() const;
    void setCheckMimeType(const QString &checkMimeType);
    void setModel(QAbstractItemModel *model);

signals:
    void indexSelected(int index);
    void indexPressed(int index);

private:
    QString mCheckMimeType;
    QRect mHighlightRect;

    inline int getIndex(const QModelIndex &index);

//protected:
//    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
//    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
//    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
//    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
//    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

};

#endif // OBJECTLISTVIEW_H

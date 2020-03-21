#ifndef TMODSTREE_H
#define TMODSTREE_H

#include <QEvent>
#include <QTreeView>
#include <QMenu>

class TModsTree : public QTreeView
{
    Q_OBJECT

public:
    explicit TModsTree(QWidget *parent = Q_NULLPTR);
    ~TModsTree();

private:
    void retranslateUi();

    QModelIndex mIndex;
    QMenu *mMenu;

signals:
    void modelIndexDoubleClicked(const QModelIndex &index);

private slots:
    void slotCustomContextMenuRequested(const QPoint &pos);
    void slotActionTriggered(QAction *open);

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model);
};

#endif // TMODSTREE_H

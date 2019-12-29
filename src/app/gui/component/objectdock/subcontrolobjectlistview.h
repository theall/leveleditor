#ifndef TSUBCONTROLOBJECTLISTVIEW_H
#define TSUBCONTROLOBJECTLISTVIEW_H

#include <QTableView>

class TSubControlObjectListView : public QTableView
{
    Q_OBJECT

public:
    TSubControlObjectListView(QWidget *parent=nullptr);
    ~TSubControlObjectListView();

    QList<int> getSelectedIndexes();
    int getCurrentIndex();
    void selectRow(int row);
    void setModel(QAbstractItemModel *model);

private:
    inline int getIndex(const QModelIndex &index);

signals:
    void indexPressed(int index);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // TSUBCONTROLOBJECTLISTVIEW_H

#include "subcontrolobjectlistview.h"

#include <QHeaderView>

TSubcontrolObjectListView::TSubcontrolObjectListView(QWidget *parent)
{
    horizontalHeader()->setStretchLastSection(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);


}
TSubcontrolObjectListView::~TSubcontrolObjectListView()
{

}

void TSubcontrolObjectListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

void TSubcontrolObjectListView::selectRow(int row)
{
    QTableView::selectRow(row);
}

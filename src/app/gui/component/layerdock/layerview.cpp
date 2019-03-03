#include "layerview.h"

#include <QHeaderView>

TLayerView::TLayerView(QWidget *parent):
    QTreeView(parent),
    mActionAddForeLayer(new QAction(this)),
    mActionAddBackLayer(new QAction(this)),
    mActionRemoveLayer(new QAction(this)),
    mActionDuplicateLayer(new QAction(this)),
    mActionMergeLayerDown(new QAction(this)),
    mActionMoveLayerUp(new QAction(this)),
    mActionMoveLayerDown(new QAction(this)),
    mActionToggleOtherLayers(new QAction(this)),
    mActionLayerProperties(new QAction(this)),
    mContextMenu(new QMenu(this))
{
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setItemsExpandable(true);
    setUniformRowHeights(true);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(this, SIGNAL(pressed(QModelIndex)), SLOT(slotPressed(QModelIndex)));

    connect(this, SIGNAL(activated(QModelIndex)), SLOT(onActivated(QModelIndex)));

    connect(header(), SIGNAL(sectionResized(int,int,int)), this, SLOT(slotOnSectionResized(int)));
}

QSize TLayerView::sizeHint() const
{
    return QSize(130, 100);
}

QMenu *TLayerView::contextMenu()
{
    return mContextMenu;
}

//void TLayerView::setSceneDocument(TSceneDocument *sceneDocument)
//{
//    if (mDocument) {
//        mDocument->disconnect(this);
//        QItemSelectionModel *s = selectionModel();
//        disconnect(s, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//                   this, SLOT(slotCurrentRowChanged(QModelIndex)));
//    }

//    mDocument = sceneDocument;

//    if (mDocument) {
//        setModel(mDocument->layersModel());

//        connect(mDocument, SIGNAL(currentLayerIndexChanged(int)),
//                this, SLOT(slotCurrentLayerIndexChanged(int)));

//        QItemSelectionModel *s = selectionModel();
//        connect(s, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//                this, SLOT(slotCurrentRowChanged(QModelIndex)));

//        slotCurrentLayerIndexChanged(mDocument->currentLayerIndex());
//    } else {
//        setModel(nullptr);
//    }
//}

void TLayerView::slotCurrentRowChanged(const QModelIndex &index)
{
//    const int layer = mDocument->layersModel()->toLayerIndex(index);
//    mDocument->setCurrentLayerIndex(layer);
}

void TLayerView::slotPressed(const QModelIndex &index)
{
//    const int layerIndex = mDocument->layersModel()->toLayerIndex(index);
//    if (layerIndex != -1) {
//        Layer *layer = mDocument->scene()->layerAt(layerIndex);
//        mDocument->setCurrentObject(layer);
//    }
}

void TLayerView::contextMenuEvent(QContextMenuEvent *event)
{
    const QModelIndex index = indexAt(event->pos());
    const int layerIndex = -1;

    QMenu menu;
    menu.addAction(mActionAddForeLayer);
    menu.addAction(mActionAddBackLayer);
    menu.addAction(mActionRemoveLayer);

    if (layerIndex >= 0) {
        menu.addAction(mActionDuplicateLayer);
        menu.addAction(mActionMergeLayerDown);
        menu.addSeparator();
        menu.addAction(mActionMoveLayerUp);
        menu.addAction(mActionMoveLayerDown);
        menu.addSeparator();
        menu.addAction(mActionToggleOtherLayers);
        menu.addSeparator();
        menu.addAction(mActionLayerProperties);
    }

    menu.exec(event->globalPos());
}

void TLayerView::keyPressEvent(QKeyEvent *event)
{
    const QModelIndex index = currentIndex();
    if (!index.isValid())
        return;

    if (event->key() == Qt::Key_Delete) {
        emit requestRemoveObject(index.row());
        return;
    }

    QTreeView::keyPressEvent(event);
}

//void TLayerView::setSceneDocument(TSceneDocument *mapDoc)
//{
//    if (mapDoc == mDocument)
//        return;

//    if (mDocument)
//        mDocument->disconnect(this);

//    mDocument = mapDoc;

//    if (mDocument) {
//        setModel(mDocument->mapObjectModel());

//        const QSettings *settings = Preferences::instance()->settings();
//        const int firstSectionSize =
//                settings->value(QLatin1String(FIRST_SECTION_SIZE_KEY), 200).toInt();
//        header()->resizeSection(0, firstSectionSize);

//        connect(mDocument, SIGNAL(selectedObjectsChanged()),
//                this, SLOT(selectedObjectsChanged()));
//    } else {
//        setModel(nullptr);
//    }
//}

//void TLayerView::onPressed(const QModelIndex &index)
//{
//    if (TSceneObject *mapObject = model()->toMapObject(index))
//        mDocument->setCurrentObject(mapObject);
//    else if (ObjectGroup *objectGroup = model()->toObjectGroup(index))
//        mDocument->setCurrentObject(objectGroup);
//}

//void TLayerView::onActivated(const QModelIndex &index)
//{
//    if (TSceneObject *mapObject = model()->toMapObject(index)) {
//        mDocument->setCurrentObject(mapObject);
//        mDocument->emitEditCurrentObject();
//    }
//}

void TLayerView::slotOnSectionResized(int logicalIndex)
{
    if (logicalIndex != 0)
        return;

//    QSettings *settings = TPreferences::instance()->settings();
//    settings->setValue(QLatin1String(FIRST_SECTION_SIZE_KEY),
//                       header()->sectionSize(0));
}

void TLayerView::slotSelectionChanged(const QItemSelection &selected,
                                   const QItemSelection &deselected)
{
    QTreeView::selectionChanged(selected, deselected);
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    QList<int> rows;
    foreach (const QModelIndex &index, selectedRows) {
        rows.append(index.row());
    }

    emit onSelectionChanged(rows);
}

void TLayerView::selectRows(QList<int> rows, int newRow)
{    
    QAbstractItemModel *m = model();
    if(!m)
        return;

    clearSelection();
    foreach (int row, rows) {
        QModelIndex index = m->index(row, 0);
        selectionModel()->select(index, QItemSelectionModel::Select |  QItemSelectionModel::Rows);
    }

    if(newRow>=0)
        scrollTo(m->index(newRow, 0));
}

#include "framelistview.h"

#include <QPainter>
#include <QMimeData>
#include <QClipboard>
#include <QHeaderView>
#include <QResizeEvent>
#include <QGuiApplication>

TFrameListView::TFrameListView(QWidget *parent) :
    QTableView(parent)
  , mContextMenu(new QMenu(this))
  , mHighlightColor(Qt::green)
{
    setObjectName(QStringLiteral("framesView"));

    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);

    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setLayoutDirection(Qt::LeftToRight);

    setMouseTracking(true);
    setSortingEnabled(false);
    setShowGrid(false);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    //setDropIndicatorShown(true);
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);

    mActionCopy = mContextMenu->addAction(QString(), this, SLOT(slotActionCopyTriggered()));
    mActionClone = mContextMenu->addAction(QString(), this, SLOT(slotActionCloneTriggered()));
    mActionPaste = mContextMenu->addAction(QString(), this, SLOT(slotActionPasteTriggered()));
    mActionInsert = mContextMenu->addAction(QString(), this, SLOT(slotActionInsertTriggered()));
    mContextMenu->addSeparator();
    mActionRemove = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTriggered()));
    mContextMenu->addSeparator();
    mActionShowGrid = mContextMenu->addAction(QString(), this, SLOT(slotActionShowGridTriggered(bool)));
    mActionShowGrid->setCheckable(true);
    mContextMenu->addSeparator();
    mActionSetStandardFrame = mContextMenu->addAction(QString(), this, SLOT(slotActionSetStandardFrameTriggered()));

    retranslateUi();
}

TFrameListView::~TFrameListView()
{

}

QList<int> TFrameListView::getSelectedIndexes()
{
    QList<int> selectedRows;
    for(QModelIndex index : selectionModel()->selectedIndexes())
    {
        int i = getIndex(index);
        if(i != -1)
            selectedRows.append(i);
    }
    qSort(selectedRows);
    return selectedRows;
}

int TFrameListView::getCurrentIndex()
{
    return getIndex(currentIndex());
}

void TFrameListView::selectIndex(int index)
{
    QTableView::selectColumn(index);

    emit indexSelected(index);
}

void TFrameListView::selectItems(QList<int> posList, bool locate)
{
    QItemSelectionModel *selModel = selectionModel();
    if(!selModel)
        return;

    selModel->clearSelection();
    QAbstractItemModel *m = model();
    int indexSize = posList.size();
    if(!m || !selModel || indexSize<=0)
        return;

    int colCount = m->columnCount();
    int row = -1;
    int col = -1;
    for(int i : posList) {
        row = i/colCount;
        col = i%colCount;
        selModel->select(m->index(row, col), QItemSelectionModel::Select);
    }

    if(locate)
    {
        scrollTo(m->index(row, col), QAbstractItemView::PositionAtCenter);
    }
}

void TFrameListView::slotActionRemoveTriggered()
{
    emit requestRemoveFrames(getSelectedIndexes());
}

void TFrameListView::slotActionInsertTriggered()
{
    int i = currentIndex().column();
    emit requestInsertFrames(i);
}

void TFrameListView::slotActionShowGridTriggered(bool checked)
{
    setShowGrid(checked);
}

void TFrameListView::slotActionSetStandardFrameTriggered()
{
    emit requestSetStandardFrame(currentIndex().column());
}

void TFrameListView::slotActionCloneTriggered()
{
    emit requestCloneFrames(getSelectedIndexes());
}

void TFrameListView::slotActionCopyTriggered()
{
    emit requestCopyFrames(getSelectedIndexes());
}

void TFrameListView::slotActionPasteTriggered()
{
    int pos = getCurrentIndex();
    emit requestPasteFrames(pos);
}

QString TFrameListView::getCheckMimeType() const
{
    return mCheckMimeType;
}

void TFrameListView::setCheckMimeType(const QString &checkMimeType)
{
    mCheckMimeType = checkMimeType;
}

int TFrameListView::getIndex(const QModelIndex &index)
{
    QAbstractItemModel *m = model();
    if(!m)
        return -1;

    int columnSize = m->columnCount();
    return columnSize*index.row()+index.column();
}

void TFrameListView::retranslateUi()
{
    mActionInsert->setText(tr("Insert"));
    mActionRemove->setText(tr("Remove"));
    mActionShowGrid->setText(tr("Show grid"));
    mActionSetStandardFrame->setText(tr("Set as standard frame"));
    mActionClone->setText(tr("Clone"));
    mActionCopy->setText(tr("Copy"));
    mActionPaste->setText(tr("Paste"));
}

void TFrameListView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    emit resized();
}

void TFrameListView::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->source()==this) {
        QModelIndex i = indexAt(event->pos());
        QRect rt;
        if(i.isValid()) {
            rt = visualRect(i);
            rt.setLeft(rt.left()-1);
        } else {
            QAbstractItemModel *m = model();
            i = m->index(m->rowCount()-1, m->columnCount()-1);
            rt = visualRect(i);
            rt.setLeft(rt.right()+1);
        }
        rt.setTop(0);
        rt.setWidth(1);
        if(rt != mHighlightRect)
        {
            mHighlightRect = rt;
            viewport()->update();
        }
        event->accept();
    } else {
        event->ignore();
    }
}

void TFrameListView::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = mHighlightRect;
    mHighlightRect = QRect();
    viewport()->update(updateRect);
    event->accept();
}

void TFrameListView::dropEvent(QDropEvent *event)
{
    QAbstractItemModel *m = model();
    if(m)
    {
        QModelIndex mIndex = indexAt(event->pos());
        int itemCount = m->columnCount();
        int insertPos = mIndex.column() + mIndex.row()*itemCount;
        if(insertPos<0 || insertPos>itemCount)
            insertPos = itemCount;

        if(event->source()==this)
        {
            QList<int> selected = getSelectedIndexes();
            int selectedSize = selected.size();
            if(selectedSize > 0)
            {
                int firstPos = selected[0];
                int lastPos = selected[selectedSize-1];
                int diff = lastPos - firstPos + 1;
                if(diff<=selectedSize && (selected.contains(insertPos) || insertPos==lastPos+1))
                {
                    // In this case, cancel emit signal
                } else {
                    emit requestMoveFrames(selected, insertPos);
                    QList<int> newIndexes;
                    int n = 0;
                    for(int i : selected)
                    {
                        if(i < insertPos)
                            n++;
                    }
                    insertPos -= n;
                    for(int i=0;i<selectedSize;i++)
                        newIndexes.append(insertPos+i);
                    selectItems(newIndexes);
                }
            }
            event->accept();
        } else {
            event->ignore();
        }
    }
    mHighlightRect = QRect();
    viewport()->update();
}

void TFrameListView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source()==this) {
        event->accept();
    } else {
        event->ignore();
    }
}

void TFrameListView::paintEvent(QPaintEvent *event)
{
    QTableView::paintEvent(event);

    QPainter painter(viewport());
    if (mHighlightRect.isValid()) {
        painter.setBrush(mHighlightColor);
        painter.drawRect(mHighlightRect);
    }

    painter.end();
}

void TFrameListView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    emit indexPressed(getIndex(index));
    QTableView::mousePressEvent(event);
}

void TFrameListView::contextMenuEvent(QContextMenuEvent *event)
{
    int selectionSize = getSelectedIndexes().size();
    bool hasSelection = selectionSize>0;
    bool hasOnlyOneSelection = selectionSize==1;
    mActionRemove->setEnabled(hasSelection);
    mActionSetStandardFrame->setEnabled(hasOnlyOneSelection);
    mActionPaste->setEnabled(qApp->clipboard()->mimeData()->hasFormat(mCheckMimeType));
    mContextMenu->popup(event->globalPos());
}

bool TFrameListView::event(QEvent *event)
{
    if(event->type()==QEvent::LanguageChange)
    {
        retranslateUi();
    }
    return QTableView::event(event);
}


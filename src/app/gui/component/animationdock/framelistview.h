#ifndef FRAMELISTVIEW_H
#define FRAMELISTVIEW_H

#include <QMenu>
#include <QList>
#include <QAction>
#include <QTableView>

class TFrameListView : public QTableView
{
    Q_OBJECT

public:
    TFrameListView(QWidget *parent = 0);
    ~TFrameListView();

    QList<int> getSelectedIndexes();
    int getCurrentIndex();
    void selectIndex(int index);
    void selectItems(QList<int> posList, bool locate = true);
    QString getCheckMimeType() const;
    void setCheckMimeType(const QString &checkMimeType);

signals:
    void indexPressed(int index);
    void indexSelected(int index);
    void resized();
    void requestMoveFrames(QList<int> indexes, int pos);
    void requestInsertFrames(int pos);
    void requestRemoveFrames(const QList<int> &indexList);
    void requestSetStandardFrame(int index);
    void requestCloneFrames(const QList<int> &indexList);
    void requestCopyFrames(const QList<int> &indexList);
    void requestPasteFrames(int pos);

private slots:
    void slotActionRemoveTriggered();
    void slotActionInsertTriggered();
    void slotActionShowGridTriggered(bool checked);
    void slotActionSetStandardFrameTriggered();
    void slotActionCloneTriggered();
    void slotActionCopyTriggered();
    void slotActionPasteTriggered();

private:
    QString mCheckMimeType;
    QMenu *mContextMenu;
    QAction *mActionRemove;
    QAction *mActionInsert;
    QAction *mActionClone;
    QAction *mActionCopy;
    QAction *mActionPaste;
    QAction *mActionShowGrid;
    QAction *mActionSetStandardFrame;
    QColor mHighlightColor;
    QRect mHighlightRect;

    inline int getIndex(const QModelIndex &index);

    void retranslateUi();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    // QObject interface
public:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // FRAMELISTVIEW_H

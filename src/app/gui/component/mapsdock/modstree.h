#ifndef TMODSTREE_H
#define TMODSTREE_H

#include <QEvent>
#include <QTreeView>

class TModsTree : public QTreeView
{
    Q_OBJECT

public:
    explicit TModsTree(QWidget *parent = Q_NULLPTR);
    ~TModsTree();

private:
    void retranslateUi();

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // TMODSTREE_H

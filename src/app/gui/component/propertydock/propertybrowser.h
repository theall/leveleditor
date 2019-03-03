#ifndef PROPERTYBROWSER_H
#define PROPERTYBROWSER_H

#include <QStackedWidget>

#include <qtpropertybrowser/QtTreePropertyBrowser>
#include <qtpropertybrowser/QtButtonPropertyBrowser>
#include <qtpropertybrowser/QtGroupPropertyManager>

#include "variantpropertymanager.h"
#include "varianteditorfactory.h"

class TPropertyBrowser : public QWidget
{
    Q_OBJECT

public:
    enum ViewMode
    {
        Tree,
        Button
    };

    explicit TPropertyBrowser(QWidget *parent = nullptr);
    ~TPropertyBrowser();

    void setPropertyManager(QtVariantPropertyManager *variantManager);
    void setFilter(const QString &filter);
    void collapseAll();
    void setViewMode(ViewMode viewMode);

    TVariantEditorFactory *editorFactory() const;
    void setEditorFactory(TVariantEditorFactory *editorFactory);

    void setItemVisible(QtBrowserItem *item, bool visible);
    bool isExpanded(QtBrowserItem *item) const;
    void setExpanded(QtBrowserItem *item, bool expanded);

    bool getSorting() const;
    void setSorting(bool sorting);

    QtBrowserItem *currentItem() const;
    void setCurrentItem(QtBrowserItem *item);
    QtBrowserItem *addProperty(QtProperty *property);
    QtBrowserItem *insertProperty(QtProperty *property, QtProperty *afterProperty);
    void removeProperty(QtProperty *property);
    QList<QtProperty *> properties() const;
    QList<QtBrowserItem *> items(QtProperty *property) const;
    QtBrowserItem *topLevelItem(QtProperty *property) const;
    QList<QtBrowserItem *> topLevelItems() const;
    void clear();

signals:
    void currentItemChanged(QtBrowserItem *);

protected:
    bool event(QEvent *event) override;

private slots:
    void slotPropertyInserted(QtProperty *property, QtProperty *parent, QtProperty *after);
    void slotPropertyRemoved(QtProperty *property, QtProperty *parent);

private:
    bool mSorting;
    int mTreeIndex;
    int mButtonIndex;
    QStackedWidget *mStackedWidget;
    QtTreePropertyBrowser *mTreeBrowser;
    QtButtonPropertyBrowser *mButtonBrowser;
    QtAbstractPropertyBrowser *mCurrentBrowser;
    TVariantEditorFactory *mEditorFactory;
    QMap<QString, bool> mExpansionState;
    QtVariantPropertyManager *mCurrentPropertyManager;
    QMap<QString, QtProperty*> mNameToProperty;
    QMap<QtProperty*, QString> mPropertyToGroup;
    QMap<QString, QtVariantProperty*> mNameToGroup;
    QList<QtProperty *> mPropertyGroups;

    void retranslateUi();
    void updatePropertyColor(const QString &name);
    QList<QtBrowserItem *> getBrowserItemList(QtBrowserItem *browserItem);
    void storeExpansionState();
    void storePropertiesExpansionState(const QList<QtBrowserItem *> &items);
    void applyExpansionState();
    void applyPropertiesExpansionState(const QList<QtBrowserItem *> &items);
    void fillView();
};

#endif // PROPERTYBROWSER_H

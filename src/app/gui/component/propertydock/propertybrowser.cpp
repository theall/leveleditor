#include "propertybrowser.h"

#include <QEvent>
#include <QScrollArea>
#include <QVBoxLayout>

TPropertyBrowser::TPropertyBrowser(QWidget *parent) :
    QWidget(parent)
  , mSorting(false)
  , mTreeIndex(-1)
  , mButtonIndex(-1)
  , mStackedWidget(new QStackedWidget)//提供了一个小部件堆栈，其中一次只能看到一个小部件
  , mTreeBrowser(nullptr)
  , mButtonBrowser(nullptr)
  , mCurrentBrowser(nullptr)
  , mEditorFactory(new TVariantEditorFactory(this))
  , mCurrentPropertyManager(nullptr)
{
    // Views
    QScrollArea *buttonScroll = new QScrollArea(mStackedWidget);
    mButtonBrowser = new QtButtonPropertyBrowser(buttonScroll);
    buttonScroll->setWidgetResizable(true);
    buttonScroll->setWidget(mButtonBrowser);
    mButtonIndex = mStackedWidget->addWidget(buttonScroll);
    connect(mButtonBrowser, SIGNAL(currentItemChanged(QtBrowserItem*)), this, SIGNAL(currentItemChanged(QtBrowserItem*)));

    mTreeBrowser = new QtTreePropertyBrowser(mStackedWidget);
    mTreeBrowser->setRootIsDecorated(true);
    mTreeBrowser->setPropertiesWithoutValueMarked(true);
    mTreeBrowser->setResizeMode(QtTreePropertyBrowser::Interactive);
    mTreeIndex = mStackedWidget->addWidget(mTreeBrowser);
    connect(mTreeBrowser, SIGNAL(currentItemChanged(QtBrowserItem*)), this, SIGNAL(currentItemChanged(QtBrowserItem*)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mStackedWidget);
    layout->setMargin(0);
    layout->setSpacing(0);

    setViewMode(Tree);
}

TPropertyBrowser::~TPropertyBrowser()
{

}

void TPropertyBrowser::setPropertyManager(QtVariantPropertyManager *variantManager)
{
    if(mCurrentPropertyManager)
        mCurrentPropertyManager->disconnect(this);
    mTreeBrowser->setFactoryForManager(variantManager, mEditorFactory);
    mButtonBrowser->setFactoryForManager(variantManager, mEditorFactory);

    mCurrentPropertyManager = variantManager;
    if(mCurrentPropertyManager)
    {

    }
}

void TPropertyBrowser::setFilter(const QString &filter)
{
    if(!mCurrentBrowser)
        return;

    const QList<QtBrowserItem *> items = mCurrentBrowser->topLevelItems();
    const bool matchAll = filter.isEmpty();
    QListIterator<QtBrowserItem *> itProperty(items);
    while (itProperty.hasNext()) {
        QtBrowserItem *browserItem = itProperty.next();
        bool showProperty = matchAll || browserItem->property()->propertyName().contains(filter, Qt::CaseInsensitive);
        QList<QtBrowserItem *> browserItemList = getBrowserItemList(browserItem);
        for(QtBrowserItem *subBrowerItem : browserItemList)
        {
            bool showSubProperty = matchAll || subBrowerItem->property()->propertyName().contains(filter, Qt::CaseInsensitive);
            setItemVisible(subBrowerItem, showSubProperty);
            showProperty |= showSubProperty;
        }

        setItemVisible(browserItem, showProperty);
    }
}

void TPropertyBrowser::collapseAll()
{
    if(!mCurrentBrowser)
        return;

    QList<QtBrowserItem *> items = mCurrentBrowser->topLevelItems();
    QListIterator<QtBrowserItem *> itGroup(items);
    while (itGroup.hasNext()) {
        setExpanded(itGroup.next(), false);
    }
}

void TPropertyBrowser::applyPropertiesExpansionState(const QList<QtBrowserItem *> &items)
{
    const QChar bar = QLatin1Char('|');
    QListIterator<QtBrowserItem *> itProperty(items);
    while (itProperty.hasNext()) {
        const QMap<QString, bool>::const_iterator excend = mExpansionState.constEnd();
        QtBrowserItem *propertyItem = itProperty.next();
        QtProperty *property = propertyItem->property();
        const QString propertyName = property->propertyName();
        const QMap<QtProperty *, QString>::const_iterator itGroup = mPropertyToGroup.constFind(property);
        if(itGroup != mPropertyToGroup.constEnd()) {
            QString key = itGroup.value();
            key += bar;
            key += propertyName;
            const QMap<QString, bool>::const_iterator pit = mExpansionState.constFind(key);
            if(pit != excend)
                setExpanded(propertyItem, pit.value());
            else
                setExpanded(propertyItem, false);
        }
    }
}

void TPropertyBrowser::applyExpansionState()
{
    const QList<QtBrowserItem *> items = mCurrentBrowser->topLevelItems();
    if(mSorting) {
        applyPropertiesExpansionState(items);
    } else {
        QListIterator<QtBrowserItem *> itTopLevel(items);
        const QMap<QString, bool>::const_iterator excend = mExpansionState.constEnd();
        while (itTopLevel.hasNext()) {
            QtBrowserItem *item = itTopLevel.next();
            const QString groupName = item->property()->propertyName();
            const QMap<QString, bool>::const_iterator git = mExpansionState.constFind(groupName);
            if(git != excend)
                setExpanded(item, git.value());
            else
                setExpanded(item, true);
            // properties stuff here
            applyPropertiesExpansionState(item->children());
        }
    }
}

void TPropertyBrowser::setViewMode(TPropertyBrowser::ViewMode viewMode)
{
    int idx = 0;
    if(viewMode == Tree) {
        mCurrentBrowser = mTreeBrowser;
        idx = mTreeIndex;
    } else if(viewMode == Button) {
        mCurrentBrowser = mButtonBrowser;
        idx = mButtonIndex;
    }

    storeExpansionState();
    collapseAll();
    mCurrentBrowser->clear();
    fillView();
    mStackedWidget->setCurrentIndex(idx);
    applyExpansionState();
}

bool TPropertyBrowser::event(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
        retranslateUi();

    return QWidget::event(event);
}

void TPropertyBrowser::slotPropertyInserted(QtProperty *property, QtProperty *parent, QtProperty *after)
{
    Q_UNUSED(parent);
    Q_UNUSED(after);
    mNameToProperty[property->propertyName()] = property;
}

void TPropertyBrowser::slotPropertyRemoved(QtProperty *property, QtProperty *parent)
{
    Q_UNUSED(parent);
    mNameToProperty.remove(property->propertyName());
}

bool TPropertyBrowser::getSorting() const
{
    return mSorting;
}

void TPropertyBrowser::setSorting(bool sorting)
{
    if(sorting == mSorting)
        return;

    storeExpansionState();
    mSorting = sorting;
    collapseAll();
    mCurrentBrowser->clear();
    mTreeBrowser->setRootIsDecorated(sorting);
    fillView();
    applyExpansionState();
}

QtBrowserItem *TPropertyBrowser::currentItem() const
{
    return mCurrentBrowser?mCurrentBrowser->currentItem():nullptr;
}

void TPropertyBrowser::setCurrentItem(QtBrowserItem *item)
{
    if(mCurrentBrowser)
        mCurrentBrowser->setCurrentItem(item);
}

QtBrowserItem *TPropertyBrowser::addProperty(QtProperty *property)
{
    if(!mCurrentBrowser)
        return nullptr;

    return mCurrentBrowser->addProperty(property);
}

QList<QtProperty *> TPropertyBrowser::properties() const
{
    if(mCurrentBrowser)
        return mCurrentBrowser->properties();

    return QList<QtProperty *>();
}

QList<QtBrowserItem *> TPropertyBrowser::items(QtProperty *property) const
{
    if(!mCurrentBrowser)
        return QList<QtBrowserItem *>();

    return mCurrentBrowser->items(property);
}

QtBrowserItem *TPropertyBrowser::topLevelItem(QtProperty *property) const
{
    if(mCurrentBrowser)
        return mCurrentBrowser->topLevelItem(property);

    return nullptr;
}

QList<QtBrowserItem *> TPropertyBrowser::topLevelItems() const
{
    if(mCurrentBrowser)
        return mCurrentBrowser->topLevelItems();

    return QList<QtBrowserItem *>();
}

void TPropertyBrowser::clear()
{
    if(mCurrentBrowser)
        mCurrentBrowser->clear();
}

void TPropertyBrowser::fillView()
{
    if(mSorting) {
        QMapIterator<QString, QtProperty *> itProperty(mNameToProperty);
        while (itProperty.hasNext()) {
            QtProperty *property = itProperty.next().value();
            mCurrentBrowser->addProperty(property);
        }
    } else {
        QListIterator<QtProperty *> itGroup(mPropertyGroups);
        while (itGroup.hasNext()) {
            QtProperty *group = itGroup.next();
            mCurrentBrowser->addProperty(group);
            group->setModified(mCurrentBrowser == mTreeBrowser);
        }
    }
}

TVariantEditorFactory *TPropertyBrowser::editorFactory() const
{
    return mEditorFactory;
}

void TPropertyBrowser::setEditorFactory(TVariantEditorFactory *editorFactory)
{
    mEditorFactory = editorFactory;
}

void TPropertyBrowser::retranslateUi()
{

}

QList<QtBrowserItem *> TPropertyBrowser::getBrowserItemList(QtBrowserItem *browserItem)
{
    QList<QtBrowserItem *> browserItemList;
    if(browserItem)
    {
        browserItemList.append(browserItem);
        for(QtBrowserItem *subBrowserItem : browserItem->children())
        {
            browserItemList += getBrowserItemList(subBrowserItem);
        }
    }
    return browserItemList;
}

void TPropertyBrowser::setExpanded(QtBrowserItem *item, bool expanded)
{
    if(mButtonBrowser == mCurrentBrowser)
        mButtonBrowser->setExpanded(item, expanded);
    else if(mTreeBrowser == mCurrentBrowser)
        mTreeBrowser->setExpanded(item, expanded);
}

bool TPropertyBrowser::isExpanded(QtBrowserItem *item) const
{
    if(mButtonBrowser == mCurrentBrowser)
        return mButtonBrowser->isExpanded(item);
    else if(mTreeBrowser == mCurrentBrowser)
        return mTreeBrowser->isExpanded(item);
    return false;
}

void TPropertyBrowser::storePropertiesExpansionState(const QList<QtBrowserItem *> &items)
{
    const QChar bar = QLatin1Char('|');
    QListIterator<QtBrowserItem *> itProperty(items);
    while (itProperty.hasNext()) {
        QtBrowserItem *propertyItem = itProperty.next();
        if(!propertyItem->children().empty()) {
            QtProperty *property = propertyItem->property();
            const QString propertyName = property->propertyName();
            const QMap<QtProperty *, QString>::const_iterator itGroup = mPropertyToGroup.constFind(property);
            if(itGroup != mPropertyToGroup.constEnd()) {
                QString key = itGroup.value();
                key += bar;
                key += propertyName;
                mExpansionState[key] = isExpanded(propertyItem);
            }
        }
    }
}

void TPropertyBrowser::storeExpansionState()
{
    const QList<QtBrowserItem *> items = mCurrentBrowser->topLevelItems();
    if(mSorting) {
        storePropertiesExpansionState(items);
    } else {
        QListIterator<QtBrowserItem *> itGroup(items);
        while (itGroup.hasNext()) {
            QtBrowserItem *item = itGroup.next();
            const QString groupName = item->property()->propertyName();
            QList<QtBrowserItem *> propertyItems = item->children();
            if(!propertyItems.empty())
                mExpansionState[groupName] = isExpanded(item);

            // properties stuff here
            storePropertiesExpansionState(propertyItems);
        }
    }
}

void TPropertyBrowser::setItemVisible(QtBrowserItem *item, bool visible)
{
    if(mCurrentBrowser == mTreeBrowser) {
        mTreeBrowser->setItemVisible(item, visible);
    }
}

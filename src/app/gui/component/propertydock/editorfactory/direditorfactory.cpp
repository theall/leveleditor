#include "direditorfactory.h"
#include "../propertymanager/dirpropertymanager.h"
#include "../qtpropertybrowser/include/QtEnumEditorFactory"
#include "../qtpropertybrowser/include/QtEnumPropertyManager"

#include <QStyle>
#include <QPainter>
#include <QComboBox>
#include <QApplication>
#include <QStyleOptionButton>

static QIcon drawArrow(bool left)
{
    QStyleOptionButton opt;
    opt.state |= left ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    const QStyle *style = QApplication::style();
    // Figure out size of an indicator and make sure it is not scaled down in a list view item
    // by making the pixmap as big as a list view icon and centering the indicator in it.
    // (if it is smaller, it can't be helped)
    const int indicatorWidth = style->pixelMetric(QStyle::PM_IndicatorWidth, &opt);
    const int indicatorHeight = style->pixelMetric(QStyle::PM_IndicatorHeight, &opt);
    const int listViewIconSize = indicatorWidth;
    const int pixmapWidth = indicatorWidth;
    const int pixmapHeight = qMax(indicatorHeight, listViewIconSize);

    opt.rect = QRect(0, 0, indicatorWidth, indicatorHeight);
    QPixmap pixmap = QPixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    {
        // Center?
        const int xoff = (pixmapWidth  > indicatorWidth)  ? (pixmapWidth  - indicatorWidth)  / 2 : 0;
        const int yoff = (pixmapHeight > indicatorHeight) ? (pixmapHeight - indicatorHeight) / 2 : 0;
        QPainter painter(&pixmap);
        painter.translate(xoff, yoff);
        style->drawPrimitive(QStyle::PE_IndicatorArrowLeft, &opt, &painter);
    }
    return QIcon(pixmap);
}

class TDirEditorFactoryPrivate
{
    TDirEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(TDirEditorFactory)

public:
    TDirEditorFactoryPrivate();

    void slotSetValue(int value);
    void slotPropertyChanged(QtProperty *property, int value);
    void slotEnumChanged(QtProperty *property, int value);
    void slotEditorDestroyed(QObject *object);

    QMap<int, QIcon> getIconList() const;

    QtEnumEditorFactory *m_enumEditorFactory;
    QtEnumPropertyManager *m_enumPropertyManager;

    QMap<QtProperty *, QtProperty *> m_propertyToEnum;
    QMap<QtProperty *, QtProperty *> m_enumToProperty;
    QMap<QtProperty *, QList<QWidget *> > m_enumToEditors;
    QMap<QWidget *, QtProperty *> m_editorToEnum;
    bool m_updatingEnum;
    const QIcon m_arrow_left;
    const QIcon m_arrow_right;
};

TDirEditorFactoryPrivate::TDirEditorFactoryPrivate() :
    m_updatingEnum(false)
  , m_arrow_left(drawArrow(true))
  , m_arrow_right(drawArrow(false))
{

}

void TDirEditorFactoryPrivate::slotSetValue(int value)
{
    QWidget *editor = qobject_cast<QWidget*>(q_ptr->sender());
    QtProperty *property = m_enumToProperty[m_editorToEnum[editor]];
    TDirPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    manager->setIndexValue(property, value);
}

void TDirEditorFactoryPrivate::slotPropertyChanged(QtProperty *property, int value)
{
    // update enum property
    QtProperty *enumProp = m_propertyToEnum.value(property);
    if (!enumProp)
        return;

    m_updatingEnum = true;
    m_enumPropertyManager->setValue(enumProp, value);
    m_updatingEnum = false;
}

void TDirEditorFactoryPrivate::slotEnumChanged(QtProperty *property, int value)
{
    if (m_updatingEnum)
        return;
    // update cursor property
    QtProperty *prop = m_enumToProperty.value(property);
    if (!prop)
        return;
    TDirPropertyManager *dirManager = q_ptr->propertyManager(prop);
    if (!dirManager)
        return;

    dirManager->setIndexValue(prop,value );
}

void TDirEditorFactoryPrivate::slotEditorDestroyed(QObject *object)
{
    // remove from m_editorToEnum map;
    // remove from m_enumToEditors map;
    // if m_enumToEditors doesn't contains more editors delete enum property;
    const  QMap<QWidget *, QtProperty *>::ConstIterator ecend = m_editorToEnum.constEnd();
    for (QMap<QWidget *, QtProperty *>::ConstIterator itEditor = m_editorToEnum.constBegin(); itEditor != ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QWidget *editor = itEditor.key();
            QtProperty *enumProp = itEditor.value();
            m_editorToEnum.remove(editor);
            m_enumToEditors[enumProp].removeAll(editor);
            if (m_enumToEditors[enumProp].isEmpty()) {
                m_enumToEditors.remove(enumProp);
                QtProperty *property = m_enumToProperty.value(enumProp);
                m_enumToProperty.remove(enumProp);
                m_propertyToEnum.remove(property);
                delete enumProp;
            }
            return;
        }
    }
}

QMap<int, QIcon> TDirEditorFactoryPrivate::getIconList() const
{
    QMap<int, QIcon> iconMap;
    iconMap.insert(0, m_arrow_left);
    iconMap.insert(1, m_arrow_right);
    return iconMap;
}

/*!
    \class TDirEditorFactory

    \brief The TDirEditorFactory class provides QComboBox widgets for
    properties created by TDirPropertyManager objects.

    \sa QtAbstractEditorFactory, TDirPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
TDirEditorFactory::TDirEditorFactory(QObject *parent)
    : QtAbstractEditorFactory<TDirPropertyManager>(parent)
{
    d_ptr = new TDirEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_enumEditorFactory = new QtEnumEditorFactory(this);
    d_ptr->m_enumPropertyManager = new QtEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotEnumChanged(QtProperty *, int)));
    d_ptr->m_enumEditorFactory->addPropertyManager(d_ptr->m_enumPropertyManager);
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
TDirEditorFactory::~TDirEditorFactory()
{
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void TDirEditorFactory::connectPropertyManager(TDirPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *TDirEditorFactory::createEditor(TDirPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QtProperty *enumProp = 0;
    if (d_ptr->m_propertyToEnum.contains(property)) {
        enumProp = d_ptr->m_propertyToEnum[property];
    } else {
        enumProp = d_ptr->m_enumPropertyManager->addProperty(property->propertyName());
        d_ptr->m_enumPropertyManager->setEnumNames(enumProp, manager->getEnumNames());
        //d_ptr->m_enumPropertyManager->setEnumIcons(enumProp, d_ptr->getIconList());
        d_ptr->m_enumPropertyManager->setValue(enumProp, manager->valueIndex(property));
        d_ptr->m_propertyToEnum[property] = enumProp;
        d_ptr->m_enumToProperty[enumProp] = property;
    }
    QtAbstractEditorFactoryBase *af = d_ptr->m_enumEditorFactory;
    QWidget *editor = af->createEditor(enumProp, parent);
    d_ptr->m_enumToEditors[enumProp].append(editor);
    d_ptr->m_editorToEnum[editor] = enumProp;

    connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void TDirEditorFactory::disconnectPropertyManager(TDirPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
}

#include "moc_direditorfactory.cpp"

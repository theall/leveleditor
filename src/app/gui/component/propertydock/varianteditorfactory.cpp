#include "varianteditorfactory.h"
#include "variantpropertymanager.h"
#include "editorfactory/direditorfactory.h"
#include "propertymanager/dirpropertymanager.h"

class TVariantEditorFactoryPrivate
{
    TVariantEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(TVariantEditorFactory)

public:
    TDirEditorFactory *m_dirFactory;

    QMap<QtAbstractEditorFactoryBase *, int> m_factoryToType;
    QMap<int, QtAbstractEditorFactoryBase *> m_typeToFactory;
};

TVariantEditorFactory::TVariantEditorFactory(QObject *parent) :
    QtVariantEditorFactory(parent)
{
    d_ptr = new TVariantEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_dirFactory = new TDirEditorFactory(this);
    const int dirTypeId = TVariantPropertyManager::dirTypeId();
    registerFactory(dirTypeId, d_ptr->m_dirFactory);
}

TVariantEditorFactory::~TVariantEditorFactory()
{
    delete d_ptr;
}

void TVariantEditorFactory::connectPropertyManager(QtVariantPropertyManager *manager)
{
    QtVariantEditorFactory::connectPropertyManager(manager);

    QList<TDirPropertyManager *> dirPropertyManagers = manager->findChildren<TDirPropertyManager *>();
    QListIterator<TDirPropertyManager *> itDir(dirPropertyManagers);
    while (itDir.hasNext())
        d_ptr->m_dirFactory->addPropertyManager(itDir.next());
}

QWidget *TVariantEditorFactory::createEditor(QtVariantPropertyManager *manager,
                                            QtProperty *property,
                                            QWidget *parent)
{
    return QtVariantEditorFactory::createEditor(manager, property, parent);
}

void TVariantEditorFactory::disconnectPropertyManager(QtVariantPropertyManager *manager)
{
    QtVariantEditorFactory::disconnectPropertyManager(manager);

    QList<TDirPropertyManager *> intPropertyManagers = manager->findChildren<TDirPropertyManager *>();
    QListIterator<TDirPropertyManager *> itDir(intPropertyManagers);
    while (itDir.hasNext())
        d_ptr->m_dirFactory->removePropertyManager(itDir.next());
}

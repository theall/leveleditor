#ifndef TDIREDITORFACTORY_H
#define TDIREDITORFACTORY_H

#include "../qtpropertybrowser/include/QtProperty"

class TDirEditorFactoryPrivate;
class TDirPropertyManager;
class TDirEditorFactory : public QtAbstractEditorFactory<TDirPropertyManager>
{
    Q_OBJECT

public:
    TDirEditorFactory(QObject *parent = 0);
    ~TDirEditorFactory();

protected:
    void connectPropertyManager(TDirPropertyManager *manager);
    QWidget *createEditor(TDirPropertyManager *manager, QtProperty *property, QWidget *parent);
    void disconnectPropertyManager(TDirPropertyManager *manager);

private:
    TDirEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(TDirEditorFactory)
    Q_DISABLE_COPY(TDirEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
};

#endif // TDIREDITORFACTORY_H

#ifndef TDIRPROPERTYMANAGER_H
#define TDIRPROPERTYMANAGER_H

#include "../qtpropertybrowser/include/QtProperty"

class TDirPropertyManagerPrivate;
class TDirPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT

public:
    TDirPropertyManager(QObject *parent = 0);
    ~TDirPropertyManager();

    int value(const QtProperty *property) const;
    int valueIndex(const QtProperty *property) const;
    void setIndexValue(QtProperty *property, int val);

    QStringList getEnumNames() const;

public Q_SLOTS:
    void setValue(QtProperty *property, int val);

Q_SIGNALS:
    void valueChanged(QtProperty *property, int val);

protected:
    QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);

private:
    QStringList mDirNames;
    QString valueString(int value) const;
    TDirPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(TDirPropertyManager)
    Q_DISABLE_COPY(TDirPropertyManager)
};

#endif // TDIRPROPERTYMANAGER_H

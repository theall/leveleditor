#ifndef TBOX_H
#define TBOX_H

#include <QList>

#include "rectobject.h"

class TBox : public TRectObject
{
    Q_OBJECT

public:
    explicit TBox(QObject *parent = nullptr);
    TBox(const QRect &rect, QObject *parent = Q_NULLPTR);

    QList<QPoint> pointList() const;

private:
    int mCurrentPoint;
    int mFinalPoint;
    QList<QPoint> mPointList;
    
	void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};

typedef QList<TBox*> TBoxList;

#endif // TBOX_H

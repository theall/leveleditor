#include "areaplat.h"
#include "plat.h"
#include "../../base/tr.h"

static const QString P_MOVE_BY = T("Move With Plat");

TAreaPlat::TAreaPlat(TObject::Type type, QObject *parent) :
    TRectObject(type, parent)
{
    initPropertySheet();
}

TAreaPlat::TAreaPlat(const QRect &rect, TObject::Type type, QObject *parent) :
    TRectObject(rect, type, parent)
{

}

int TAreaPlat::platIndex() const
{
    return mPlatIndex;
}

TPlat *TAreaPlat::plat() const
{
    return mPlat;
}

void TAreaPlat::setPlat(TPlat *plat, int index)
{
    if(mPlat == plat)
        return;

    TPlat *oldPlat = mPlat;
    int oldIndex = mPlatIndex;
    mPlat = plat;
    mPlatIndex = index;
    emit bindPlatChanged(plat, index, oldPlat, oldIndex);
}

bool TAreaPlat::hasPlat() const
{
    return mPlat != nullptr;
}

void TAreaPlat::initPropertySheet()
{
    mPropertySheet->addProperty(PT_STRING, P_MOVE_BY, PID_AREA_MOVE_BY)->setReadOnly();
}

void TAreaPlat::setPlatDisplayText(int index)
{
    QString text = tr("Plat %1").arg(++index);
    mPropertySheet->setValue(PID_AREA_MOVE_BY, text);
}

void TAreaPlat::saveToStream(QDataStream &stream) const
{
    stream << mPlatIndex + 1;
}

void TAreaPlat::readFromStream(QDataStream &stream)
{
    stream >> mPlatIndex;
    mPlatIndex--;

}

QByteArray TAreaPlat::toByteArray(TObject *object) const
{

}

void TAreaPlat::loadFromByteArray(const QByteArray &byteArray)
{

}

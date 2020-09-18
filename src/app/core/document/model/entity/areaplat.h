#ifndef TAREAPLAT_H
#define TAREAPLAT_H

#include "rectobject.h"

class TPlat;
class TAreaPlat : public TRectObject
{
    Q_OBJECT

public:
    TAreaPlat(TObject::Type type, QObject *parent = Q_NULLPTR);
    TAreaPlat(const QRect &rect, TObject::Type type, QObject *parent = Q_NULLPTR);

    /**
     * @brief Return plat index that read from stream, it will be processed in readfromstream in scenemodel
     * @return plat index start from zero
     */
    int platIndex() const;

    TPlat *plat() const;
    /**
     * @brief This function will be called while processing the bindings between plat and area after platmodel read over in scene mode
     * @param plat
     * @param index
     */
    void setPlat(TPlat *plat, int index = -1);

    bool hasPlat() const;

signals:
    void bindPlatChanged(TPlat *newPlat, int newIndex, TPlat *oldPlat, int oldIndex);

protected:
    virtual void initPropertySheet() override;

private:
    int mPlatIndex;
    TPlat *mPlat;

    void setPlatDisplayText(int index);

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const override;
    void readFromStream(QDataStream &stream) override;

    // TObject interface
public:
    QByteArray toByteArray(TObject *object) const;
    void loadFromByteArray(const QByteArray &byteArray);
};

#endif // TAREAPLAT_H

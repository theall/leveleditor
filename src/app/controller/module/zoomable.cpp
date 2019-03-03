#include "zoomable.h"

#include <QComboBox>
#include <QLineEdit>
#include <QPinchGesture>
#include <QValidator>

#include <cmath>

static const qreal zoomFactors[] = {
    0.015625,
    0.03125,
    0.0625,
    0.125,
    0.25,
    0.33,
    0.5,
    0.75,
    1.0,
    1.5,
    2.0,
    3.0,
    4.0,
    5.5,
    8.0,
    11.0,
    16.0,
    23.0,
    32.0,
    45.0,
    64.0,
    90.0,
    128.0,
    180.0,
    256.0
};
const int g_zoomFactorCount = sizeof(zoomFactors) / sizeof(zoomFactors[0]);


static QString scaleToString(qreal scale)
{
    return QString(QLatin1String("%1 %")).arg(int(scale * 100));
}


TZoomable::TZoomable(QObject *parent)
    : QObject(parent)
    , mScale(1)
    , mGestureStartScale(0)
    , mComboBox(nullptr)
    , mComboRegExp(QLatin1String("^\\s*(\\d+)\\s*%?\\s*$"))
    , mComboValidator(nullptr)
{
    for (int i = 0; i < g_zoomFactorCount; i++)
        mZoomFactors << zoomFactors[i];
}

void TZoomable::setScale(qreal scale)
{
    if (scale == mScale)
        return;

    mScale = scale;

    syncComboBox();

    emit scaleChanged(mScale);
}

bool TZoomable::canZoomIn() const
{
    return mScale < mZoomFactors.last();
}

bool TZoomable::canZoomOut() const
{
    return mScale > mZoomFactors.first();
}

void TZoomable::handleWheelDelta(int delta)
{
    if (delta <= -120) {
        zoomOut();
    } else if (delta >= 120) {
        zoomIn();
    } else {
        // We're dealing with a finer-resolution mouse. Allow it to have finer
        // control over the zoom level.
        qreal factor = 1 + 0.3 * qAbs(qreal(delta) / 8 / 15);
        if (delta < 0)
            factor = 1 / factor;

        qreal scale = qBound(mZoomFactors.first(),
                             mScale * factor,
                             mZoomFactors.back());

        // Round to at most four digits after the decimal point
        setScale(std::floor(scale * 10000 + 0.5) / 10000);
    }
}

void TZoomable::handlePinchGesture(QPinchGesture *pinch)
{
    if (!(pinch->changeFlags() & QPinchGesture::ScaleFactorChanged))
        return;

    switch (pinch->state()) {
    case Qt::NoGesture:
        break;
    case Qt::GestureStarted:
        mGestureStartScale = mScale;
        // fall through
    case Qt::GestureUpdated: {
        qreal factor = pinch->scaleFactor();
        qreal scale = qBound(mZoomFactors.first(),
                             mGestureStartScale * factor,
                             mZoomFactors.back());
        setScale(std::floor(scale * 10000 + 0.5) / 10000);
        break;
    }
    case Qt::GestureFinished:
    case Qt::GestureCanceled:
        break;
    }
}

void TZoomable::zoomIn()
{
    foreach (qreal scale, mZoomFactors) {
        if (scale > mScale) {
            setScale(scale);
            break;
        }
    }
}

void TZoomable::zoomOut()
{
    for (int i = mZoomFactors.count() - 1; i >= 0; --i) {
        if (mZoomFactors[i] < mScale) {
            setScale(mZoomFactors[i]);
            break;
        }
    }
}

void TZoomable::resetZoom()
{
    setScale(1);
}

void TZoomable::setZoomFactors(const QVector<qreal>& factors)
{
    mZoomFactors = factors;
}

void TZoomable::connectToComboBox(QComboBox *comboBox)
{
    if (mComboBox) {
        mComboBox->disconnect(this);
        if (mComboBox->lineEdit())
            mComboBox->lineEdit()->disconnect(this);
        mComboBox->setValidator(nullptr);
    }

    mComboBox = comboBox;

    if (mComboBox) {
        mComboBox->clear();
        foreach (qreal scale, mZoomFactors)
            mComboBox->addItem(scaleToString(scale), scale);
        syncComboBox();
        connect(mComboBox, SIGNAL(activated(int)),
                this, SLOT(comboActivated(int)));

        mComboBox->setEditable(true);
        mComboBox->setInsertPolicy(QComboBox::NoInsert);
        connect(mComboBox->lineEdit(), SIGNAL(editingFinished()),
                this, SLOT(comboEdited()));

        if (!mComboValidator)
            mComboValidator = new QRegExpValidator(mComboRegExp, this);
        mComboBox->setValidator(mComboValidator);
    }
}

void TZoomable::comboActivated(int index)
{
    setScale(mComboBox->itemData(index).toReal());
}

void TZoomable::comboEdited()
{
    int pos = mComboRegExp.indexIn(mComboBox->currentText());
    Q_ASSERT(pos != -1);
    Q_UNUSED(pos)

    qreal scale = qBound(mZoomFactors.first(),
                         qreal(mComboRegExp.cap(1).toDouble() / 100.f),
                         mZoomFactors.last());

    setScale(scale);
}

void TZoomable::syncComboBox()
{
    if (!mComboBox)
        return;

    int index = mComboBox->findData(mScale);
    // For a custom scale, the current index must be set to -1
    mComboBox->setCurrentIndex(index);
    mComboBox->setEditText(scaleToString(mScale));
}

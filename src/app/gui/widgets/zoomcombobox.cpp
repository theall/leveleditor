#include "zoomcombobox.h"

#include <QComboBox>
#include <QLineEdit>
#include <QPinchGesture>
#include <QValidator>
#include <cmath>

static const qreal g_zoomFactors[] = {
    0.10,
    0.125,
    0.25,
    0.33,
    0.5,
    0.80,
    1.0,
    1.5,
    2.0,
    2.5,
    3.0,
    4.0,
    5.0,
    8.0,
    10.0,
    12.0,
    15.0,
    20.0,
    32.0,
    40.0,
    64.0
};
const int g_zoomFactorCount = sizeof(g_zoomFactors) / sizeof(g_zoomFactors[0]);

static QString scaleToString(qreal scale)
{
    return QString(QLatin1String("%1 %")).arg(int(scale * 100));
}

static qreal boundedScaleValue(qreal scale)
{
    return qBound(g_zoomFactors[0],
                 scale,
                 g_zoomFactors[g_zoomFactorCount-1]);
}

TZoomComboBox::TZoomComboBox(QWidget *parent)
    : QComboBox(parent)
  , mScaleValue(1.0)
  , mGestureStartScale(0)
  , mComboRegExp(QLatin1String("^\\s*(\\d+)\\s*%?\\s*$"))
{
    for (int i = 0; i < g_zoomFactorCount; i++)
        mZoomFactors << g_zoomFactors[i];

    foreach (qreal scale, mZoomFactors)
        addItem(scaleToString(scale), scale);

    //setEditable(true);
    setInsertPolicy(QComboBox::NoInsert);
    setValidator(new QRegExpValidator(mComboRegExp, this));
    setCurrentText(scaleToString(mScaleValue));
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
    //connect(lineEdit(), SIGNAL(editingFinished()), this, SLOT(slotComboEdited()));
}

TZoomComboBox::~TZoomComboBox()
{

}

qreal TZoomComboBox::scaleValue() const
{
    return mScaleValue;
}

void TZoomComboBox::setScaleValue(qreal scale, bool emitSignal)
{
    if (scale == mScaleValue)
        return;

    mScaleValue = scale;

    // For a custom scale, the current index must be set to -1
    int findIndex = findData(scale);
    if(findIndex < 0)
        findIndex = findData(1.0);
    if(findIndex < 0)
        findIndex = 6;
    setCurrentIndex(findIndex);
    setEditText(scaleToString(mScaleValue));

    if(emitSignal)
        emit scaleChanged(mScaleValue);
}

bool TZoomComboBox::canZoomIn() const
{
    return mScaleValue < mZoomFactors.last();
}

bool TZoomComboBox::canZoomOut() const
{
    return mScaleValue > mZoomFactors.first();
}

void TZoomComboBox::handleWheelDelta(int delta)
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

        qreal scale = boundedScaleValue(mScaleValue * factor);

        // Round to at most four digits after the decimal point
        setScaleValue(std::floor(scale * 10000 + 0.5) / 10000);
    }
}

void TZoomComboBox::handlePinchGesture(QPinchGesture *pinch)
{
    if (!(pinch->changeFlags() & QPinchGesture::ScaleFactorChanged))
        return;

    switch (pinch->state()) {
    case Qt::NoGesture:
        break;
    case Qt::GestureStarted:
        mGestureStartScale = mScaleValue;
        // fall through
    case Qt::GestureUpdated: {
        qreal factor = pinch->scaleFactor();
        qreal scale = boundedScaleValue(mGestureStartScale * factor);
        setScaleValue(std::floor(scale * 10000 + 0.5) / 10000);
        break;
    }
    case Qt::GestureFinished:
    case Qt::GestureCanceled:
        break;
    }
}

void TZoomComboBox::zoomIn()
{
    foreach (qreal scale, mZoomFactors) {
        if (scale > mScaleValue) {
            setScaleValue(scale);
            break;
        }
    }
}

void TZoomComboBox::zoomOut()
{
    for (int i = mZoomFactors.count() - 1; i >= 0; --i) {
        if (mZoomFactors[i] < mScaleValue) {
            setScaleValue(mZoomFactors[i]);
            break;
        }
    }
}

void TZoomComboBox::resetZoom()
{
    setScaleValue(1.0);
}

void TZoomComboBox::slotComboEdited()
{
    int pos = mComboRegExp.indexIn(currentText());
    Q_ASSERT(pos != -1);
    Q_UNUSED(pos)

    qreal scale = qBound(mZoomFactors.first(),
                         qreal(mComboRegExp.cap(1).toDouble() / 100.f),
                         mZoomFactors.last());

    setScaleValue(scale);
}

void TZoomComboBox::slotCurrentIndexChanged(int index)
{
    mScaleValue = mZoomFactors[index];
    emit scaleChanged(mScaleValue);
}

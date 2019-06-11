#include "frame.h"
#include "../../base/tr.h"

static const QString P_BACKGROUND = T("Tile Layer");
static const QString P_NUMBER = T("Number");
static const QString P_DURATION = T("Duration");

TFrame::TFrame(QObject *parent) :
    TObject(TObject::FRAME, parent)
{
    initPropertySheet();
}

TFrame::~TFrame()
{

}

void TFrame::saveToStream(QDataStream &stream) const
{
    stream << mPropertySheet->getValue(PID_FRAME_TILE_LAYER).toPoint();
    stream << mPropertySheet->getValue(PID_FRAME_TILE_NUMBER).toPoint();
    stream << mPropertySheet->getValue(PID_FRAME_DURATION).toPoint();
}

void TFrame::readFromStream(QDataStream &stream)
{
    int background;
    int number;
    int duration;
    stream >> background;
    stream >> number;
    stream >> duration;
    mPropertySheet->setValue(PID_FRAME_TILE_LAYER, background);
    mPropertySheet->setValue(PID_FRAME_TILE_NUMBER, number);
    mPropertySheet->setValue(PID_FRAME_DURATION, duration);
}

void TFrame::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_BACKGROUND, PID_FRAME_TILE_LAYER);
    mPropertySheet->addProperty(PT_INT, P_NUMBER, PID_FRAME_TILE_NUMBER);
    mPropertySheet->addProperty(PT_INT, P_DURATION, PID_FRAME_DURATION);
}

QString TFrame::typeString() const
{
    return T("Frame");
}

bool TFrame::isCongener(TObject *object) const
{
    return static_cast<TFrame*>(object);
}

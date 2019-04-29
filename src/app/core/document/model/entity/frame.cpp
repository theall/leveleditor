#include "frame.h"
#include "../../base/tr.h"

static const QString P_Background = T("Background");
static const QString P_Number = T("Number");
static const QString P_Duration = T("Duration");

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

}

void TFrame::readFromStream(QDataStream &stream)
{
    int background;
    int number;
    int duration;
    stream >> background;
    stream >> number;
    stream >> duration;
    mPropertySheet->setValue(PID_FRAME_Background, background);
    mPropertySheet->setValue(PID_FRAME_Number, number);
    mPropertySheet->setValue(PID_FRAME_Duration, duration);
}

void TFrame::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_Background, PID_FRAME_Background);
    mPropertySheet->addProperty(PT_INT, P_Number, PID_FRAME_Number);
    mPropertySheet->addProperty(PT_INT, P_Duration, PID_FRAME_Duration);
}

QString TFrame::typeString() const
{
    return T("Frame");
}

bool TFrame::isCongener(TObject *object) const
{
    return static_cast<TFrame*>(object);
}

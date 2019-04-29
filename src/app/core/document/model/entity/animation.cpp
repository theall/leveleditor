#include "animation.h"
#include "../../base/tr.h"

static const QString P_SEQUENCE = T("Sequence");
static const QString P_BG_SEL = T("Background");
static const QString P_N_SEL = T("Number");
static const QString P_CURRENT_FRAME = T("Current frame");

TAnimation::TAnimation(QObject *parent) :
    TObject(TObject::ANIMATION, parent)
{
    initPropertySheet();
}

TAnimation::~TAnimation()
{

}

TFrameList TAnimation::frameList() const
{
    return mFrameList;
}

void TAnimation::setFrameList(const TFrameList &frameList)
{
    mFrameList = frameList;
}

void TAnimation::saveToStream(QDataStream &stream) const
{

}

void TAnimation::readFromStream(QDataStream &stream)
{
    int aniSeq;
    int aniFrames;
    int aniBgSel;
    int aniNSel;
    int aniCurFrame;
    stream >> aniSeq;
    stream >> aniFrames;
    stream >> aniBgSel;
    stream >> aniNSel;
    stream >> aniCurFrame;
    mFrameList.clear();
    for(int i=0;i<aniFrames;i++) {
        TFrame *frame = new TFrame(this);
        frame->readFromStream(stream);
        mFrameList.append(frame);
    }
    mPropertySheet->setValue(PID_ANIMATION_SEQUENCE, aniSeq);
    mPropertySheet->setValue(PID_ANIMATION_BG_SEL, aniBgSel);
    mPropertySheet->setValue(PID_ANIMATION_N_SEL, aniNSel);
    mPropertySheet->setValue(PID_ANIMATION_CURRENT_FRAME, aniCurFrame);
}

void TAnimation::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_SEQUENCE, PID_ANIMATION_SEQUENCE);
    mPropertySheet->addProperty(PT_INT, P_BG_SEL, PID_ANIMATION_BG_SEL);
    mPropertySheet->addProperty(PT_INT, P_N_SEL, PID_ANIMATION_N_SEL);
    mPropertySheet->addProperty(PT_INT, P_CURRENT_FRAME, PID_ANIMATION_CURRENT_FRAME);
}

QString TAnimation::typeString() const
{
    return T("Animation");
}

bool TAnimation::isCongener(TObject *object) const
{
    return static_cast<TAnimation*>(object);
}

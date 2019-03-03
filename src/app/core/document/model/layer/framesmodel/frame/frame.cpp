#include "frame.h"
#include "framescene/framescene.h"
#include "areasundocommand.h"

#include <gameutils.h>
#include "../../../../document.h"
#include "../../../../base/docutil.h"
#include "../../../../base/docobject.h"

#include <QDataStream>

static const char *P_IMAGE = "Image";
static const char *P_VECTOR = "Vector";
static const char *P_ANTI_GRAVITY = "Anti-Gravity";
static const char *P_DURATION = "Duration";
static const char *P_ANCHOR = "Anchor";
static const char *P_INTERRUPT_TYPE = "Interrupt type";

TFrame *TFrame::mStandardFrame = nullptr;

TFrame::TFrame(QObject *parent) :
    TDocObject(parent)
  , mPixmap(nullptr)
  , mPrevBuddy(nullptr)
  , mSoundSet(new TSoundSet(this))
  , mVectorTableModel(new TVectorTableModel(this))
{
    setObjectName("Frame");

    QObject *obj = parent;
    while (obj) {
        mDocument = qobject_cast<TDocument*>(obj);
        if(mDocument)
            break;
        obj = obj->parent();
    }
    if(!mDocument)
        throw QString("File:%1, Line:%2: Parent must be document.").arg(__FILE__).arg(__LINE__);

    connect(mSoundSet->soundItemsModel(),
            SIGNAL(soundItemsCountChanged(int,int)),
            this,
            SLOT(slotSoundItemsCountChanged(int,int)));
    connect(mVectorTableModel,
            SIGNAL(vectorItemsAdded(TVectorItemList,QList<int>)),
            this,
            SLOT(slotVectorItemsAdded(TVectorItemList,QList<int>)));
    connect(mVectorTableModel,
            SIGNAL(vectorItemsRemoved(TVectorItemList,QList<int>)),
            this,
            SLOT(slotVectorItemsRemoved(TVectorItemList,QList<int>)));
    connect(mVectorTableModel,
            SIGNAL(vectorItemsCountChanged(int,int)),
            this,
            SLOT(slotVectorItemsCountChanged(int,int)));
    connect(mVectorTableModel,
            SIGNAL(vectorPropertyChanged(TPropertyItem*,QVariant)),
            this,
            SIGNAL(propertyChanged(TPropertyItem*,QVariant)));
    initPropertySheet();

    for(int i=0;i<TArea::TypeCount;i++)
    {
        mAreaManagers[i] = new TAreaManager((TArea::Type)i, this);
        connect(mAreaManagers[i], SIGNAL(areasChanged()), this, SIGNAL(frameChanged()));
    }

    // Initialize scene at last
    mScene = new TFrameScene(this);
}

TFrame::~TFrame()
{

}

QString TFrame::mimeType()
{
    return "2dcombat/frame";
}

QByteArray TFrame::toByteArray() const
{
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    dataStream << *this;
    return data;
}

void TFrame::loadFromByteArray(QByteArray *byteArray)
{
    QDataStream dataStream(byteArray, QIODevice::ReadOnly);
    dataStream >> *this;
}

TFrame *TFrame::prevBuddy()
{
    TFrame *buddyFrame = mPrevBuddy?mPrevBuddy:mStandardFrame;
    return buddyFrame==this?nullptr:buddyFrame;
}

void TFrame::setPrevBuddy(TFrame *buddy)
{
    if(mPrevBuddy==buddy)
        return;

    TFrame *oldBuddy = mPrevBuddy;
    mPrevBuddy = buddy;

    emit frameBuddyChanged(oldBuddy);
}

void TFrame::loadFromModel(const Model::TFrame &frame, void *context)
{
    TDocument *document = (TDocument*)context;
    if(!document)
        return;

    mAreaManagers[TArea::Undertake]->setRectList(DocUtil::toRectList(frame.getUndertakeRectList()));
    mAreaManagers[TArea::Attack]->setRectList(DocUtil::toRectList(frame.getAttackRectList()));
    mAreaManagers[TArea::Collide]->setRectList(DocUtil::toRectList(frame.getCollideRectList()));
    mAreaManagers[TArea::Terrain]->setRectList(DocUtil::toRectList(frame.getTerrianRectList()));
    mFootRect = DocUtil::toRectF(frame.getFootRect());

    FREE_CONTAINER(mHandList);
    for(Model::THand *handModel : frame.getHandList())
    {
        THand *hand = new THand(this);
        hand->loadFromModel(*handModel);
        mHandList.append(hand);
    }

    mPixmap = document->getPixmap(QString::fromStdString(frame.getImagePath()));
    if(!mPixmap)
        throw(QString("Failed to load pixmap %1").arg(QString::fromStdString(frame.getImagePath())));

    if(mAreaManagers[TArea::Collide]->isEmpty())
    {
        mAreaManagers[TArea::Collide]->add(0,0,mPixmap->width(),mPixmap->height());
    }
    (*mPropertySheet)[P_IMAGE]->setValue(mPixmap->fileName());
    (*mPropertySheet)[P_DURATION]->setValue(frame.getDuration());
    (*mPropertySheet)[P_VECTOR]->setValue(DocUtil::toPointF(frame.getVector()));
    (*mPropertySheet)[P_ANTI_GRAVITY]->setValue(frame.getAntiGravity());
    (*mPropertySheet)[P_ANCHOR]->setValue(DocUtil::toPointF(frame.getAnchor()));
    (*mPropertySheet)[P_INTERRUPT_TYPE]->setValue(frame.getInterruptType());

    mSoundSet->loadFromModel(frame.getSoundSet());
    mVectorTableModel->loadFromModel(frame.getVectorItemsList());
}

Model::TFrame *TFrame::toModel() const
{
    QString image = mPropertySheet->getValue(P_IMAGE).toString();
    if(image.isEmpty())
        Q_ASSERT(false);

    Model::TFrame *frame = new Model::TFrame;
    frame->setImagePath(mDocument->getPixmapRelativePath(image).toStdString());
    frame->setDuration(mPropertySheet->getValue(P_DURATION).toInt());
    frame->setVector(DocUtil::toVector2(mPropertySheet->getValue(P_VECTOR).toPointF()));
    frame->setAnchor(DocUtil::toVector2(mPropertySheet->getValue(P_ANCHOR).toPointF()));
    frame->setAntiGravity(mPropertySheet->getValue(P_ANTI_GRAVITY).toBool());
    frame->setInterruptType((InterruptType)mPropertySheet->getValue(P_INTERRUPT_TYPE).toInt());
    frame->setCollideRectList(DocUtil::toRectList(mAreaManagers[TArea::Collide]->toRectList()));
    frame->setAttackRectList(DocUtil::toRectList(mAreaManagers[TArea::Attack]->toRectList()));
    frame->setTerrianRectList(DocUtil::toRectList(mAreaManagers[TArea::Terrain]->toRectList()));
    frame->setUndertakeRectList(DocUtil::toRectList(mAreaManagers[TArea::Undertake]->toRectList()));
    frame->setSoundSet(mSoundSet->toModel());
    frame->setVectorItemsList(mVectorTableModel->toModel());
    return frame;
}

TPixmap *TFrame::pixmap() const
{
    return mPixmap;
}

void TFrame::setPixmap(TPixmap *pixmap)
{
    if(mPixmap==pixmap || !pixmap)
        return;

    mPixmap = pixmap;
    QString fileName = pixmap->fileName();
    TPropertyItem *propertyItem = (*mPropertySheet)[P_IMAGE];
    QString oldFileName = propertyItem->value().toString();
    propertyItem->setValue(pixmap->fileName());
    mAreaManagers[TArea::Collide]->clear();
    mAreaManagers[TArea::Collide]->add(0,0,pixmap->width(),pixmap->height());
    emit propertyChanged(propertyItem, QVariant(oldFileName));
}

QString TFrame::getImageName() const
{
    if(!mPixmap)
        return QString();

    return mPixmap->fileName();
}

void TFrame::setImageName(const QString &imageName)
{
    if(!mDocument)
        return;

    setPixmap(mDocument->getPixmap(imageName));
}

void TFrame::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue)
{
    if(!item)
        return;

    if(mDocument)
    {
        PropertyID pid = item->propertyId();
        if(pid == PID_FRAME_IMAGE) {
            mPixmap = mDocument->getPixmap(item->value().toString());
        }
    }

    emit propertyChanged(item, oldValue);
}

void TFrame::slotSoundItemsCountChanged(int oldCount, int newCount)
{
    if((oldCount==0 || newCount==0) && (oldCount != newCount))
    {
        emit frameChanged();
    }
}

void TFrame::slotVectorItemsAdded(const TVectorItemList &vectorItemList, const QList<int> indexList)
{
    Q_UNUSED(indexList);
    Q_UNUSED(vectorItemList);
    int vectorCount = mVectorTableModel->vectorItemsCount();
    if(vectorCount < 1)
        return;

    TPropertyItem *durationPropertyItem = mPropertySheet->get(P_DURATION);
    if(durationPropertyItem->value().toInt() < vectorCount)
        durationPropertyItem->setValue(vectorCount);

    emit frameChanged();
}

void TFrame::slotVectorItemsRemoved(const TVectorItemList &vectorItemList, const QList<int> indexList)
{
    Q_UNUSED(indexList);
    Q_UNUSED(vectorItemList);
    int vectorCount = mVectorTableModel->vectorItemsCount();
    TPropertyItem *durationPropertyItem = mPropertySheet->get(P_DURATION);
    if(durationPropertyItem->value().toInt()==vectorItemList.size()+vectorCount) {
        if(vectorCount < 1)
            vectorCount = 1;
        durationPropertyItem->setValue(vectorCount);
    }

    emit frameChanged();
}

void TFrame::slotVectorItemsCountChanged(int oldCount, int newCount)
{
    if((oldCount==0 || newCount==0) && (oldCount != newCount))
    {
        emit frameChanged();
    }
}

InterruptType TFrame::getInterruptType() const
{
    return (InterruptType)mPropertySheet->getValue(P_INTERRUPT_TYPE).toInt();
}

void TFrame::setInterruptType(const InterruptType &interruptType)
{
    (*mPropertySheet)[P_INTERRUPT_TYPE]->setValue(interruptType);
}

TVectorTableModel *TFrame::vectorTableModel() const
{
    return mVectorTableModel;
}

TSoundSet *TFrame::soundSet() const
{
    return mSoundSet;
}

TFrame *TFrame::standardFrame()
{
    return mStandardFrame;
}

void TFrame::setStandardFrame(TFrame *standardFrame)
{
    mStandardFrame = standardFrame;
}

void TFrame::moveAnchor(const QPointF &distance)
{
    QPointF anchorPos = mPropertySheet->getValue(P_ANCHOR).toPointF();
    (*mPropertySheet)[P_ANCHOR]->setValue(anchorPos + distance);
}

QPointF TFrame::anchor() const
{
    return mPropertySheet->getValue(P_ANCHOR).toPointF();
}

void TFrame::setAnchor(const QPointF &anchor)
{
    (*mPropertySheet)[P_ANCHOR]->setValue(anchor);
}

void TFrame::cmdSetAnchor(const QPointF &anchor)
{
    (*mPropertySheet)[P_ANCHOR]->setNewValue(anchor);
}

TAreaManager *TFrame::terrianAreaManager() const
{
    return mAreaManagers[TArea::Terrain];
}

TAreaManager *TFrame::undertakeAreaManager() const
{
    return mAreaManagers[TArea::Undertake];
}

TAreaManager *TFrame::attackAreaManager() const
{
    return mAreaManagers[TArea::Attack];
}

TAreaManager *TFrame::collideAreaManager() const
{
    return mAreaManagers[TArea::Collide];
}

int TFrame::duration() const
{
    return mPropertySheet->getValue(P_DURATION).toInt();
}

void TFrame::setDuration(int duration)
{
    (*mPropertySheet)[P_DURATION]->setValue(duration);
}

bool TFrame::hasCollideArea() const
{
    return !mAreaManagers[TArea::Collide]->isEmpty();
}

bool TFrame::hasAttackArea() const
{
    return !mAreaManagers[TArea::Attack]->isEmpty();
}

bool TFrame::hasUndertakeArea() const
{
    return !mAreaManagers[TArea::Undertake]->isEmpty();
}

bool TFrame::hasTerrianArea() const
{
    return !mAreaManagers[TArea::Terrain]->isEmpty();
}

bool TFrame::hasSound() const
{
    return mSoundSet->soundItemsModel()->soundItemsCount()>0;
}

bool TFrame::hasVector() const
{
    return mVectorTableModel->hasVector();
}

bool TFrame::antiGravity() const
{
    return mPropertySheet->getValue(P_ANTI_GRAVITY).toBool();
}

void TFrame::setAntiGravity(bool antiGravity)
{
    (*mPropertySheet)[P_ANTI_GRAVITY]->setValue(antiGravity);
}

QPointF TFrame::vector() const
{
    return mPropertySheet->getValue(P_VECTOR).toPointF();
}

void TFrame::setVector(const QPointF &vector)
{
    (*mPropertySheet)[P_VECTOR]->setValue(vector);
}

TFrameScene *TFrame::scene() const
{
    return mScene;
}

TPropertySheet *TFrame::propertySheet() const
{
    return mPropertySheet;
}

void TFrame::createScene()
{
    mScene->clear();

    QGraphicsPixmapItem *item = mScene->addPixmap(mPixmap->pixmap());
    item->setPos(100, 100);
}

void TFrame::initPropertySheet()
{
    connect(mPropertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));

    TPropertyItem *propertyItem;
    propertyItem = mPropertySheet->addProperty(PT_PIXMAP, P_IMAGE, PID_FRAME_IMAGE);
    propertyItem = mPropertySheet->addProperty(PT_INT, P_DURATION, PID_FRAME_DURATION, 1);
    propertyItem->addAttribute(PA_MINIMUM, 1);
    propertyItem = mPropertySheet->addProperty(PT_VECTOR, P_VECTOR, PID_FRAME_VECTOR, QPointF(0, 0));
    propertyItem = mPropertySheet->addProperty(PT_VECTOR, P_ANCHOR, PID_FRAME_ANCHOR, QPointF(0, 0));
    propertyItem = mPropertySheet->addProperty(PT_BOOL, P_ANTI_GRAVITY, PID_FRAME_ANTI_GRAVITY, false);
    propertyItem = mPropertySheet->addProperty(PT_ENUM, P_INTERRUPT_TYPE, PID_FRAME_INTERRUPT_TYPE, IT_DISABLE);
    ADD_ENUM_NAMES(propertyItem,IT_COUNT,InterruptType);
}

void TFrame::cmdAddCollideArea(const QRectF &rect)
{
    cmdAddArea(rect, TArea::Collide);
}

void TFrame::cmdAddCollideAreas(const TAreaList &areaList)
{
    checkAreaList(areaList);
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_ADD, mAreaManagers[TArea::Collide], areaList);
    mDocument->addUndoCommand(undoCommand);
}

void TFrame::cmdAddAttackArea(const QRectF &rect)
{
    cmdAddArea(rect, TArea::Attack);
}

void TFrame::cmdAddAttackAreas(const TAreaList &areaList)
{
    checkAreaList(areaList);
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_ADD, mAreaManagers[TArea::Attack], areaList);
    mDocument->addUndoCommand(undoCommand);
}

void TFrame::cmdAddUndertakeArea(const QRectF &rect)
{
    cmdAddArea(rect, TArea::Undertake);
}

void TFrame::cmdAddUndertakeAreas(const TAreaList &areaList)
{
    checkAreaList(areaList);
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_ADD, mAreaManagers[TArea::Undertake], areaList);
    mDocument->addUndoCommand(undoCommand);
}

void TFrame::cmdaddTerrianArea(const QRectF &rect)
{
    cmdAddArea(rect, TArea::Terrain);
}

void TFrame::cmdAddArea(const QRectF &rect, TArea::Type type)
{
    TArea *area = new TArea(rect, type, this);
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_ADD, mAreaManagers[type], area);
    mDocument->addUndoCommand(undoCommand);
}

void TFrame::cmdRemoveAreas(const QList<TArea *> &areaList)
{
    checkAreaList(areaList);
    TArea::Type areaType = areaList.first()->type();
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_REMOVE, mAreaManagers[areaType], areaList);
    mDocument->addUndoCommand(undoCommand);
}

void TFrame::cmdMoveAreas(const QList<TArea *> &areaList, const QPointF &distance)
{
    checkAreaList(areaList);
    TArea::Type areaType = areaList.first()->type();
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_MOVE, mAreaManagers[areaType], areaList, distance);
    mDocument->addUndoCommand(undoCommand);
}

void TFrame::cmdaddTerrianAreas(const TAreaList &areaList)
{
    checkAreaList(areaList);
    TAreasUndoCommand *undoCommand = new TAreasUndoCommand(AUC_ADD, mAreaManagers[TArea::Terrain], areaList);
    mDocument->addUndoCommand(undoCommand);
}

bool TFrame::checkAreaList(const TAreaList &areaList)
{
    if(areaList.size() < 1)
        throw(std::string("Invalid area list size."));

    TArea::Type areaType = areaList.first()->type();
    for(TArea *area : areaList)
    {
        if(area->type() != areaType)
            throw(std::string("Invalid area list, all areas should has the same type."));
    }
    return true;
}

QDataStream &operator<<(QDataStream &out, const TFrame &frame)
{
    out << frame.getImageName();
    out << frame.duration();
    out << frame.vector();
    out << frame.anchor();
    out << frame.antiGravity();
    out << frame.getInterruptType();
    out << *frame.attackAreaManager();
    out << *frame.undertakeAreaManager();
    out << *frame.collideAreaManager();
    out << *frame.terrianAreaManager();
    out << *frame.soundSet();
    out << *frame.vectorTableModel();
    return out;
}

QDataStream &operator>>(QDataStream &in, TFrame &frame)
{
    QString imageName;
    int duration;
    QPointF vector;
    QPointF anchor;
    bool antiGravity;
    int interruptType;
    in >> imageName;
    in >> duration;
    in >> vector;
    in >> anchor;
    in >> antiGravity;
    in >> interruptType;
    in >> *frame.attackAreaManager();
    in >> *frame.undertakeAreaManager();
    in >> *frame.collideAreaManager();
    in >> *frame.terrianAreaManager();
    in >> *frame.soundSet();
    in >> *frame.vectorTableModel();
    frame.setImageName(imageName);
    frame.setDuration(duration);
    frame.setVector(vector);
    frame.setAnchor(anchor);
    frame.setAntiGravity(antiGravity);
    frame.setInterruptType((InterruptType)interruptType);
    return in;
}

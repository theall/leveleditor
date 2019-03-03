#include "miniscenecontroller.h"
#include "../gui/component/tabwidget/graphicsview.h"
#include "../gui/component/miniscenedock/miniscene.h"
#include "../gui/component/tabwidget/tabwidget.h"

#include <QScrollBar>

TMiniSceneController::TMiniSceneController(QObject *parent) :
    TAbstractController(parent)
  , mGraphicsView(nullptr)
  , mMiniScene(nullptr)
  , mNeedRedraw(false)
  , mDrawFlags(DrawAll)
{
    mSceneImageUpdateTimer.setSingleShot(true);
    connect(&mSceneImageUpdateTimer, SIGNAL(timeout()), SLOT(slotRedrawTimeout()));
}

TMiniSceneController::~TMiniSceneController()
{

}

bool TMiniSceneController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    if(mMiniScene)
    {
        connect(mMiniScene, SIGNAL(resized()), this, SLOT(slotMiniSceneResized()));
    }
    return TAbstractController::joint(mainWindow, core);
}

void TMiniSceneController::setCurrentDocument(TDocument *document)
{
    if(mDocument)
        mDocument->disconnect(this);

    if(mGraphicsView) {
        //mGraphicsView->zoomable()->disconnect(this);
        mGraphicsView->horizontalScrollBar()->disconnect(this);
        mGraphicsView->verticalScrollBar()->disconnect(this);
    }

    mGraphicsView = mMainWindow->tabWidget()->currentGraphicsView();

    if(document)
        connect(document->undoStack(), SIGNAL(indexChanged(int)), this, SLOT(scheduleUpdateSceneImage()));

    if(mGraphicsView) {
        connect(mGraphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), SLOT(slotUpdateMiniScene()));
        connect(mGraphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), SLOT(slotUpdateMiniScene()));
        //connect(mGraphicsView->zoomable(), SIGNAL(scaleChanged(qreal)), SLOT(update()));
    }

    scheduleUpdateSceneImage();
}

void TMiniSceneController::slotRedrawTimeout()
{
    convertSceneToImage();
}

void TMiniSceneController::slotUpdateMiniScene()
{

}

void TMiniSceneController::slotMiniSceneResized()
{
    //updateImageRect();
    scheduleUpdateSceneImage();
}

void TMiniSceneController::slotMiniSceneWheeled(const QPoint &cursorPos, int delta)
{
    //centerViewOnLocalPixel(cursorPos, delta);
}

TMiniSceneController::DrawFlags TMiniSceneController::getDrawFlags() const
{
    return mDrawFlags;
}

void TMiniSceneController::setDrawFlags(const DrawFlags &drawFlags)
{
    mDrawFlags = drawFlags;
}

void TMiniSceneController::scheduleUpdateSceneImage()
{
    mSceneImageUpdateTimer.start(100);
}

void TMiniSceneController::slotTimerEvent()
{

}

QImage TMiniSceneController::convertSceneToImage()
{
    QImage sceneImage;
    if(!mDocument)
        return sceneImage;

//    SceneRenderer *renderer = mDocument->renderer();
//    const QRect r = contentsRect();
//    QSize mapSize = renderer->mapSize();

//    if(mapSize.isEmpty()) {
//        return sceneImage;
//    }

//    QMargins margins = mDocument->map()->computeLayerOffsetMargins();
//    mapSize.setWidth(mapSize.width() + margins.left() + margins.right());
//    mapSize.setHeight(mapSize.height() + margins.top() + margins.bottom());

//    // Determine the largest possible scale
//    qreal scale = qMin((qreal) r.width() / mapSize.width(), (qreal) r.height() / mapSize.height());

//    // Allocate a new image when the size changed
//    const QSize imageSize = mapSize * scale;
//    if(sceneImage.size() != imageSize) {
//        sceneImage = QImage(imageSize, QImage::Format_ARGB32_Premultiplied);
//        updateImageRect();
//    }

//    if(imageSize.isEmpty())
//        return;

//    bool drawObjects = mDrawFlags.testFlag(DrawObjects);
//    bool drawTiles = mDrawFlags.testFlag(DrawTiles);
//    bool drawImages = mDrawFlags.testFlag(DrawImages);
//    bool drawTileGrid = mDrawFlags.testFlag(DrawGrid);
//    bool visibleLayersOnly = mDrawFlags.testFlag(IgnoreInvisibleLayer);

//    // Remember the current render flags
//    const DrawFlags renderFlags = renderer->flags();
//    renderer->setFlag(ShowTileObjectOutlines, false);

//    sceneImage.fill(Qt::transparent);
//    QPainter painter(&sceneImage);
//    painter.setRenderHints(QPainter::SmoothPixmapTransform);
//    painter.setTransform(QTransform::fromScale(scale, scale));
//    painter.translate(margins.left(), margins.top());
//    renderer->setPainterScale(scale);

//    foreach (const Layer *layer, mDocument->map()->layers())
//    {
//        if(visibleLayersOnly && !layer->isVisible())
//            continue;

//        painter.setOpacity(layer->opacity());
//        painter.translate(layer->offset());

//        const TileLayer *tileLayer = dynamic_cast<const TileLayer*>(layer);
//        const ObjectGroup *objGroup = dynamic_cast<const ObjectGroup*>(layer);
//        const ImageLayer *imageLayer = dynamic_cast<const ImageLayer*>(layer);

//        if(tileLayer && drawTiles) {
//            renderer->drawTileLayer(&painter, tileLayer);
//        } else if(objGroup && drawObjects) {
//            QList<SceneObject*> objects = objGroup->objects();

//            if(objGroup->drawOrder() == ObjectGroup::TopDownOrder)
//                qStableSort(objects.begin(), objects.end(), objectLessThan);

//            foreach (const SceneObject *object, objects) {
//                if(object->isVisible()) {
//                    if(object->rotation() != qreal(0)) {
//                        QPointF origin = renderer->pixelToScreenCoords(object->position());
//                        painter.save();
//                        painter.translate(origin);
//                        painter.rotate(object->rotation());
//                        painter.translate(-origin);
//                    }

//                    const QColor color = SceneObjectItem::objectColor(object);
//                    renderer->drawSceneObject(&painter, object, color);

//                    if(object->rotation() != qreal(0))
//                        painter.restore();
//                }
//            }
//        } else if(imageLayer && drawImages) {
//            renderer->drawImageLayer(&painter, imageLayer);
//        }

//        painter.translate(-layer->offset());
//    }

//    if(drawTileGrid) {
//        Preferences *prefs = Preferences::instance();
//        renderer->drawGrid(&painter, QRectF(QPointF(), renderer->mapSize()), prefs->gridColor());
//    }

//    renderer->setFlags(renderFlags);
    return sceneImage;
}


//void TMiniSceneController::updateImageRect()
//{
//    QRect imageRect = sceneImage.rect();
//    if(imageRect.isEmpty()) {
//        mImageRect = QRect();
//        return;
//    }

//    // Scale and center the image
//    const QRect r = contentsRect();
//    qreal scale = qMin((qreal)r.width()/imageRect.width(), (qreal)r.height()/imageRect.height());
//    imageRect.setSize(imageRect.size() * scale);
//    imageRect.moveCenter(r.center());

//    mImageRect = imageRect;
//}

//static bool objectLessThan(const SceneObject *a, const SceneObject *b)
//{
//    return a->y() < b->y();
//}

//void TMiniSceneController::centerViewOnLocalPixel(const QPoint &centerPos, int delta)
//{
//    if(!mMainWindow->tabWidget()->currentContainer())
//    TGraphicsView *graphicsView = DocumentManager::instance()->currentGraphicsView();
//    if(!graphicsView)
//        return;

//    if(delta != 0)
//        graphicsView->zoomable()->handleWheelDelta(delta);

//    graphicsView->centerOn(mapToScene(centerPos));
//}

//QRect TMiniSceneController::getViewPortRect() const
//{
//    TGraphicsView *graphicsView = DocumentManager::instance()->currentGraphicsView();
//    if(!graphicsView)
//        return QRect(0, 0, 1, 1);

//    const QRectF sceneRect = graphicsView->sceneRect();
//    const QRectF viewRect = graphicsView->mapToScene(graphicsView->viewport()->geometry()).boundingRect();
//    return QRect((viewRect.x() - sceneRect.x()) / sceneRect.width() * mImageRect.width() + mImageRect.x(),
//                 (viewRect.y() - sceneRect.y()) / sceneRect.height() * mImageRect.height() + mImageRect.y(),
//                 viewRect.width() / sceneRect.width() * mImageRect.width(),
//                 viewRect.height() / sceneRect.height() * mImageRect.height());
//}

//QPointF TMiniSceneController::mapToScene(const QPoint &p) const
//{
//    if(mImageRect.isEmpty())
//        return QPointF();

//    TGraphicsView *graphicsView = DocumentManager::instance()->currentGraphicsView();
//    if(!graphicsView)
//        return QPointF();

//    const QRectF sceneRect = graphicsView->sceneRect();
//    p -= mImageRect.topLeft();
//    return QPointF(p.x() * (sceneRect.width() / mImageRect.width()) + sceneRect.x(),
//                   p.y() * (sceneRect.height() / mImageRect.height()) + sceneRect.y());
//}

#include "miniscenecontroller.h"
#include "../core/document/graphics/graphicsscene.h"
#include "../gui/component/tabwidget/graphicsview.h"
#include "../gui/component/miniscenedock/miniscenedock.h"
#include "../gui/component/tabwidget/tabwidget.h"
#include "../gui/widgets/zoomcombobox.h"

#include <QDebug>
#include <QScrollBar>

TMiniSceneController::TMiniSceneController(QObject *parent) :
    TAbstractController(parent)
  , mGraphicsView(nullptr)
  , mMiniScene(nullptr)
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

    mMiniScene = mainWindow->getMiniSceneDock()->miniScene();
    mZoomComboBox = mainWindow->getZoomComboBox();

    Q_ASSERT(mMiniScene);
    Q_ASSERT(mZoomComboBox);

    connect(mMiniScene, SIGNAL(resized()), this, SLOT(slotMiniSceneResized()));
    connect(mMiniScene, SIGNAL(requestLocatePoint(QPoint,int)), this, SLOT(slotRequestLocatePoint(QPoint,int)));
    return TAbstractController::joint(mainWindow, core);
}

void TMiniSceneController::setCurrentDocument(TDocument *document)
{
    if(mDocument) {
        mDocument->disconnect(this);
    }

    if(mGraphicsView) {
        mGraphicsView->disconnect(this);
        mGraphicsView->horizontalScrollBar()->disconnect(this);
        mGraphicsView->verticalScrollBar()->disconnect(this);
    }

    mGraphicsView = mMainWindow->getTabWidget()->currentGraphicsView();

    QColor backgroundColor(Qt::black);
    if(document) {
        connect(document->undoStack(), SIGNAL(indexChanged(int)), this, SLOT(delayUpdateSceneImage()));

        TSceneModel *sceneModel = document->getSceneModel();
        connect(sceneModel->propertySheet(),
                SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
                this,
                SLOT(slotSceneModelPropertyItemValueChanged(TPropertyItem *, QVariant)));
        backgroundColor = sceneModel->getBackgroundColor();
    }
    if(mGraphicsView) {
        connect(mGraphicsView, SIGNAL(resized()), this, SLOT(slotGraphicsViewResized()));
        connect(mGraphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), SLOT(slotGraphicsViewScrollBarValueChanged()));
        connect(mGraphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), SLOT(slotGraphicsViewScrollBarValueChanged()));
    }

    mMiniScene->setBackgroundColor(backgroundColor);
    delayUpdateSceneImage();
}

void TMiniSceneController::slotRedrawTimeout()
{
    QImage image = convertSceneToImage();
    mMiniScene->setSceneImage(image);
    updateViewPortRect();
    mMiniScene->update();
}

void TMiniSceneController::slotGraphicsViewScrollBarValueChanged()
{
    updateViewPortRect();
    mMiniScene->update();
}

void TMiniSceneController::slotMiniSceneResized()
{
    delayUpdateSceneImage();
}

void TMiniSceneController::slotGraphicsViewResized()
{
    delayUpdateSceneImage();
}

void TMiniSceneController::slotRequestLocatePoint(const QPoint &point, int delta)
{
    if(!mGraphicsView)
        return;

    if(delta != 0)
        mZoomComboBox->handleWheelDelta(delta);

//    static int x = 0;
//    qDebug() << x << point;
//    x++;
    mGraphicsView->forceCenterOn(mapToScene(point));
}

void TMiniSceneController::slotSceneModelPropertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &)
{
    if(!propertyItem)
        return;

    PropertyID pid = propertyItem->propertyId();
    if(pid == PID_SCENE_BACKGROUND_COLOR) {
        mMiniScene->setBackgroundColor(propertyItem->value().value<QColor>());
    }
}

void TMiniSceneController::delayUpdateSceneImage()
{
    mSceneImageUpdateTimer.start(100);
}

void TMiniSceneController::slotTimerEvent()
{

}

void TMiniSceneController::slotScaleChanged(qreal)
{
    updateViewPortRect();
    mMiniScene->update();
}

QImage TMiniSceneController::convertSceneToImage()
{
    if(!mGraphicsView)
        return QImage();

    TGraphicsScene *scene = static_cast<TGraphicsScene*>(mGraphicsView->scene());
    if(!scene)
        return QImage();

    return scene->toImage();
}

QPointF TMiniSceneController::mapToScene(const QPoint &p) const
{
    QRectF imageRect = mMiniScene->imageRect();
    if(imageRect.isEmpty())
        return QPointF();

    QPointF _p(p);
    const QRectF sceneRect = mGraphicsView->sceneRect();
    _p -= imageRect.topLeft();
    return QPointF(_p.x() * (sceneRect.width() / imageRect.width()) + sceneRect.x(),
                   _p.y() * (sceneRect.height() / imageRect.height()) + sceneRect.y());
}

void TMiniSceneController::updateViewPortRect() const
{
    QRect ret(0, 0, 1, 1);
    if(mGraphicsView) {
        QRectF imageRect = mMiniScene->imageRect();
        const QRectF sceneRect = mGraphicsView->sceneRect();
        const QRectF viewRect = mGraphicsView->mapToScene(mGraphicsView->viewport()->geometry()).boundingRect();
        ret = QRect((viewRect.x() - sceneRect.x()) / sceneRect.width() * imageRect.width() + imageRect.x(),
                     (viewRect.y() - sceneRect.y()) / sceneRect.height() * imageRect.height() + imageRect.y(),
                     viewRect.width() / sceneRect.width() * imageRect.width(),
                     viewRect.height() / sceneRect.height() * imageRect.height());
        // qDebug() << imageRect << sceneRect << viewRect << ret;
    }
    mMiniScene->setViewPortRect(ret);
}

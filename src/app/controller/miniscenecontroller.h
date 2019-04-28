#ifndef MINISCENECONTROLLER_H
#define MINISCENECONTROLLER_H

#include <QTimer>

#include "abstractcontroller.h"

class TGraphicsView;
class TMiniSceneFrame;
class TZoomComboBox;
class TMiniSceneController : public TAbstractController
{
    Q_OBJECT

public:

    TMiniSceneController(QObject *parent = nullptr);
    ~TMiniSceneController();

    // TAbstractController interface
    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

public slots:
    void delayUpdateSceneImage();

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;

private slots:
    void slotScaleChanged(qreal scale);
    void slotRedrawTimeout();
    void slotGraphicsViewScrollBarValueChanged();
    void slotMiniSceneResized();
    void slotGraphicsViewResized();
    void slotRequestLocatePoint(const QPoint &point, int delta = 0);
    void slotSceneModelPropertyItemValueChanged(TPropertyItem*, const QVariant &oldValue);

private:
    TGraphicsView *mGraphicsView;
    TMiniSceneFrame *mMiniScene;
    QTimer mSceneImageUpdateTimer;
    bool mNeedRedraw;
    QRectF mImageRect;
    TZoomComboBox *mZoomComboBox;

    QPointF mapToScene(const QPoint &p) const;
    QImage convertSceneToImage();
    void updateViewPortRect() const;
};

#endif // MINISCENECONTROLLER_H

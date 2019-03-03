#ifndef MINISCENECONTROLLER_H
#define MINISCENECONTROLLER_H

#include <QTimer>

#include "abstractcontroller.h"

class TGraphicsView;
class TMiniScene;

class TMiniSceneController : public TAbstractController
{
    Q_OBJECT

public:
    enum DrawFlag {
        DrawObjects             = 0x0001,
        DrawTiles               = 0x0002,
        DrawImages              = 0x0004,
        IgnoreInvisibleLayer    = 0x0008,
        DrawGrid                = 0x0010,
        DrawAll = 0xffffffff
    };
    Q_DECLARE_FLAGS(DrawFlags, DrawFlag)

    TMiniSceneController(QObject *parent = nullptr);
    ~TMiniSceneController();

    // TAbstractController interface
    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

    DrawFlags getDrawFlags() const;
    void setDrawFlags(const DrawFlags &drawFlags);

public slots:
    void scheduleUpdateSceneImage();

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;

private slots:
    void slotRedrawTimeout();
    void slotUpdateMiniScene();
    void slotMiniSceneResized();
    void slotMiniSceneWheeled(const QPoint &cursorPos, int delta);

private:
    TGraphicsView *mGraphicsView;
    TMiniScene *mMiniScene;
    QTimer mSceneImageUpdateTimer;
    bool mNeedRedraw;
    DrawFlags mDrawFlags;

    QRect getViewPortRect() const;
    QPointF mapToScene(const QPoint &p) const;
    void updateImageRect();
    QImage convertSceneToImage();
    void centerViewOnLocalPixel(const QPoint &centerPos, int delta = 0);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TMiniSceneController::DrawFlags)

#endif // MINISCENECONTROLLER_H

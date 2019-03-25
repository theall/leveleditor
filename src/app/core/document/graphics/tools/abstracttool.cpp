#include "abstracttool.h"

#include <QKeyEvent>

TAbstractTool::TAbstractTool(const QString &name, const QIcon &icon,
                           const QKeySequence &shortcut, QObject *parent)
    : QObject(parent)
    , mName(name)
    , mIcon(icon)
    , mShortcut(shortcut)
    , mEnabled(false)
{

}

/**
 * Sets the current status information for this tool. This information will be
 * displayed in the status bar.
 */
void TAbstractTool::setStatusInfo(const QString &statusInfo)
{
    if (mStatusInfo != statusInfo) {
        mStatusInfo = statusInfo;
        emit statusInfoChanged(mStatusInfo);
    }
}

/**
 * Sets the cursor used by this tool. This will be the cursor set on the
 * viewport of the MapView while the tool is active.
 */
void TAbstractTool::setCursor(const QCursor &cursor)
{
    mCursor = cursor;
    emit cursorChanged(cursor);
}

void TAbstractTool::setEnabled(bool enabled)
{
    if (mEnabled == enabled)
        return;

    mEnabled = enabled;
    emit enabledChanged(enabled);
}

void TAbstractTool::keyPressed(QKeyEvent *event)
{
    event->ignore();
}

void TAbstractTool::mouseDoubleClicked(QGraphicsSceneMouseEvent *event)
{
    mousePressed(event);
}

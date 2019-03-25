#pragma once

#include <QIcon>
#include <QCursor>
#include <QObject>
#include <QString>
#include <QMetaType>
#include <QKeyEvent>
#include <QKeySequence>
#include <QGraphicsSceneMouseEvent>

class MapDocument;
class MapScene;
class ToolManager;

/**
 * An abstraction of any kind of tool used to edit the map.
 *
 * Events that hit the MapScene are forwarded to the current tool, which can
 * handle them as appropriate for that tool.
 *
 * A tool will usually add one or more QGraphicsItems to the scene in order to
 * represent it to the user.
 */
class TAbstractTool : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QKeySequence shortcut READ shortcut WRITE setShortcut)
    Q_PROPERTY(QString statusInfo READ statusInfo WRITE setStatusInfo NOTIFY statusInfoChanged)
    Q_PROPERTY(QCursor cursor READ cursor WRITE setCursor NOTIFY cursorChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    /**
     * Constructs an abstract tool with the given \a name and \a icon.
     */
    TAbstractTool(const QString &name,
                 const QIcon &icon,
                 const QKeySequence &shortcut,
                 QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QKeySequence shortcut() const;
    void setShortcut(const QKeySequence &shortcut);

    QString statusInfo() const;
    void setStatusInfo(const QString &statusInfo);

    QCursor cursor() const;
    void setCursor(const QCursor &cursor);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    /**
     * Activates this tool. If the tool plans to add any items to the scene, it
     * probably wants to do it here.
     */
    virtual void activate(MapScene *scene) = 0;

    /**
     * Deactivates this tool. Should do any necessary cleanup to make sure the
     * tool is no longer active.
     */
    virtual void deactivate(MapScene *scene) = 0;

    virtual void keyPressed(QKeyEvent *);

    /**
     * Called when the mouse entered the scene. This is usually an appropriate
     * time to make a hover item visible.
     */
    virtual void mouseEntered() = 0;

    /**
     * Called when the mouse left the scene.
     */
    virtual void mouseLeft() = 0;

    /**
     * Called when the mouse cursor moves in the scene.
     */
    virtual void mouseMoved(const QPointF &pos,
                            Qt::KeyboardModifiers modifiers) = 0;

    /**
     * Called when a mouse button is pressed on the scene.
     */
    virtual void mousePressed(QGraphicsSceneMouseEvent *event) = 0;

    /**
     * Called when a mouse button is released on the scene.
     */
    virtual void mouseReleased(QGraphicsSceneMouseEvent *event) = 0;

    /**
     * Called when a mouse button is pressed a second time on the scene, after
     * a short interval.
     *
     * By default, this function calls mousePressed.
     */
    virtual void mouseDoubleClicked(QGraphicsSceneMouseEvent *event);

    /**
     * Called when the user presses or releases a modifier key resulting
     * in a change of modifier status, and when the tool is enabled with
     * a modifier key pressed.
     */
    virtual void modifiersChanged(Qt::KeyboardModifiers) {}

    /**
     * Called when the application language changed.
     */
    virtual void languageChanged() = 0;

signals:
    void statusInfoChanged(const QString &statusInfo);
    void cursorChanged(const QCursor &cursor);
    void enabledChanged(bool enabled);

private:
    QString mName;
    QIcon mIcon;
    QKeySequence mShortcut;
    QString mStatusInfo;
    QCursor mCursor;
    bool mEnabled;
};


inline QString TAbstractTool::name() const
{
    return mName;
}

inline void TAbstractTool::setName(const QString &name)
{
    mName = name;
}

inline QIcon TAbstractTool::icon() const
{
    return mIcon;
}

inline void TAbstractTool::setIcon(const QIcon &icon)
{
    mIcon = icon;
}

inline QKeySequence TAbstractTool::shortcut() const
{
    return mShortcut;
}

inline void TAbstractTool::setShortcut(const QKeySequence &shortcut)
{
    mShortcut = shortcut;
}

inline QString TAbstractTool::statusInfo() const
{
    return mStatusInfo;
}

inline QCursor TAbstractTool::cursor() const
{
    return mCursor;
}

inline bool TAbstractTool::isEnabled() const
{
    return mEnabled;
}

Q_DECLARE_METATYPE(TAbstractTool*)

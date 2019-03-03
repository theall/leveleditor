#ifndef GRAPHICSITEMUTIL_H
#define GRAPHICSITEMUTIL_H

#include <QGraphicsItem>
#include <QGraphicsObject>

enum GraphicsItemType
{
    GIT_AREA = QGraphicsItem::UserType + 1,
    GIT_HANDLE_RESIZE,
    GIT_HANDLE_ROTATE,
    GIT_COUNT
};

#endif // GRAPHICSITEMUTIL_H

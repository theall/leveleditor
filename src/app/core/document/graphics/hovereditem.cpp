/*
 * hovereditem.cpp
 * Copyright 2019, Bilge Theall<wazcd_1608@qq.com>
 *
 * This file is part of level editor.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "hovereditem.h"

#include <QPainter>
#include <utils/utils.h>

THoveredItem::THoveredItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mObjectItem(nullptr)
  , mIsHoveredIndicator(true)
{
    setAcceptedMouseButtons(Qt::MouseButtons());
    setAcceptHoverEvents(true);
}

void THoveredItem::setIsHoverIndicator(bool isHoverIndicator)
{
    if (mIsHoveredIndicator == isHoverIndicator)
        return;

    mIsHoveredIndicator = isHoverIndicator;

    setOpacity(mIsHoveredIndicator?0.5:1.0);
    update();
}

QRectF THoveredItem::boundingRect() const
{
    return mBoundingRect;
}

void THoveredItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *,
                          QWidget *)
{
    if (mIsHoveredIndicator) {
        QRectF bounds = mBoundingRect;

        const QLineF lines[4] = {
            QLineF(bounds.topLeft(), bounds.topRight()),
            QLineF(bounds.bottomLeft(), bounds.bottomRight()),
            QLineF(bounds.topLeft(), bounds.bottomLeft()),
            QLineF(bounds.topRight(), bounds.bottomRight())
        };

        // Draw solid white lines
        QPen pen(Qt::white, 1.0, Qt::SolidLine);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawLines(lines, 4);

        const qreal devicePixelRatio = painter->device()->devicePixelRatioF();
        const qreal dashLength = std::ceil(Utils::dpiScaled(3) * devicePixelRatio);

        // Draw black dashed lines above the white line
        pen.setColor(Qt::black);
        pen.setCapStyle(Qt::FlatCap);
        pen.setDashPattern({dashLength, dashLength});
        painter->setPen(pen);
        painter->drawLines(lines, 4);
    }
}

TObjectItem *THoveredItem::objectItem() const
{
    return mObjectItem;
}

void THoveredItem::setObjectItem(TObjectItem *objectItem)
{
    if(mObjectItem) {
        mObjectItem->disconnect(this);
    }

    mObjectItem = objectItem;

    if(mObjectItem) {
        mBoundingRect = mObjectItem->boundingRect();
        if(!isVisible())
            setVisible(true);
    } else {
        if(isVisible())
            setVisible(false);
        mBoundingRect = QRectF();
    }
}

QColor THoveredItem::color() const {
    return mColor;
}

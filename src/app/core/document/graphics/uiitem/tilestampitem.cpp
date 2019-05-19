/*
 * tilestampitem.cpp
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

#include "tilestampitem.h"

#include <QPainter>
#include <utils/utils.h>

TTileStampItem::TTileStampItem(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    setAcceptedMouseButtons(Qt::MouseButtons());
    setAcceptHoverEvents(false);
    setOpacity(0.5);
}

TTileStampItem::~TTileStampItem()
{

}

void TTileStampItem::setPixmap(const QPixmap &pixmap)
{
    QGraphicsPixmapItem::setPixmap(pixmap);

    mTranslate.setX(pixmap.width()/2);
    mTranslate.setY(pixmap.height()/2);
}

void TTileStampItem::setCenterPos(const QPointF &centerPos)
{
    setPos(centerPos - mTranslate);
}

/*
 * hovereditem.h
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

#pragma once

#include <QGraphicsObject>
#include "objectitem.h"

/**
 * Graphics item for displaying a rectangle on hovered map object.
 */
class THoveredItem : public QGraphicsObject
{
    Q_OBJECT

public:
    THoveredItem(QGraphicsItem *parent = nullptr);
    ~THoveredItem();

    bool isHoverIndicator() const;
    void setIsHoverIndicator(bool isHoverIndicator);

    TObjectItem *objectItem() const;
    void setObjectItem(TObjectItem *objectItem);

public:
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private slots:
    void slotObjectBoundingRectChanged();

private:
    TObjectItem *mObjectItem;
    QRectF mBoundingRect;
    QColor mColor;      // Cached color of the object
    bool mIsHoveredIndicator;
    QColor color() const;
};


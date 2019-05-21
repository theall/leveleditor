/*
 * miniscenedock.h
 * Copyright 2017, Bilge Theall <wazcd_1608@qq.com>
 *
 * This file is part of 2dcombat.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MINIMAPDOCK_H
#define MINIMAPDOCK_H

#include "../basedock.h"
#include "minisceneframe.h"

/**
 * Shows a mini-scene.
 */
class TMiniSceneDock : public TBaseDock
{
    Q_OBJECT

public:
    TMiniSceneDock(QWidget *parent = nullptr);
    ~TMiniSceneDock();

    TMiniSceneFrame *miniScene() const;

protected:
    void changeEvent(QEvent *e) override;

private:
    void retranslateUi();

    TMiniSceneFrame *mMiniScene;
};

#endif // MINIMAPDOCK_H

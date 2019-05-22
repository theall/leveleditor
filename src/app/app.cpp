/*
 * Copyright (C) Bilge Theall, wazcd_1608@qq.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include "app.h"

#include "res/version.h"
#include "utils/preferences.h"

#include "controller/maincontroller.h"
#include "core/core.h"
#include "gui/mainwindow.h"

#include <QTextCodec>
#include <QFileOpenEvent>

TApp::TApp(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    TVersionInfo *vi = TVersionInfo::instance();
    setOrganizationDomain(vi->legalCopyright());
    setApplicationDisplayName(vi->fileDescription());
    setOrganizationName(vi->companyName());
    setApplicationName(vi->productName());
    setApplicationVersion(vi->productVersion());

#ifdef Q_OS_MAC
    setAttribute(Qt.AA_DontShowIconsInMenus);
#endif

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    TPreferences::instance();
}

TApp::~TApp()
{
    TPreferences::deleteInstance();
}

int TApp::start()
{
    TCore core;
    TMainWindow gui;
    TMainController controller;
    if(!controller.joint(&gui, &core))
        return 0;

    connect(this, SIGNAL(requestOpenMap(QString)), &gui, SIGNAL(requestOpenMap(QString)));

    int ret = exec();
    return ret;
}

bool TApp::event(QEvent *event)
{
    if(event->type()==QEvent::FileOpen)
    {
        QFileOpenEvent *fileOpenEvent = static_cast<QFileOpenEvent*>(event);
        emit requestOpenMap(fileOpenEvent->file());
        return true;
    }
    return QApplication::event(event);
}

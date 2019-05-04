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
#include "utils.h"

#include <QDir>
#include <QtMath>
#include <QScreen>
#include <QProcess>
#include <QFileInfo>
#include <QApplication>

namespace Utils {

QString microSecToTimeStr(long ms, bool padZero)
{
    return secToTimeStr(qCeil((double)ms/1000), padZero);
}

QString secToTimeStr(long seconds, bool padZero)
{
    int hour = seconds / 3600;
    if(hour > 99)
        hour = 99;

    seconds %= 3600;

    int minute = seconds / 60;
    if(minute>99)
        minute = 99;

    seconds %= 60;

    int second = seconds % 60;

    QString result;
    if(hour > 0)
        result = QString::asprintf("%2d:%2d:%2d", hour, minute, second);
    else
        result = QString::asprintf("%2d:%2d", minute, second);

    if(padZero)
        result = result.replace(" ", "0");

    return result;
}

QString absoluteFilePath(QString fileName)
{
    QFileInfo fi(fileName);
    if(fi.isRelative())
    {
        QDir dir(qApp->applicationDirPath());
        fileName = dir.absoluteFilePath(fileName);
    }
    return fileName;
}

bool exploreFile(QString fileName)
{
    bool ret = false;
#ifdef Q_OS_WIN32
    ret = QProcess::startDetached("explorer /select,"+QDir::toNativeSeparators(fileName));
#elif Q_OS_UNIX
#elif Q_OS_MACX
#endif
    return ret;
}

void cpy2wchar(wchar_t *dest, const QString &source)
{
    if(dest)
    {
        std::wstring sourceW = source.toStdWString();
        wcscpy(dest, sourceW.c_str());
    }
}

qreal defaultDpiScale()
{
    static qreal scale = []{
        if (const QScreen *screen = QGuiApplication::primaryScreen())
            return screen->logicalDotsPerInchX() / 96.0;
        return 1.0;
    }();
    return scale;
}

qreal dpiScaled(qreal value)
{
#ifdef Q_OS_MAC
    // On mac the DPI is always 72 so we should not scale it
    return value;
#else
    static const qreal scale = defaultDpiScale();
    return value * scale;
#endif
}

QSize dpiScaled(QSize value)
{
    return QSize(qRound(dpiScaled(value.width())),
                 qRound(dpiScaled(value.height())));
}

QPoint dpiScaled(QPoint value)
{
    return QPoint(qRound(dpiScaled(value.x())),
                  qRound(dpiScaled(value.y())));
}

QRectF dpiScaled(QRectF value)
{
    return QRectF(dpiScaled(value.x()),
                  dpiScaled(value.y()),
                  dpiScaled(value.width()),
                  dpiScaled(value.height()));
}

QSize smallIconSize()
{
    static QSize size = dpiScaled(QSize(16, 16));
    return size;
}

}

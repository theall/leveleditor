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
#ifndef UTILS_H
#define UTILS_H

#include <QString>

enum ExportState
{
    ES_NULL = 0x0,
    ES_READY = 0x1,
    ES_STARTING = 0x2,
    ES_RUNNING = 0x4,
    ES_ERROR = 0x8,
    ES_PAUSED = 0x10,
    ES_COMPLETE = 0x20,
    ES_ALL = 0xFFFFFFFF
};

struct TExportParam
{
    wchar_t fileName[260];
    wchar_t title[260];
    wchar_t indexName[260];
    wchar_t outputPath[260];
    wchar_t errorString[260];
    char format[10];
    int sampleRate;
    int duration;
    bool autoTruncate;
    bool overwrite;
    int progressCurrentFrames;
    int progressTotalFrames;
    int number;
    int serverTick;
    int clientTick;
    ExportState state;
    ExportState oldState;
    TExportParam()
    {
        *fileName = 0;
        *indexName = 0;
        *outputPath = 0;
        *errorString = 0;
        *format = 0;
        sampleRate = 44100;
        duration = 0;
        autoTruncate = false;
        overwrite = false;
        progressCurrentFrames = 0;
        progressTotalFrames = 0;
        number = -1;
        serverTick = 0;
        clientTick = 0;
        state = ES_NULL;
        oldState = ES_NULL;
    }
};

namespace Utils{
    const int TextHighlight = Qt::UserRole + 1;
    const int IsCurrentRow = TextHighlight + 1;
    const int IsPlayingItem = IsCurrentRow + 1;

    QString microSecToTimeStr(long ms, bool padZero=true);
    QString secToTimeStr(long seconds, bool padZero=true);
    QString absoluteFilePath(QString fileName);
    bool exploreFile(QString fileName);
    void cpy2wchar(wchar_t *dest, QString source);
}

#endif // UTILS_H

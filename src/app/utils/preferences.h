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
#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDate>
#include <QTime>
#include <QColor>
#include <QString>
#include <QStringList>
#include <QSettings>

class TPreferences : public QObject
{
    Q_OBJECT

public:
    static const int MAX_RECENT_FILES;
    static const int ICON_SIZE_SMALL;
    static const int ICON_SIZE_MEDIUM;
    static const int ICON_SIZE_LARGE;
    static TPreferences* mInstance;

public:
    TPreferences(QObject *parent=0);
    ~TPreferences();

    static TPreferences *instance();
    static void deleteInstance();

    void windowGeometryState(QByteArray* g, QByteArray* s);
    void setWindowGeometryState(const QVariant &geometry, const QVariant &windowState);

    bool displayTrayIcon() const;
    void setDisplayTrayIcon(bool displayTrayIcon);

    bool alwaysOnTop() const;
    void setAlwaysOnTop(bool alwaysOnTop);

    int runCount() const;
    void setRunCount(int runCount);

    QString language() const;
    void setLanguage(const QString &language);

    QString lastOpenPath() const;
    void setLastOpenPath(const QString &lastOpenPath);

    QString lastOpenDir() const;
    void setLastOpenDir(const QString &lastOpenDir);

    void save();

    bool saveBeforeExit() const;
    void setSaveBeforeExit(bool saveBeforeExit);

    bool openLastFile() const;
    void setOpenLastFile(bool openLastFile);

    bool fullScreen() const;
    void setFullScreen(bool fullScreen);

    int toolbarIconSize() const;
    void setToolbarIconSize(int toolbarIconSize);

    QStringList recentFiles() const;
    void setRecentFiles(const QStringList &recentFiles);

    bool hideMenuBar() const;
    void setHideMenuBar(bool hideMenuBar);

    bool hideStatusBar() const;
    void setHideStatusBar(bool hideStatusBar);

    QStringList recentOpenedFiles() const;
    void setRecentOpenedFiles(const QStringList &recentOpenedFiles);

    QString lastActiveFile() const;
    void setLastActiveFile(const QString &lastActiveFile);

    QString style() const;
    void setStyle(const QString &style);

    qreal sceneScale() const;
    void setSceneScale(const qreal &sceneScale);

    QString enginePath() const;
    void setEnginePath(const QString &enginePath);

    bool enableDebugMultiInstances() const;
    void setEnableDebugMultiInstances(bool enableDebugMultiInstances);

    QString root() const;
    void setRoot(const QString &root);

signals:
    void hideMenuBarChanged(bool);
    void toolbarIconSizeChanged(int);
    void hideStatusBarChanged(bool);
    void styleChanged(const QString &style);

private:
    QSettings *mSettings;
    bool mAlwaysOnTop;
    int mRunCount;
    QString mStyle;
    QString mLanguage;
    QString mLastOpenPath;
    QString mLastOpenDir;
    bool mDisplayTrayIcon;
    bool mSaveBeforeExit;
    bool mOpenLastFile;
    bool mFullScreen;
    int mToolbarIconSize;
    QStringList mRecentFiles;
    bool mHideMenuBar;
    bool mHideStatusBar;
    QStringList mRecentOpenedFiles;
    QString mLastActiveFile;
    qreal mSceneScale;
    QString mEnginePath;
    bool mEnableDebugMultiInstances;
    QString mRoot;

    void setValue(const QString &section, const QVariant &value);
    QVariant value(const QString &section, const QVariant &defValue=QVariant());
    bool boolValue(const QString &key, bool defValue = false);
    QColor colorValue(const QString &key, const QColor &defValue = QColor());
    QString stringValue(const QString &key, const QString &defValue = "");
    int intValue(const QString &key, int defaultValue=0);
    float floatValue(const QString &key, float defaultValue=0.0);
    QDate dateValue(const QString &key, int defaultValue=-1);
    QTime timeValue(const QString &key, int defaultValue=0);
    QStringList listValue(const QString &key);
    qreal doubleValue(const QString &key, qreal defaultValue);
};

#endif // PREFERENCES_H

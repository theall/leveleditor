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
#include "preferences.h"
#include "utils.h"

#include <QSettings>

const int TPreferences::MAX_RECENT_FILES = 10;
const int TPreferences::ICON_SIZE_SMALL = 16;
const int TPreferences::ICON_SIZE_MEDIUM = 24;
const int TPreferences::ICON_SIZE_LARGE = 32;

#define SETTINGS_FILE_NAME                "setting.ini"

// General
#define SEC_GUI "Gui"
#define SEC_GUI_ALWAYS_ON_TOP "AlwaysOnTop"
#define SEC_GUI_LANGUAGE "Language"
#define SEC_GUI_STYLE "Style"
#define SEC_GUI_GEOMETRY "Geometry"
#define SEC_GUI_WINDOW_STATE "WindowState"
#define SEC_GUI_LAST_OPEN_PATH "LastOpenPath"
#define SEC_GUI_LAST_OPEN_DIR "LastOpenDirectory"
#define SEC_GUI_SAVEBEFOREEXIT "SaveBeforeExit"
#define SEC_GUI_OPENLASTFILE "OpenLastFile"
#define SEC_GUI_FULLSCREEN "FullScreen"
#define SEC_GUI_TOOLBARICONSIZE "ToolbarIconSize"
#define SEC_GUI_RECENTFILES "RecentFiles"
#define SEC_GUI_HIDEMENUBAR "HideMenuBar"
#define SEC_GUI_HIDESTATUSBAR "HideStatusBar"
#define SEC_GUI_RECENTOPENEDFILES "RecentOpenedFiles"
#define SEC_GUI_LASTACTIVEFILE "LastActiveFile"
#define SEC_GUI_SCENE_SCALE "SceneScale"
#define SEC_GUI_SHOW_TILE_BORDER "ShowTileBorder"

// Install
#define SEC_INSTALL "Install"
#define SEC_INSTALL_RUN_COUNT "RunCount"
#define SEC_INSTALL_GAME_ROOT "GameRoot"

// Options
#define SEC_OPTIONS "Options"

#define SEC_OPTION_GENERAL "OptionGeneral"
#define SEC_OPTION_DISPLAY_TRAY_ICON "DisplayTrayIcon"
#define SEC_OPTION_DEBUG_MULTI_INSTANCES "MultiInstances"

#define SEC_OPTION_UI "OptionUI"
#define SEC_OPTION_UI_APP_STYLE "AppStyle"
#define SEC_OPTION_UI_BASE_COLOR "BaseColor"
#define SEC_OPTION_UI_SELECTION_COLOR "SelectionColor"
#define SEC_OPTION_UI_USE_OPENGL "UseOpenGL"

#define SEC_OPTION_DEBUG "OptionDebug"
#define SEC_OPTION_DEBUG_ENGINE_PATH "EnginePath"

#define SET_VALUE(value,member,parent,section) \
    if(member==value)\
        return;\
    mSettings->beginGroup(parent);\
    mSettings->setValue(section, value);\
    mSettings->endGroup();\
    member = value

#define SET_VALUE2(value,member,parent,sub,section) \
    if(member==value)\
        return;\
    mSettings->beginGroup(parent);\
    mSettings->beginGroup(sub);\
    mSettings->setValue(section, value);\
    mSettings->endGroup();\
    mSettings->endGroup();\
    member = value

TPreferences *TPreferences::mInstance = NULL;

//
// This class holds user preferences and provides a convenient interface to
// access them.
//
TPreferences::TPreferences(QObject *parent):
    QObject(parent)
{
    mSettings = new QSettings(Utils::absoluteFilePath(SETTINGS_FILE_NAME), QSettings::IniFormat);

    // Retrieve gui settings
    mSettings->beginGroup(SEC_GUI);
    mAlwaysOnTop = boolValue(SEC_GUI_ALWAYS_ON_TOP);
    mLastOpenPath = stringValue(SEC_GUI_LAST_OPEN_PATH);
    mLastOpenDir = stringValue(SEC_GUI_LAST_OPEN_DIR);
    mSaveBeforeExit = boolValue(SEC_GUI_SAVEBEFOREEXIT, true);
    mOpenLastFile = boolValue(SEC_GUI_OPENLASTFILE, true);
    mFullScreen = boolValue(SEC_GUI_FULLSCREEN);
    mToolbarIconSize = intValue(SEC_GUI_TOOLBARICONSIZE, ICON_SIZE_MEDIUM);
    mLanguage = stringValue(SEC_GUI_LANGUAGE, "en");
    mStyle = stringValue(SEC_GUI_STYLE);
    mRecentFiles = listValue(SEC_GUI_RECENTFILES);
    mHideMenuBar = boolValue(SEC_GUI_HIDEMENUBAR);
    mHideStatusBar = boolValue(SEC_GUI_HIDESTATUSBAR);
    mRecentOpenedFiles = listValue(SEC_GUI_RECENTOPENEDFILES);
    mLastActiveFile = stringValue(SEC_GUI_LASTACTIVEFILE);
    mSceneScale = doubleValue(SEC_GUI_SCENE_SCALE, 1.0);
    mSceneScale = QString::number(mSceneScale, 'f', 2).toDouble();
    mShowTileBorder = boolValue(SEC_GUI_SHOW_TILE_BORDER);
    mSettings->endGroup();

    //// Options
    mSettings->beginGroup(SEC_OPTIONS);
        // general
        mSettings->beginGroup(SEC_OPTION_GENERAL);
        mDisplayTrayIcon = boolValue(SEC_OPTION_DISPLAY_TRAY_ICON, true);
        mEnableDebugMultiInstances = boolValue(SEC_OPTION_DEBUG_MULTI_INSTANCES);
        mSettings->endGroup();

        // UI
        mSettings->beginGroup(SEC_OPTION_UI);
        mBaseColor = colorValue(SEC_OPTION_UI_BASE_COLOR);
        mSelectionColor = colorValue(SEC_OPTION_UI_SELECTION_COLOR);
        mApplicationStyle = (ApplicationStyle)intValue(SEC_OPTION_UI_APP_STYLE);
        mUseOpenGL = boolValue(SEC_OPTION_UI_USE_OPENGL);
        mSettings->endGroup();

        // debug
        mSettings->beginGroup(SEC_OPTION_DEBUG);
        mEnginePath = stringValue(SEC_OPTION_DEBUG_ENGINE_PATH);
        mSettings->endGroup();

    mSettings->endGroup();

    //// Keeping track of some usage information
    mSettings->beginGroup(SEC_INSTALL);

        // This section wrote by main controller while write trial license
        mRunCount = intValue(SEC_INSTALL_RUN_COUNT) + 1;
        mSettings->setValue(SEC_INSTALL_RUN_COUNT, mRunCount);
        mGameRoot = stringValue(SEC_INSTALL_GAME_ROOT);
    mSettings->endGroup();
}

TPreferences::~TPreferences()
{
    if(mSettings)
    {
        mSettings->sync();
        delete mSettings;
        mSettings = NULL;
    }
}

TPreferences* TPreferences::instance()
{
    if(mInstance==NULL)
        mInstance = new TPreferences();
    return mInstance;
}

void TPreferences::deleteInstance()
{
    if(mInstance)
    {
        delete mInstance;
        mInstance = NULL;
    }
}

void TPreferences::save()
{
    mSettings->sync();
}

bool TPreferences::saveBeforeExit() const
{
    return mSaveBeforeExit;
}

void TPreferences::setSaveBeforeExit(bool saveBeforeExit)
{
    SET_VALUE(saveBeforeExit, mSaveBeforeExit, SEC_GUI, SEC_GUI_SAVEBEFOREEXIT);
}

bool TPreferences::openLastFile() const
{
    return mOpenLastFile;
}

void TPreferences::setOpenLastFile(bool openLastFile)
{
    SET_VALUE(openLastFile, mOpenLastFile, SEC_GUI, SEC_GUI_OPENLASTFILE);
}

bool TPreferences::fullScreen() const
{
    return mFullScreen;
}

void TPreferences::setFullScreen(bool fullScreen)
{
    SET_VALUE(fullScreen, mFullScreen, SEC_GUI, SEC_GUI_FULLSCREEN);
}

int TPreferences::toolbarIconSize() const
{
    return mToolbarIconSize;
}

void TPreferences::setToolbarIconSize(int toolbarIconSize)
{
    SET_VALUE(toolbarIconSize, mToolbarIconSize, SEC_GUI, SEC_GUI_TOOLBARICONSIZE);
    emit toolbarIconSizeChanged(toolbarIconSize);
}

QStringList TPreferences::recentFiles() const
{
    return mRecentFiles;
}

void TPreferences::setRecentFiles(const QStringList &recentFiles)
{
    SET_VALUE(recentFiles, mRecentFiles, SEC_GUI, SEC_GUI_RECENTFILES);
}

bool TPreferences::hideMenuBar() const
{
    return mHideMenuBar;
}

void TPreferences::setHideMenuBar(bool hideMenuBar)
{
    SET_VALUE(hideMenuBar, mHideMenuBar, SEC_GUI, SEC_GUI_HIDEMENUBAR);
    emit hideMenuBarChanged(hideMenuBar);
}

bool TPreferences::hideStatusBar() const
{
    return mHideStatusBar;
}

void TPreferences::setHideStatusBar(bool hideStatusBar)
{
    SET_VALUE(hideStatusBar, mHideStatusBar, SEC_GUI, SEC_GUI_HIDESTATUSBAR);
    emit hideStatusBarChanged(hideStatusBar);
}

QStringList TPreferences::recentOpenedFiles() const
{
    return mRecentOpenedFiles;
}

void TPreferences::setRecentOpenedFiles(const QStringList &recentOpenedFiles)
{
    QStringList realRecentFiles;
    for(QString file : recentOpenedFiles) {
        if(file.isEmpty())
            continue;
        realRecentFiles.append(file);
    }
    SET_VALUE(realRecentFiles, mRecentOpenedFiles, SEC_GUI, SEC_GUI_RECENTOPENEDFILES);
}

QString TPreferences::lastActiveFile() const
{
    return mLastActiveFile;
}

void TPreferences::setLastActiveFile(const QString &lastActiveFile)
{
    SET_VALUE(lastActiveFile, mLastActiveFile, SEC_GUI, SEC_GUI_LASTACTIVEFILE);
}

QString TPreferences::style() const
{
    return mStyle;
}

void TPreferences::setStyle(const QString &style)
{
    SET_VALUE(style, mStyle, SEC_GUI, SEC_GUI_STYLE);
    emit styleChanged(style);
}

qreal TPreferences::sceneScale() const
{
    return mSceneScale;
}

void TPreferences::setSceneScale(const qreal &sceneScale)
{
    qreal scale = QString::number(sceneScale, 'f', 2).toDouble();
    SET_VALUE(scale, mSceneScale, SEC_GUI, SEC_GUI_SCENE_SCALE);
}


QString TPreferences::enginePath() const
{
    return mEnginePath;
}

void TPreferences::setEnginePath(const QString &enginePath)
{
    SET_VALUE2(enginePath, mEnginePath, SEC_OPTIONS, SEC_OPTION_DEBUG, SEC_OPTION_DEBUG_ENGINE_PATH);
}

bool TPreferences::enableDebugMultiInstances() const
{
    return mEnableDebugMultiInstances;
}

void TPreferences::setEnableDebugMultiInstances(bool enableDebugMultiInstances)
{
    SET_VALUE2(enableDebugMultiInstances, mEnableDebugMultiInstances, SEC_OPTIONS, SEC_OPTION_GENERAL, SEC_OPTION_DEBUG_MULTI_INSTANCES);
}

QString TPreferences::gameRoot() const
{
    return mGameRoot;
}

void TPreferences::setGameRoot(const QString &gameRoot)
{
    SET_VALUE(gameRoot, mGameRoot, SEC_INSTALL, SEC_INSTALL_GAME_ROOT);
}

TPreferences::ApplicationStyle TPreferences::applicationStyle() const
{
    return mApplicationStyle;
}

void TPreferences::setApplicationStyle(const ApplicationStyle &applicationStyle)
{
    SET_VALUE2(applicationStyle, mApplicationStyle, SEC_OPTIONS, SEC_OPTION_UI, SEC_OPTION_UI_APP_STYLE);
}

QColor TPreferences::baseColor() const
{
    return mBaseColor;
}

void TPreferences::setBaseColor(const QColor &baseColor)
{
    SET_VALUE(baseColor, mBaseColor, SEC_OPTIONS, SEC_OPTION_UI_BASE_COLOR);
}

QColor TPreferences::selectionColor() const
{
    return mSelectionColor;
}

void TPreferences::setSelectionColor(const QColor &selectionColor)
{
    SET_VALUE(selectionColor, mSelectionColor, SEC_OPTIONS, SEC_OPTION_UI_SELECTION_COLOR);
}

bool TPreferences::showTileBorder() const
{
    return mShowTileBorder;
}

void TPreferences::setShowTileBorder(bool showTileBorder)
{
    SET_VALUE(showTileBorder, mShowTileBorder, SEC_GUI, SEC_GUI_SHOW_TILE_BORDER);
}

bool TPreferences::useOpenGL() const
{
    return mUseOpenGL;
}

void TPreferences::setUseOpenGL(bool useOpenGL)
{
    SET_VALUE2(useOpenGL, mUseOpenGL, SEC_OPTIONS, SEC_OPTION_UI, SEC_OPTION_UI_USE_OPENGL);
}

void TPreferences::windowGeometryState(QByteArray *g, QByteArray *s)
{
    mSettings->beginGroup(SEC_GUI);
    *g = mSettings->value(SEC_GUI_GEOMETRY).toByteArray();
    *s = mSettings->value(SEC_GUI_WINDOW_STATE).toByteArray();
    mSettings->endGroup();
}

void TPreferences::setWindowGeometryState(const QVariant &geometry, const QVariant &windowState)
{
    mSettings->beginGroup(SEC_GUI);
    mSettings->setValue(SEC_GUI_GEOMETRY, geometry);
    mSettings->setValue(SEC_GUI_WINDOW_STATE, windowState);
    mSettings->endGroup();
}

bool TPreferences::displayTrayIcon() const
{
    return mDisplayTrayIcon;
}

void TPreferences::setDisplayTrayIcon(bool displayTrayIcon)
{
    SET_VALUE2(displayTrayIcon, mDisplayTrayIcon, SEC_OPTIONS, SEC_OPTION_GENERAL, SEC_OPTION_DISPLAY_TRAY_ICON);
}

bool TPreferences::alwaysOnTop() const
{
    return mAlwaysOnTop;
}

void TPreferences::setAlwaysOnTop(bool alwaysOnTop)
{
    SET_VALUE(alwaysOnTop, mAlwaysOnTop, SEC_GUI, SEC_GUI_ALWAYS_ON_TOP);
}

int TPreferences::runCount() const
{
    return mRunCount;
}

void TPreferences::setRunCount(int runCount)
{
    SET_VALUE(runCount, mRunCount, SEC_INSTALL, SEC_INSTALL_RUN_COUNT);
}

QString TPreferences::language() const
{
    return mLanguage;
}

void TPreferences::setLanguage(const QString &language)
{
    SET_VALUE(language, mLanguage, SEC_GUI, SEC_GUI_LANGUAGE);
}

QString TPreferences::lastOpenPath() const
{
    return mLastOpenPath;
}

void TPreferences::setLastOpenPath(const QString &lastOpenPath)
{
    SET_VALUE(lastOpenPath, mLastOpenPath, SEC_GUI, SEC_GUI_LAST_OPEN_PATH);
}

QString TPreferences::lastOpenDir() const
{
    return mLastOpenDir;
}

void TPreferences::setLastOpenDir(const QString &lastOpenDir)
{
    SET_VALUE(lastOpenDir, mLastOpenDir, SEC_GUI, SEC_GUI_LAST_OPEN_DIR);
}

void TPreferences::setValue(const QString &section, const QVariant &value)
{
    mSettings->setValue(section, value);
}

QVariant TPreferences::value(const QString &section, const QVariant &defValue)
{
    return mSettings->value(section, defValue);
}

bool TPreferences::boolValue(const QString &key, bool defValue)
{
    return mSettings->value(key, defValue).toBool();
}

QColor TPreferences::colorValue(const QString &key, const QColor &defValue)
{
    QString name = mSettings->value(key, defValue.name()).toString();
    if((!QColor::isValidColor(name)))
        return QColor();
    return QColor(name);
}

QString TPreferences::stringValue(const QString &key, const QString &defValue)
{
    return mSettings->value(key, defValue).toString();
}

int TPreferences::intValue(const QString &key, int defaultValue)
{
    bool ok = false;
    int v = mSettings->value(key, defaultValue).toInt(&ok);
    if (ok)
        return v;
    return defaultValue;
}

float TPreferences::floatValue(const QString &key, float defaultValue)
{
    bool ok = false;
    float v = mSettings->value(key, defaultValue).toFloat(&ok);
    if (ok)
        return v;
    return defaultValue;
}

qreal TPreferences::doubleValue(const QString &key, qreal defaultValue)
{
    bool ok = false;
    float v = mSettings->value(key, defaultValue).toDouble(&ok);
    if (ok)
        return v;
    return defaultValue;
}

QStringList TPreferences::listValue(const QString &key)
{
    return mSettings->value(key).toStringList();
}

QDate TPreferences::dateValue(const QString &key, int defaultValue)
{
    if (defaultValue==-1)
        defaultValue = QDate::currentDate().toJulianDay();
    int days = intValue(key, defaultValue);
    return QDate::fromJulianDay(days);
}

QTime TPreferences::timeValue(const QString &key, int defaultValue)
{
    int seconds = intValue(key, defaultValue);
    QTime time = QTime::fromMSecsSinceStartOfDay(seconds);
    if(!time.isValid())
        time = QTime::fromMSecsSinceStartOfDay(0);
    return time;
}

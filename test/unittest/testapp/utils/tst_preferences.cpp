#include "tst_preferences.h"
#include <utils/preferences.h>
#include <QtTest>

#define VERIFY_READ_WRITE_VALUE(setter,getter,value)\
    TPreferences::instance()->setter(value);\
    TPreferences::deleteInstance();\
    QCOMPARE(TPreferences::instance()->getter(), value)

#define VERIFY_READ_WRITE_BOOLEAN(setter,getter)\
    VERIFY_READ_WRITE_VALUE(setter,getter,true);\
    VERIFY_READ_WRITE_VALUE(setter,getter,false)

TestPreferences::TestPreferences(QObject *parent) : QObject(parent)
{

}

void TestPreferences::testSetWindowGeometryState()
{
    QByteArray geometry, state;
    for(int i=0;i<100;i++) {
        geometry.append((char)i);
        state.append((char)i);
    }
    TPreferences::instance()->setWindowGeometryState(geometry, state);
    TPreferences::deleteInstance();

    QByteArray g, s;
    TPreferences::instance()->windowGeometryState(&g, &s);
    QCOMPARE(geometry, g);
    QCOMPARE(state, s);
}

void TestPreferences::testSetDisplayTrayIcon()
{
    VERIFY_READ_WRITE_BOOLEAN(setDisplayTrayIcon, displayTrayIcon);
}
void TestPreferences::testSetAlwaysOnTop()
{
    VERIFY_READ_WRITE_BOOLEAN(setAlwaysOnTop, alwaysOnTop);
}

void TestPreferences::testSetRunCount()
{
    VERIFY_READ_WRITE_VALUE(setRunCount, runCount, 0);
    VERIFY_READ_WRITE_VALUE(setRunCount, runCount, 10);
    VERIFY_READ_WRITE_VALUE(setRunCount, runCount, 9999);
}

void TestPreferences::testSetLanguage()
{
    VERIFY_READ_WRITE_VALUE(setLanguage, language, QString("cn"));
    VERIFY_READ_WRITE_VALUE(setLanguage, language, QString("en"));
}

void TestPreferences::testSetLastOpenPath()
{
    VERIFY_READ_WRITE_VALUE(setLastOpenPath, lastOpenPath, QString("z:/"));
    VERIFY_READ_WRITE_VALUE(setLastOpenPath, lastOpenPath, QString("c:/"));
}

void TestPreferences::testSetLastOpenDir()
{
    VERIFY_READ_WRITE_VALUE(setLastOpenDir, lastOpenDir, QString("c:/"));
}

void TestPreferences::testSetSaveBeforeExit()
{
    VERIFY_READ_WRITE_BOOLEAN(setSaveBeforeExit, saveBeforeExit);
}

void TestPreferences::testSetOpenLastFile()
{
    VERIFY_READ_WRITE_BOOLEAN(setOpenLastFile, openLastFile);
}

void TestPreferences::testSetFullScreen()
{
    VERIFY_READ_WRITE_BOOLEAN(setFullScreen, fullScreen);
}

void TestPreferences::testSetToolbarIconSize()
{
    VERIFY_READ_WRITE_VALUE(setToolbarIconSize, toolbarIconSize, 16);
    VERIFY_READ_WRITE_VALUE(setToolbarIconSize, toolbarIconSize, 1);
}

void TestPreferences::testSetRecentFiles()
{
    QStringList sl;
    sl << "c:/a.txt";
    sl << "z:/test.bat";
    VERIFY_READ_WRITE_VALUE(setRecentFiles, recentFiles, sl);
}

void TestPreferences::testSetHideMenuBar()
{
    VERIFY_READ_WRITE_BOOLEAN(setHideMenuBar, hideMenuBar);
}

void TestPreferences::testSetHideStatusBar()
{
    VERIFY_READ_WRITE_BOOLEAN(setHideStatusBar, hideStatusBar);
}

void TestPreferences::testSetRecentOpenedFiles()
{
    QStringList sl;
    sl << "c:/a.txt";
    sl << "z:/test.bat";
    VERIFY_READ_WRITE_VALUE(setRecentOpenedFiles, recentOpenedFiles, sl);
}

void TestPreferences::testSetLastActiveFile()
{
    VERIFY_READ_WRITE_VALUE(setLastActiveFile, lastActiveFile, QString("z:/temp/biu.txt"));
    VERIFY_READ_WRITE_VALUE(setLastActiveFile, lastActiveFile, QString("z:/temp/ok.txt"));
}

void TestPreferences::testSetStyle()
{
    VERIFY_READ_WRITE_VALUE(setStyle, style, QString("fusion"));
}

void TestPreferences::testSetSceneScale()
{
    VERIFY_READ_WRITE_VALUE(setSceneScale, sceneScale, 1.0);
}

void TestPreferences::testSetEnginePath()
{
    VERIFY_READ_WRITE_VALUE(setEnginePath, enginePath, QString("z:/"));
}

void TestPreferences::testSetEnableDebugMultiInstances()
{
    VERIFY_READ_WRITE_BOOLEAN(setEnableDebugMultiInstances, enableDebugMultiInstances);
}

void TestPreferences::testSetGameRoot()
{
    VERIFY_READ_WRITE_VALUE(setGameRoot, gameRoot, QString("z:/"));
}

void TestPreferences::testSetApplicationStyle()
{
    VERIFY_READ_WRITE_VALUE(setApplicationStyle, applicationStyle, TPreferences::FusionStyle);
}

void TestPreferences::testSetBaseColor()
{
    VERIFY_READ_WRITE_VALUE(setBaseColor, baseColor, QColor(Qt::black));
}

void TestPreferences::testSetSelectionColor()
{
    VERIFY_READ_WRITE_VALUE(setSelectionColor, selectionColor, QColor(Qt::black));
}

void TestPreferences::testSetShowTileBorder()
{
    VERIFY_READ_WRITE_BOOLEAN(setShowTileBorder, showTileBorder);
}

void TestPreferences::testSetUseOpenGL()
{
    VERIFY_READ_WRITE_BOOLEAN(setUseOpenGL, useOpenGL);
}

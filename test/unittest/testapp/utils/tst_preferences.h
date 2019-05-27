#ifndef TESTPREFERENCES_H
#define TESTPREFERENCES_H

#include <QObject>

class TestPreferences : public QObject
{
    Q_OBJECT
public:
    explicit TestPreferences(QObject *parent = 0);

signals:

private slots:
    void testSetWindowGeometryState();
    void testSetDisplayTrayIcon();
    void testSetAlwaysOnTop();
    void testSetRunCount();
    void testSetLanguage();
    void testSetLastOpenPath();
    void testSetLastOpenDir();
    void testSetSaveBeforeExit();
    void testSetOpenLastFile();
    void testSetFullScreen();
    void testSetToolbarIconSize();
    void testSetRecentFiles();
    void testSetHideMenuBar();
    void testSetHideStatusBar();
    void testSetRecentOpenedFiles();
    void testSetLastActiveFile();
    void testSetStyle();
    void testSetSceneScale();
    void testSetEnginePath();
    void testSetEnableDebugMultiInstances();
    void testSetGameRoot();
    void testSetApplicationStyle();
    void testSetBaseColor();
    void testSetSelectionColor();
    void testSetShowTileBorder();
    void testSetUseOpenGL();
};

#endif // TESTPREFERENCES_H

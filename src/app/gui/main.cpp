#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TMainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

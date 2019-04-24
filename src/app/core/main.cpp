#include "core.h"
#include <QMessageBox>
#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if(argc < 3) {
        QMessageBox::critical(nullptr, "Error", "Need specify game root and map full path!", QMessageBox::Ok);
        return app.exec();
    }

    QGraphicsView gv;
    TCore core;
    core.loadResource(argv[1], false);
    core.open(argv[2]);
    QGraphicsScene *scene;
    scene = core.documents().at(0)->graphicsScene();
    gv.setScene(scene);
    gv.show();
    return app.exec();
}

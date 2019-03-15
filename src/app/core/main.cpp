#include "core.h"
#include <QApplication>
#include <QGraphicsView>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if(argc < 2) {
        QMessageBox::critical(nullptr, "Error", "Need specify map full path!", QMessageBox::Ok);
        return app.exec();
    }

    QGraphicsView gv;
    TCore core;
    core.loadResource("Z:/mh-reinstated-zeto");
    core.open(argv[1]);
    QGraphicsScene *scene;
    scene = core.documents().at(0)->graphicsScene();
    gv.setScene(scene);
    gv.show();
    return app.exec();
}

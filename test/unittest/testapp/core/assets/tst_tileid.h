#ifndef TESTTILEID_H
#define TESTTILEID_H

#include <QObject>

class TestTileId : public QObject
{
    Q_OBJECT

public:
    explicit TestTileId(QObject *parent = 0);

private Q_SLOTS:
    void testSetId();
    void testSetPixmap();
    void testSetTilesetId();
};

#endif // TESTTILEID_H

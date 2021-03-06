#ifndef TESTTILESET_H
#define TESTTILESET_H

#include <QObject>

class TestTileset : public QObject
{
    Q_OBJECT

public:
    explicit TestTileset(QObject *parent = 0);

private Q_SLOTS:
    void testSetId();
    void testAddTile();
    void testSort();
    void testSetTileIdList();
};

#endif // TESTTILESET_H

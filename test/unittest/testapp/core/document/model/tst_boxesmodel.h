#ifndef TESTBOXESMODEL_H
#define TESTBOXESMODEL_H

#include <QObject>

class TestBoxesModel : public QObject
{
    Q_OBJECT

public:
    explicit TestBoxesModel(QObject *parent = 0);

private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
    
};

#endif // TESTBOXESMODEL_H

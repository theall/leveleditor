#ifndef TESTTRIGGERSMODEL_H
#define TESTTRIGGERSMODEL_H

#include <QObject>

class TestTriggersModel : public QObject
{
    Q_OBJECT

public:
    explicit TestTriggersModel(QObject *parent = 0);
private:
    void readWriteTest(const char *buf, int size);

private Q_SLOTS:
    void testReadWrite1();
};

#endif // TESTTRIGGERSMODEL_H

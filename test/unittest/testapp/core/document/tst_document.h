#ifndef TESTDOCUMENT_H
#define TESTDOCUMENT_H

#include <QObject>

class TestDocument : public QObject
{
    Q_OBJECT

public:
    explicit TestDocument(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTDOCUMENT_H
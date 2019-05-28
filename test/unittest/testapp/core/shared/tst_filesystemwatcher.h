#ifndef TESTFILESYSTEMWATCHER_H
#define TESTFILESYSTEMWATCHER_H

#include <QObject>

class TestFileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit TestFileSystemWatcher(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTFILESYSTEMWATCHER_H
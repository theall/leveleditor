#ifndef TIODEBUG_H
#define TIODEBUG_H

#include <QBuffer>

class THookBuffer : public QBuffer
{
public:
    THookBuffer(QByteArray *buf, QObject *parent = Q_NULLPTR);

    static int hookFrom();
    static void setHookFrom(int hookFrom);

    static int hookTo();
    static void setHookTo(int hookTo);

private:
    static int mHookFrom;
    static int mHookTo;

    // QIODevice interface
protected:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
};

#endif // TIODEBUG_H

#include "debug.h"

#include <QDebug>

int THookBuffer::mHookFrom = 0x7fffffff;
int THookBuffer::mHookTo = -1;
THookBuffer::THookBuffer(QByteArray *buf, QObject *parent) :
    QBuffer(buf, parent)
{

}

int THookBuffer::hookFrom()
{
    return mHookFrom;
}

void THookBuffer::setHookFrom(int hookFrom)
{
    mHookFrom = hookFrom;
}

int THookBuffer::hookTo()
{
    return mHookTo;
}

void THookBuffer::setHookTo(int hookTo)
{
    mHookTo = hookTo;
}

qint64 THookBuffer::readData(char *data, qint64 maxlen)
{
    qint64 currentPos = pos();
    if(currentPos>=mHookFrom && currentPos<=mHookTo) {
        qDebug() << "Hooked";
    }
    return QBuffer::readData(data, maxlen);
}

qint64 THookBuffer::writeData(const char *data, qint64 len)
{
    qint64 currentPos = pos();
    if(currentPos>=mHookFrom && currentPos<=mHookTo) {
        qDebug() << "Hooked";
    }
    return QBuffer::writeData(data, len);
}

#include "streamiotest.h"

QDataStream *createInStream(const QByteArray &byteArray)
{
    QDataStream *stream = new QDataStream(byteArray);
    stream->setByteOrder(QDataStream::LittleEndian);
    stream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    return stream;
}

QDataStream *createOutStream(QByteArray *byteArray)
{
    QDataStream *outStream = new QDataStream(byteArray, QIODevice::WriteOnly);
    outStream->setByteOrder(QDataStream::LittleEndian);
    outStream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    return outStream;
}

bool equal(const QByteArray &a1, const QByteArray &a2)
{
    int s1 = a1.size();
    int s2 = a2.size();
    if(s1 != s2)
        return false;

    for(int i=0;i<s1;i++) {
        if(a1.at(i) != a2.at(i))
            return false;
    }
    return true;
}

QByteArray *createByteArray(const char *data, int size)
{
    return new QByteArray(data, size);
}

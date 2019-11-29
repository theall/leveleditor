#ifndef STREAMIOTEST_H
#define STREAMIOTEST_H

#include <QByteArray>
#include <QDataStream>
#include <core/document/base/io.h>

#define READ_WRITE_OBJECT_TEST(className,buf,size) \
    className io; \
    QByteArray inByteArray(buf, size); \
    QDataStream *inStream = createInStream(inByteArray); \
    io.readFromStream(*inStream); \
    QByteArray outByteArray; \
    QDataStream *outStream = createOutStream(&outByteArray); \
    io.saveToStream(*outStream); \
    QVERIFY(equal(inByteArray, outByteArray))

QByteArray *createByteArray(const char *data, int size);
QDataStream *createInStream(const QByteArray &byteArray);
QDataStream *createOutStream(QByteArray *byteArray);
bool equal(const QByteArray &a1, const QByteArray &a2);

#endif // STREAMIOTEST_H

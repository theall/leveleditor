#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <QDataStream>

class TIO
{
public:
    virtual void saveToStream(QDataStream &stream) const = 0;
    virtual void readFromStream(QDataStream &stream) = 0;
    virtual ~TIO() {}
};

#endif // INPUTOUTPUT_H

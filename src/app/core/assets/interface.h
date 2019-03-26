#ifndef INTERFACE_H
#define INTERFACE_H

class ILoadCallback
{
public:
    virtual ~ILoadCallback() {}
    virtual void onProgress(int progress, int total) = 0;
};

#endif // INTERFACE_H

#ifndef MACRO_H
#define MACRO_H

#define DECL_SINGLE_INSTANCE(x) \
public: \
    static x *mInstance; \
    static x *getInstance(); \
    void deleteInstance();

#define IMPL_SINGLE_INSTANCE(x) \
    x *x::mInstance = nullptr; \
    x *x::getInstance() { \
        if(mInstance == nullptr) \
            mInstance = new x(); \
        return mInstance; \
    } \
    void x::deleteInstance() {\
        if(mInstance) {\
            delete mInstance;\
            mInstance = nullptr;\
        }\
    }

#define FREE_CONTAINER(x) \
    for(auto a : x) \
        delete a; \
    x.clear()

#endif // MACRO_H

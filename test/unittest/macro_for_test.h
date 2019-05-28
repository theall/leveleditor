#ifndef MACRO_FOR_TEST_H
#define MACRO_FOR_TEST_H

#include <QtTest>

#define RUN_CLASS(T) \
    T t_##T;\
    QTest::qExec(&t_##T)

#define VERIFY_READ_WRITE_OBJECT_VALUE(object,getter,setter,value) \
    object.setter(value);\
    QCOMPARE(object.getter(), value)

#define VERIFY_READ_WRITE_CLASS_VALUE(className,getter,setter,value) \
    className object;\
    VERIFY_READ_WRITE_OBJECT_VALUE(object,getter,setter,value)

#endif // MACRO_FOR_TEST_H

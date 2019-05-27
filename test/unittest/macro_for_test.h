#ifndef MACRO_FOR_TEST_H
#define MACRO_FOR_TEST_H

#include <QtTest>

#define RUN_CLASS(T) \
    T t;\
    QTest::qExec(&t)

#endif // MACRO_FOR_TEST_H

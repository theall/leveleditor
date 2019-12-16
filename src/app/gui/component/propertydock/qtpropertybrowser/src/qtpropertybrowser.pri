include(../common.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD

qtpropertybrowser-uselib:!qtpropertybrowser-buildlib {
    LIBS += -L$$QTPROPERTYBROWSER_LIBDIR -l$$QTPROPERTYBROWSER_LIBNAME
} else {
    SOURCES += $$PWD/qtpropertybrowser.cpp \
            $$PWD/qtpropertymanager.cpp \
            $$PWD/qteditorfactory.cpp \
            $$PWD/qtvariantproperty.cpp \
            $$PWD/qttreepropertybrowser.cpp \
            $$PWD/qtbuttonpropertybrowser.cpp \
            $$PWD/qtgroupboxpropertybrowser.cpp \
            $$PWD/qtpropertybrowserutils.cpp
    HEADERS += $$PWD/../include/qtpropertybrowser.h \
            $$PWD/../include/qtpropertymanager.h \
            $$PWD/../include/qteditorfactory.h \
            $$PWD/../include/qtvariantproperty.h \
            $$PWD/../include/qttreepropertybrowser.h \
            $$PWD/../include/qtbuttonpropertybrowser.h \
            $$PWD/../include/qtgroupboxpropertybrowser.h \
            $$PWD/../include/qtpropertybrowserutils_p.h
    RESOURCES += $$PWD/qtpropertybrowser.qrc
}

win32 {
    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QT_QTPROPERTYBROWSER_EXPORT
    else:qtpropertybrowser-uselib:DEFINES += QT_QTPROPERTYBROWSER_IMPORT
}

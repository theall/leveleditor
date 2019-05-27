QT += core widgets gui multimedia

INCLUDEPATH += \
    $$PWD/../../../src

SOURCES += \  
    $$PWD/tst_app.cpp

HEADERS  += \  
    $$PWD/tst_app.h

include($$PWD/core/core.pri)
include($$PWD/gui/gui.pri)
include($$PWD/controller/controller.pri)
include($$PWD/utils/utils.pri)

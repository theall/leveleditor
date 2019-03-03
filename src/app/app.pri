SOURCES += \
    $$PWD/app.cpp \
    $$PWD/res/version.cpp

HEADERS  += \
    $$PWD/app.h \
    $$PWD/res/version.h

include($$PWD/core/core.pri)
include($$PWD/gui/gui.pri)
include($$PWD/controller/controller.pri)
include($$PWD/utils/utils.pri)

win32:{
    RC_FILE = $$PWD/res/sceneeditor.rc
    HEADERS += $$PWD/res/win32_ver.h
}

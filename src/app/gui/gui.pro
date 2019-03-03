TEMPLATE = app
CONFIG += c++11 object_parallel_to_source
CONFIG += app_bundle
CONFIG += qt

DEFINES += GUI_STAND_ALONE

include(gui.pri)
include(../utils/utils.pri)

SOURCES += \
    main.cpp

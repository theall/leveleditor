QT += gui widgets multimedia
CONFIG += qt

INCLUDEPATH += \
    $$PWD/widgets

TRANSLATIONS = \
    $$PWD/resource/ts/en.ts \
    $$PWD/resource/ts/zh_cn.ts \
    $$PWD/resource/ts/zh_tw.ts

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/widgets/qtcolorbutton.cpp \
    $$PWD/dialogs/aboutdialog.cpp \
    $$PWD/dialogs/abstractdialog.cpp \
    $$PWD/component/tabwidget/tabwidget.cpp \
    $$PWD/dialogs/newprojectdialog.cpp \
    $$PWD/component/undodock/undodock.cpp \
    $$PWD/component/basedock.cpp \
    $$PWD/component/propertydock/propertiesdock.cpp \
    $$PWD/component/propertydock/propertybrowser.cpp \
    $$PWD/component/propertydock/varianteditorfactory.cpp \
    $$PWD/component/propertydock/variantpropertymanager.cpp \
    $$PWD/component/propertydock/widget/plaintexteditor.cpp \
    $$PWD/component/propertydock/widget/filepathedit.cpp \
    $$PWD/component/propertydock/widget/stringexedit.cpp \
    $$PWD/component/centralwidget.cpp \
    $$PWD/dialogs/preferencesdialog.cpp \
    $$PWD/widgets/qcomboboxex.cpp \
    $$PWD/widgets/qprogressindicator.cpp \
    $$PWD/widgets/shortcutview.cpp \
    $$PWD/dialogs/preferencesdialog/module/languagemanager.cpp \
    $$PWD/dialogs/preferencesdialog/module/shortkeymanager.cpp \
    $$PWD/dialogs/preferencesdialog/shortcutmodel.cpp \
    $$PWD/component/tabwidget/tabcontainer.cpp \
    $$PWD/component/miniscenedock/miniscene.cpp \
    $$PWD/component/miniscenedock/miniscenedock.cpp \
    $$PWD/component/layerdock/layerdock.cpp \
    $$PWD/component/layerdock/layerview.cpp \
    $$PWD/component/movedock/movedock.cpp \
    $$PWD/component/sounddock/sounddock.cpp \
    $$PWD/component/sounddock/soundsetview.cpp \
    $$PWD/widgets/zoomcombobox.cpp \
    $$PWD/component/tabwidget/graphicsview.cpp \
    $$PWD/dialogs/soundresourcedialog.cpp \
    $$PWD/component/propertydock/widget/pixmapedit.cpp \
    $$PWD/component/propertydock/widget/sounditemedit.cpp \
    $$PWD/component/propertydock/widget/sounditemsourceedit.cpp \
    $$PWD/component/propertydock/widget/soundsetedit.cpp \
    $$PWD/dialogs/loadingdialog.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/widgets/qtcolorbutton.h \
    $$PWD/dialogs/aboutdialog.h \
    $$PWD/dialogs/abstractdialog.h \
    $$PWD/component/tabwidget/tabwidget.h \
    $$PWD/dialogs/newprojectdialog.h \
    $$PWD/component/undodock/undodock.h \
    $$PWD/component/basedock.h \
    $$PWD/component/propertydock/propertiesdock.h \
    $$PWD/component/propertydock/propertybrowser.h \
    $$PWD/component/propertydock/varianteditorfactory.h \
    $$PWD/component/propertydock/variantpropertymanager.h \
    $$PWD/component/propertydock/widget/plaintexteditor.h \
    $$PWD/component/propertydock/widget/filepathedit.h \
    $$PWD/component/propertydock/widget/stringexedit.h \
    $$PWD/component/centralwidget.h \
    $$PWD/dialogs/preferencesdialog.h \
    $$PWD/widgets/qcomboboxex.h \
    $$PWD/widgets/qprogressindicator.h \
    $$PWD/widgets/shortcutview.h \
    $$PWD/dialogs/preferencesdialog/module/languagemanager.h \
    $$PWD/dialogs/preferencesdialog/module/shortkeymanager.h \
    $$PWD/dialogs/preferencesdialog/shortcutmodel.h \
    $$PWD/component/tabwidget/tabcontainer.h \
    $$PWD/component/miniscenedock/miniscene.h \
    $$PWD/component/miniscenedock/miniscenedock.h \
    $$PWD/component/layerdock/layerdock.h \
    $$PWD/component/layerdock/layerview.h \
    $$PWD/component/movedock/movedock.h \
    $$PWD/component/sounddock/sounddock.h \
    $$PWD/component/sounddock/soundsetview.h \
    $$PWD/widgets/zoomcombobox.h \
    $$PWD/component/tabwidget/graphicsview.h \
    $$PWD/dialogs/soundresourcedialog.h \
    $$PWD/component/propertydock/widget/pixmapedit.h \
    $$PWD/component/propertydock/widget/sounditemedit.h \
    $$PWD/component/propertydock/widget/sounditemsourceedit.h \
    $$PWD/component/propertydock/widget/soundsetedit.h \
    $$PWD/dialogs/loadingdialog.h

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/dialogs/aboutdialog.ui \
    $$PWD/dialogs/preferencesdialog.ui \
    $$PWD/dialogs/newprojectdialog.ui \
    $$PWD/dialogs/soundresourcedialog.ui \
    $$PWD/dialogs/loadingdialog.ui

RESOURCES += $$PWD/resource/editor.qrc

CONFIG(debug, debug|release) {
    LIBS += -lqtpropertybrowserd
} else {
    LIBS += -lqtpropertybrowser
}

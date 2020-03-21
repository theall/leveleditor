QT += gui widgets multimedia
CONFIG += qt

include($$PWD/component/propertydock/qtpropertybrowser/src/qtpropertybrowser.pri)

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
    $$PWD/component/miniscenedock/miniscenedock.cpp \
    $$PWD/component/layerdock/layerdock.cpp \
    $$PWD/component/layerdock/layerview.cpp \
    $$PWD/widgets/zoomcombobox.cpp \
    $$PWD/component/tabwidget/graphicsview.cpp \
    $$PWD/dialogs/soundresourcedialog.cpp \
    $$PWD/component/propertydock/widget/pixmapedit.cpp \
    $$PWD/component/propertydock/widget/sounditemedit.cpp \
    $$PWD/component/propertydock/widget/sounditemsourceedit.cpp \
    $$PWD/component/propertydock/widget/soundsetedit.cpp \
    $$PWD/dialogs/loadingdialog.cpp \
    $$PWD/component/miniscenedock/minisceneframe.cpp \
    $$PWD/component/tilesetdock/tilesetdock.cpp \
    $$PWD/component/tilesetdock/tilesetview.cpp \
    $$PWD/component/tilesetdock/tilesettab.cpp \
    $$PWD/dialogs/selectrootdialog.cpp \
    $$PWD/component/characterdock/characterdock.cpp \
    $$PWD/component/characterdock/characterview.cpp \
    $$PWD/component/mapsdock/mapsdock.cpp \
    $$PWD/component/mapsdock/modstab/mapstab.cpp \
    $$PWD/component/mapsdock/mapsproxyview.cpp \
    $$PWD/component/mapsdock/modstab.cpp \
    $$PWD/component/mapsdock/modstree.cpp \
    $$PWD/component/mapsdock/modstab/mapview.cpp \
    $$PWD/component/layerdock/iconcheckdelegate.cpp \
    $$PWD/component/layerdock/boldcurrentitemdelegate.cpp \
    $$PWD/style/stylehelper.cpp \
    $$PWD/style/proxystyle.cpp \
    $$PWD/component/tabwidget/graphicsviewcontexmenu.cpp \
    $$PWD/dialogs/newmapdialog.cpp \
    $$PWD/widgets/flexiblescrollbar.cpp \
    $$PWD/dialogs/exceptiondialog.cpp \
    $$PWD/component/animationdock/animationdock.cpp \
    $$PWD/component/animationdock/animationlistview.cpp \
    $$PWD/component/animationdock/container.cpp \
    $$PWD/component/objectdock/objectdock.cpp \
    $$PWD/component/objectdock/objectcontainer.cpp \
    $$PWD/component/animationdock/framelistview.cpp \
    $$PWD/component/objectdock/objectlistview.cpp \
    $$PWD/dialogs/debugdialog.cpp \
    $$PWD/component/propertydock/widget/diredit.cpp \
    $$PWD/component/propertydock/propertymanager/dirpropertymanager.cpp \
    $$PWD/component/propertydock/editorfactory/direditorfactory.cpp \
    $$PWD/component/objectdock/subcontrolobjectlistview.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/widgets/qtcolorbutton.h \
    $$PWD/dialogs/aboutdialog.h \
    $$PWD/dialogs/abstractdialog.h \
    $$PWD/component/tabwidget/tabwidget.h \
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
    $$PWD/component/miniscenedock/miniscenedock.h \
    $$PWD/component/layerdock/layerdock.h \
    $$PWD/component/layerdock/layerview.h \
    $$PWD/widgets/zoomcombobox.h \
    $$PWD/dialogs/soundresourcedialog.h \
    $$PWD/component/propertydock/widget/pixmapedit.h \
    $$PWD/component/propertydock/widget/sounditemedit.h \
    $$PWD/component/propertydock/widget/sounditemsourceedit.h \
    $$PWD/component/propertydock/widget/soundsetedit.h \
    $$PWD/dialogs/loadingdialog.h \
    $$PWD/component/miniscenedock/minisceneframe.h \
    $$PWD/component/tilesetdock/tilesetdock.h \
    $$PWD/component/tilesetdock/tilesetview.h \
    $$PWD/component/tilesetdock/tilesettab.h \
    $$PWD/dialogs/selectrootdialog.h \
    $$PWD/component/characterdock/characterdock.h \
    $$PWD/component/characterdock/characterview.h \
    $$PWD/component/mapsdock/mapsdock.h \
    $$PWD/component/mapsdock/modstab/mapstab.h \
    $$PWD/component/mapsdock/mapsproxyview.h \
    $$PWD/component/mapsdock/modstab.h \
    $$PWD/component/mapsdock/modstree.h \
    $$PWD/component/mapsdock/modstab/mapview.h \
    $$PWD/component/layerdock/iconcheckdelegate.h \
    $$PWD/component/layerdock/boldcurrentitemdelegate.h \
    $$PWD/style/stylehelper.h \
    $$PWD/style/proxystyle.h \
    $$PWD/component/tabwidget/graphicsviewcontexmenu.h \
    $$PWD/dialogs/newmapdialog.h \
    $$PWD/widgets/flexiblescrollbar.h \
    $$PWD/dialogs/exceptiondialog.h \
    $$PWD/component/animationdock/animationdock.h \
    $$PWD/component/animationdock/animationlistview.h \
    $$PWD/component/animationdock/container.h \
    $$PWD/component/animationdock/framelistview.h \
    $$PWD/component/objectdock/objectdock.h \
    $$PWD/component/objectdock/objectcontainer.h \
    $$PWD/component/objectdock/objectlistview.h \
    $$PWD/dialogs/debugdialog.h \
    $$PWD/component/propertydock/widget/diredit.h \
    $$PWD/component/propertydock/propertymanager/dirpropertymanager.h \
    $$PWD/component/propertydock/editorfactory/direditorfactory.h \
    $$PWD/component/objectdock/subcontrolobjectlistview.h \
    $$PWD/component/tabwidget/graphicsview.h

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/dialogs/aboutdialog.ui \
    $$PWD/dialogs/preferencesdialog.ui \
    $$PWD/dialogs/soundresourcedialog.ui \
    $$PWD/dialogs/loadingdialog.ui \
    $$PWD/dialogs/selectrootdialog.ui \
    $$PWD/dialogs/newmapdialog.ui \
    $$PWD/dialogs/exceptiondialog.ui \
    $$PWD/dialogs/debugdialog.ui

RESOURCES += $$PWD/resource/editor.qrc

DISTFILES += \
    $$PWD/resource/images/Map.png

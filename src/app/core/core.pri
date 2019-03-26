QT += core widgets multimedia

SOURCES += \
    $$PWD/core.cpp \
    $$PWD/assets/cachedpixmap.cpp \
    $$PWD/assets/pixmap.cpp \
    $$PWD/assets/cachedsound.cpp \
    $$PWD/assets/sound.cpp \
    $$PWD/shared/filesystemwatcher.cpp \
    $$PWD/document/document.cpp \
    $$PWD/document/property/propertysheet.cpp \
    $$PWD/document/property/propertyitem.cpp \
    $$PWD/document/model/layersmodel.cpp \
    $$PWD/document/model/entity/layer.cpp \
    $$PWD/document/property/propertyobject.cpp \
    $$PWD/document/model/scenemodel.cpp \
    $$PWD/document/model/areasmodel.cpp \
    $$PWD/document/model/platformsmodel.cpp \
    $$PWD/document/model/dareasmodel.cpp \
    $$PWD/document/model/boxesmodel.cpp \
    $$PWD/document/model/wallsmodel.cpp \
    $$PWD/document/model/respawnsmodel.cpp \
    $$PWD/document/model/eventsmodel.cpp \
    $$PWD/document/model/triggersmodel.cpp \
    $$PWD/document/model/animationsmodel.cpp \
    $$PWD/document/model/entity/point.cpp \
    $$PWD/document/model/entity/area.cpp \
    $$PWD/document/model/entity/darea.cpp \
    $$PWD/document/model/entity/plat.cpp \
    $$PWD/document/model/entity/box.cpp \
    $$PWD/document/model/entity/wall.cpp \
    $$PWD/document/model/entity/tile.cpp \
    $$PWD/document/model/entity/respawn.cpp \
    $$PWD/document/model/entity/pointf.cpp \
    $$PWD/document/model/entity/rect.cpp \
    $$PWD/document/model/entity/trigger.cpp \
    $$PWD/assets/assetsmanager.cpp \
    $$PWD/assets/faceid.cpp \
    $$PWD/assets/tileset.cpp \
    $$PWD/assets/tileid.cpp \
    $$PWD/document/graphics/graphicsscene.cpp \
    $$PWD/document/graphics/hovereditem.cpp \
    $$PWD/document/graphics/selecteditem.cpp \
    $$PWD/document/model/entity/object.cpp \
    $$PWD/document/graphics/mousetraceitem.cpp \
    $$PWD/document/graphics/layeritem.cpp \
    $$PWD/document/graphics/sceneitem.cpp \
    $$PWD/document/graphics/tileitem.cpp \
    $$PWD/document/graphics/objectitem.cpp \
    $$PWD/document/graphics/selecteditems.cpp \
    $$PWD/document/undocommand/propertyundocommand.cpp \
    $$PWD/document/undocommand/layersundocommand.cpp \
    $$PWD/document/undocommand/objectundocommand.cpp \
    $$PWD/document/graphics/selectionrectangle.cpp \
    $$PWD/document/graphics/tools/abstracttool.cpp

HEADERS  += \
    $$PWD/core.h \
    $$PWD/assets/cachedpixmap.h \
    $$PWD/assets/pixmap.h \
    $$PWD/assets/cachedsound.h \
    $$PWD/assets/sound.h \
    $$PWD/shared/filesystemwatcher.h \
    $$PWD/document/document.h \
    $$PWD/document/property/property.h \
    $$PWD/document/property/propertysheet.h \
    $$PWD/document/property/propertyitem.h \
    $$PWD/document/model/layersmodel.h \
    $$PWD/document/model/entity/layer.h \
    $$PWD/document/property/propertyobject.h \
    $$PWD/document/model/scenemodel.h \
    $$PWD/document/base/io.h \
    $$PWD/document/model/areasmodel.h \
    $$PWD/document/model/platformsmodel.h \
    $$PWD/document/model/dareasmodel.h \
    $$PWD/document/model/boxesmodel.h \
    $$PWD/document/model/wallsmodel.h \
    $$PWD/document/model/respawnsmodel.h \
    $$PWD/document/model/eventsmodel.h \
    $$PWD/document/model/triggersmodel.h \
    $$PWD/document/model/animationsmodel.h \
    $$PWD/document/model/entity/point.h \
    $$PWD/document/model/entity/area.h \
    $$PWD/document/model/entity/darea.h \
    $$PWD/document/model/entity/plat.h \
    $$PWD/document/model/entity/box.h \
    $$PWD/document/base/tr.h \
    $$PWD/document/model/entity/wall.h \
    $$PWD/document/model/entity/tile.h \
    $$PWD/document/model/entity/respawn.h \
    $$PWD/document/model/entity/pointf.h \
    $$PWD/document/model/entity/rect.h \
    $$PWD/document/model/entity/trigger.h \
    $$PWD/assets/assetsmanager.h \
    $$PWD/assets/faceid.h \
    $$PWD/assets/tileset.h \
    $$PWD/assets/tileid.h \
    $$PWD/document/graphics/hovereditem.h \
    $$PWD/document/graphics/selecteditem.h \
    $$PWD/document/model/entity/object.h \
    $$PWD/document/graphics/graphicsscene.h \
    $$PWD/document/graphics/mousetraceitem.h \
    $$PWD/document/graphics/layeritem.h \
    $$PWD/document/graphics/sceneitem.h \
    $$PWD/document/graphics/tileitem.h \
    $$PWD/document/graphics/objectitem.h \
    $$PWD/document/graphics/selecteditems.h \
    $$PWD/document/undocommand/propertyundocommand.h \
    $$PWD/document/undocommand/layersundocommand.h \
    $$PWD/document/undocommand/objectundocommand.h \
    $$PWD/document/base/finddoc.h \
    $$PWD/document/graphics/selectionrectangle.h \
    $$PWD/document/graphics/tools/abstracttool.h \
    $$PWD/assets/interface.h

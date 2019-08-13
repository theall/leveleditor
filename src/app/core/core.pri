QT += core widgets gui multimedia

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
    $$PWD/document/property/propertyobject.cpp \
    $$PWD/document/model/scenemodel.cpp \
    $$PWD/document/model/areamodel.cpp \
    $$PWD/document/model/dareamodel.cpp \
    $$PWD/document/model/boxmodel.cpp \
    $$PWD/document/model/wallmodel.cpp \
    $$PWD/document/model/respawnmodel.cpp \
    $$PWD/document/model/eventmodel.cpp \
    $$PWD/document/model/triggermodel.cpp \
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
    $$PWD/document/graphics/uiitem/hovereditem.cpp \
    $$PWD/document/graphics/uiitem/selecteditem.cpp \
    $$PWD/document/model/entity/object.cpp \
    $$PWD/document/graphics/uiitem/mousetraceitem.cpp \
    $$PWD/document/graphics/sceneitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/tileitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/objectitem.cpp \
    $$PWD/document/graphics/uiitem/selecteditems.cpp \
    $$PWD/document/undocommand/propertyundocommand.cpp \
    $$PWD/document/graphics/uiitem/selectionrectangle.cpp \
    $$PWD/document/graphics/tools/abstracttool.cpp \
    $$PWD/model/tilesetmodel.cpp \
    $$PWD/document/graphics/layeritem/objectitem/areaitem.cpp \
    $$PWD/document/graphics/layeritem/tilelayeritem.cpp \
    $$PWD/document/graphics/layeritem/layeritem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/startpointitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/randomregionitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/dooritem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/trackitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/dareaitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/boxitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/platitem.cpp \
    $$PWD/model/mapmodel.cpp \
    $$PWD/model/charactermodel.cpp \
    $$PWD/assets/maps.cpp \
    $$PWD/document/graphics/layeritem/objectitem/wallitem.cpp \
    $$PWD/document/model/entity/enemy.cpp \
    $$PWD/document/model/entity/enemyfactory.cpp \
    $$PWD/document/model/entity/animation.cpp \
    $$PWD/document/model/entity/frame.cpp \
    $$PWD/document/model/enemyfactorymodel.cpp \
    $$PWD/document/model/basemodel.cpp \
    $$PWD/document/model/tilelayermodel.cpp \
    $$PWD/document/graphics/layeritem/arealayeritem.cpp \
    $$PWD/document/graphics/layeritem/boxlayeritem.cpp \
    $$PWD/document/graphics/layeritem/darealayeritem.cpp \
    $$PWD/document/graphics/layeritem/platlayeritem.cpp \
    $$PWD/document/graphics/layeritem/walllayeritem.cpp \
    $$PWD/document/graphics/layeritem/objectlayeritem.cpp \
    $$PWD/document/undocommand/objectaddcommand.cpp \
    $$PWD/document/undocommand/objectmovecommand.cpp \
    $$PWD/document/graphics/uiitem/tilestampitem.cpp \
    $$PWD/document/undocommand/removeselectioncommand.cpp \
    $$PWD/document/graphics/uiitem/objectareaitem.cpp \
    $$PWD/document/graphics/uiitem/darkmaskitem.cpp \
    $$PWD/document/graphics/uiitem/uiitemsgroup.cpp \
    $$PWD/document/model/animationmodel.cpp \
    $$PWD/document/model/platmodel.cpp \
    $$PWD/document/graphics/cameraitem.cpp \
    $$PWD/document/model/framemodel.cpp \
    $$PWD/document/graphics/layeritem/enemyfactoryitem.cpp \
    $$PWD/document/graphics/layeritem/objectitem/enemyitem.cpp

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
    $$PWD/document/property/propertyobject.h \
    $$PWD/document/model/scenemodel.h \
    $$PWD/document/base/io.h \
    $$PWD/document/model/areamodel.h \
    $$PWD/document/model/dareamodel.h \
    $$PWD/document/model/boxmodel.h \
    $$PWD/document/model/wallmodel.h \
    $$PWD/document/model/respawnmodel.h \
    $$PWD/document/model/eventmodel.h \
    $$PWD/document/model/triggermodel.h \
    $$PWD/document/model/animationmodel.h \
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
    $$PWD/document/graphics/uiitem/hovereditem.h \
    $$PWD/document/graphics/uiitem/selecteditem.h \
    $$PWD/document/model/entity/object.h \
    $$PWD/document/graphics/graphicsscene.h \
    $$PWD/document/graphics/uiitem/mousetraceitem.h \
    $$PWD/document/graphics/sceneitem.h \
    $$PWD/document/graphics/layeritem/objectitem/tileitem.h \
    $$PWD/document/graphics/layeritem/objectitem/objectitem.h \
    $$PWD/document/graphics/uiitem/selecteditems.h \
    $$PWD/document/undocommand/propertyundocommand.h \
    $$PWD/document/base/finddoc.h \
    $$PWD/document/graphics/uiitem/selectionrectangle.h \
    $$PWD/document/graphics/tools/abstracttool.h \
    $$PWD/assets/interface.h \
    $$PWD/model/tilesetmodel.h \
    $$PWD/document/graphics/layeritem/objectitem/areaitem.h \
    $$PWD/document/graphics/layeritem/tilelayeritem.h \
    $$PWD/document/graphics/layeritem/layeritem.h \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/startpointitem.h \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/randomregionitem.h \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/dooritem.h \
    $$PWD/document/graphics/layeritem/objectitem/tileitem/trackitem.h \
    $$PWD/document/graphics/layeritem/objectitem/dareaitem.h \
    $$PWD/document/graphics/layeritem/objectitem/boxitem.h \
    $$PWD/document/graphics/layeritem/objectitem/platitem.h \
    $$PWD/model/mapmodel.h \
    $$PWD/model/charactermodel.h \
    $$PWD/assets/maps.h \
    $$PWD/document/graphics/layeritem/objectitem/wallitem.h \
    $$PWD/document/model/entity/enemy.h \
    $$PWD/document/model/entity/enemyfactory.h \
    $$PWD/document/model/entity/animation.h \
    $$PWD/document/model/entity/frame.h \
    $$PWD/document/model/enemyfactorymodel.h \
    $$PWD/document/model/basemodel.h \
    $$PWD/document/model/tilelayermodel.h \
    $$PWD/document/graphics/layeritem/arealayeritem.h \
    $$PWD/document/graphics/layeritem/boxlayeritem.h \
    $$PWD/document/graphics/layeritem/darealayeritem.h \
    $$PWD/document/graphics/layeritem/platlayeritem.h \
    $$PWD/document/graphics/layeritem/walllayeritem.h \
    $$PWD/document/graphics/layeritem/objectlayeritem.h \
    $$PWD/document/undocommand/objectmovecommand.h \
    $$PWD/document/undocommand/objectaddcommand.h \
    $$PWD/document/graphics/uiitem/tilestampitem.h \
    $$PWD/document/undocommand/removeselectioncommand.h \
    $$PWD/document/graphics/uiitem/objectareaitem.h \
    $$PWD/document/graphics/uiitem/darkmaskitem.h \
    $$PWD/document/model/objectgeneric.hpp \
    $$PWD/document/graphics/uiitem/uiitemsgroup.h \
    $$PWD/document/model/platmodel.h \
    $$PWD/document/graphics/cameraitem.h \
    $$PWD/document/model/framemodel.h \
    $$PWD/document/graphics/layeritem/enemyfactoryitem.h \
    $$PWD/document/graphics/layeritem/objectitem/enemyitem.h

RESOURCES += \
    $$PWD/resource/core.qrc

TARGET = RightHand
QT += widgets
DEFINES += __EMSCRIPTEN__ 
LIBS +=-lidbfs.js 
#INCLUDEPATH +=/SDK/emsdk/fastcomp/emscripten/system/include/

HEADERS       = \
    mainwindow.h
SOURCES       = \
                main.cpp \
    mainwindow.cpp


qtConfig(thread): SUBDIRS += widgets_mandelbrot
qtHaveModule(mqtt):qtHaveModule(websockets): SUBDIRS += mqtt_simpleclient

FORMS += \
    mainwindow.ui

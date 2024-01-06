QT += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
ICON = image/app_icon.png
TARGET = 3DViewer_v2.0

SOURCES += \
    ../model/parser/file_parser.cc \
    ../model/transform/transform.cc \
    OpenGL_widget.cc \
    main.cc \
    viewer.cc

HEADERS += \
    ../controller/3d_viewer_controller.h \
    ../model/parser/file_parser.h \
    ../model/transform/transform.h \
    OpenGL_widget.h \
    ./include/gif.h \
    viewer.h

FORMS += \
    viewer.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

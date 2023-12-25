QT += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
ICON = app_icon.png
TARGET = 3DViewer_v2.0

SOURCES += \
    ../model/parser/file_parser.cc \
    OpenGL_widget.cc \
    main.cc \
    viewer.cc

HEADERS += \
    ../model/parser/file_parser.h \
    OpenGL_widget.h \
    viewer.h

FORMS += \
    viewer.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

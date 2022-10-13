QT  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += GL_SILENCE_DEPRECATION

SOURCES += \
    controller/controller.cc \
    main.cc \
    model/cave/model_cave.cc \
    model/helpers/matrix.cc \
    model/helpers/parser.cc \
    model/maze/model_maze.cc \
    model/model_facade.cc \
    view/view.cc

HEADERS += \
    controller/controller.h \
    model/cave/model_cave.h \
    model/helpers/matrix.h \
    model/helpers/parser.h \
    model/maze/model_maze.h \
    model/model_facade.h \
    view/view.h
    
FORMS += \
    view/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


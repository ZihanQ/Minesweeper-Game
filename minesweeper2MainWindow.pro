QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    look_item.cpp \
    main.cpp \
    mainwindow.cpp \
    mine_item.cpp \
    mine_scene.cpp \
    mineshow_scene.cpp \
    minewindow.cpp \
    num_item.cpp \
    num_scene.cpp \
    selfinputmain.cpp \
    time_scene.cpp

HEADERS += \
    look_item.h \
    mainwindow.h \
    mine_item.h \
    mine_scene.h \
    mineshow_scene.h \
    minewindow.h \
    num_item.h \
    num_scene.h \
    selfinputmain.h \
    time_scene.h

FORMS += \
    mainwindow.ui \
    minewindow.ui \
    selfinputmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    image/a2.jpg

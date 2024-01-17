QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/levelsavecontroller.cpp \
    Views/graphicsbasedworld.cpp \
    Views/viewerenemy.cpp \
    Views/viewerhealthpack.cpp \
    Views/viewerpenemies.cpp \
    Views/viewerprotagonist.cpp \
    Views/viewers.cpp \
    Views/viewerxenemies.cpp \
    Views/views.cpp \
    algorithm/algorithm.cpp \
    algorithm/astarbestpath.cpp \
    algorithm/node.cpp \
    algorithm/astar.cpp \
    Commands/attacknearestenemycommand.cpp \
    Commands/downcommand.cpp \
    Commands/gotoxycommand.cpp \
    Commands/leftcommand.cpp \
    Commands/rightcommand.cpp \
    Commands/takenearesthealthpackcommand.cpp \
    Commands/upcommand.cpp \
    Commands/commandlistener.cpp \
    Controllers/enemycontroller.cpp \
    Controllers/healthpackcontroller.cpp \
    Controllers/logiccontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    Controllers/protagonistcontroller.cpp \
    Controllers/worldcontroller.cpp \
    Views/textbasedview.cpp \
    xenemy.cpp

HEADERS += \
    Controllers/levelsavecontroller.h \
    Views/graphicsbasedworld.h \
    Views/viewerenemy.h \
    Views/viewerhealthpack.h \
    Views/viewerpenemies.h \
    Views/viewerprotagonist.h \
    Views/viewers.h \
    Views/viewerxenemies.h \
    Views/views.h \
    algorithm/algorithm.h \
    algorithm/astarbestpath.h \
    algorithm/node.h \
    algorithm/astar.h \
    Commands/commandlist.h \
    Commands/attacknearestenemycommand.h \
    Commands/downcommand.h \
    Commands/gotoxycommand.h \
    Commands/leftcommand.h \
    Commands/rightcommand.h \
    Commands/takenearesthealthpackcommand.h \
    Commands/upcommand.h \
    Commands/commandlistener.h \
    Controllers/enemycontroller.h \
    Controllers/healthpackcontroller.h \
    Controllers/logiccontroller.h \
    mainwindow.h \
    Controllers/protagonistcontroller.h \
    Controllers/worldcontroller.h \
    Views/textbasedview.h \
    world_images/worldmaps.h \
    xenemy.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/world_v5/ -lworld

INCLUDEPATH += $$PWD/world_v5
DEPENDPATH += $$PWD/world_v5

DISTFILES +=

RESOURCES += \
    sprites.qrc \
    world.qrc

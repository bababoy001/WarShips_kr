QT       += core gui \
multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bot.cpp \
    BotLvl2.cpp \
    BotLvl3.cpp \
    Button.cpp \
    Cell.cpp \
    Game.cpp \
    main.cpp

HEADERS += \
    Bot.h \
    BotLvl2.h \
    BotLvl3.h \
    Button.h \
    Cell.h \
    Game.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

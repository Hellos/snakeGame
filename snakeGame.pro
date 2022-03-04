TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        fruit.cpp \
        game.cpp \
        main.cpp \
        object.cpp \
        snake.cpp


LIBS += -L C:\SDL\x86_64-w64-mingw32\lib \
-lmingw32 \
-lSDL2main \
-lSDL2 \
-lSDL2_image \
-lSDL2_ttf

INCLUDEPATH += C:\SDL\x86_64-w64-mingw32\include\SDL2

HEADERS += \
    consts.h \
    fruit.h \
    game.h \
    object.h \
    snake.h


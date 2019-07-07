INCLUDEPATH += "$$PWD\..\..\thirdpaty\sfml\include"
INCLUDEPATH ~= s,/,\\,g

DEPENDPATH += "$$PWD\..\..\thirdpaty\sfml\include"
DEPENDPATH ~= s,/,\\,g


#if x32 compiler
contains(QT_ARCH, i386) {
    LIBS += -L"$$PWD\..\..\thirdpaty\sfml\lib\mingw32"   
} else {
    LIBS += -L"$$PWD\..\..\thirdpaty\sfml\lib\mingw64"
}

LIBS ~= s,/,\\,g
CONFIG(release, debug | release) : {
    LIBS += \
        -llibsfml-main \
        -lsfml-system \
        -lsfml-window
    LIBS ~= s,/,\\,g
}

CONFIG(debug, debug | release) : {
    LIBS += \
        -llibsfml-main-d \
        -lsfml-system-d \
        -lsfml-window-d
    LIBS ~= s,/,\\,g
}

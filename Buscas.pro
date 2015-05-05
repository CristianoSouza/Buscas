TEMPLATE = app

QT += qml quick widgets

SOURCES += Aresta.cpp \
    Grafo.cpp \
    main.cpp \
    interface.cpp \
    Vertice.cpp \
    Dfs.cpp \
    Bfs.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Grafo.h \
    Vertice.h \
    interface.h \
    Aresta.h \
    Dfs.h \
    Bfs.h


FORMS += \
    interface.ui

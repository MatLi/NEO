QMAKE_LFLAGS += -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++
QMAKE_INCDIR += ../Node \ 
  ../Edge \
  ../Set \
  ../Network
QMAKE_CXXFLAGS += -std=c++11 -Wextra -pedantic

HEADERS += \
    ../mainwindow.h \
    ../graphwidget.h \
    ../graphicnode.h \
    ../graphicedge.h \
    ../neopushbutton.h \
    ../datadock.h \
    ../addedgedock.h \
    ../cheapest_path_dialog.h \
    ../solution_dialog.h \
    ../Edge/Edge.h \
    ../Node/Node.h \
    ../Set/Set.h \
    ../Network/Network.h 

SOURCES += \
    ../mainwindow.cpp \
    ../main.cpp \
    ../datadock.cpp \
    ../addedgedock.cpp \
    ../graphwidget.cpp \
    ../graphicnode.cpp \
    ../graphicedge.cpp \
    ../neopushbutton.cpp \
    ../cheapest_path_dialog.cpp \
    ../solution_dialog.cpp \
    ../Edge/Edge.cc \
    ../Node/Node.cc \
    ../Network/Network.cc 

FORMS += \
    ../mainwindow.ui

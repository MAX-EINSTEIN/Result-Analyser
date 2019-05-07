#-------------------------------------------------
#
# Project created by QtCreator 2019-02-11T21:26:31
#
#-------------------------------------------------

QT       += core gui printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quick

TARGET = Result_Analyser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Utils/pythread.cpp \
    View/mainview.cpp \
    View/loginwindow.cpp \
    View/classes.cpp \
    Model/settings.cpp \
    Controller/settings_manager.cpp \
    View/settings_dialog.cpp \
    Utils/singleton_factory.cpp \
    View/themewidget.cpp \
    main.cpp


HEADERS += \
    Utils/pyhelper.hpp \
    Utils/pythread.h \
    View/mainview.h \
    View/loginwindow.h \
    View/classes.h \
    Model/settings.h \
    Controller/settings_manager.h \
    View/settings_dialog.h \
    Utils/dataanalyser.hpp \
    Utils/settings_data.hpp \
    Utils/singleton_factory.hpp \
    View/themewidget.h


FORMS += \
    View/mainview.ui \
    View/loginwindow.ui \
    View/classes.ui \
    View/settings_dialog.ui \
    View/themewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#INCLUDEPATH += $$PWD/3rdparty/pybind11

DISTFILES += \
    Files/ResultTab.qml \
    pyemb3.py

win32:CONFIG(release, debug|release): LIBS += -LC:/Users/HP.LAP/AppData/Local/Programs/Python/Python37-32/libs/ -lpython37
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Users/HP.LAP/AppData/Local/Programs/Python/Python37-32/libs/ -lpython37
else:unix: LIBS += -LC:/Users/HP.LAP/AppData/Local/Programs/Python/Python37-32/libs/ -lpython37

INCLUDEPATH += C:/Users/HP.LAP/AppData/Local/Programs/Python/Python37-32/include
INCLUDEPATH += C:/Users/HP.LAP/AppData/Local/Programs/Python/Python37-32/libs
DEPENDPATH += C:/Users/HP.LAP/AppData/Local/Programs/Python/Python37-32/libs

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

CONFIG += c++17


# Set environment values for Qxlnt. You may use default values.

msvc:DEFINES+=XLNT_IMPORT

include(3rdparty/Qxlnt/Qxlnt/Qxlnt.pri)
INCLUDEPATH += 3rdparty/Qxlnt/xlnt/include/

msvc{
# message('Visual C++ EXE TYPE')
CONFIG(debug, debug|release) {
QMAKE_POST_LINK += copy 3rdparty/Qxlnt/Qxlnt/Qxlnt.dll .\debug\
QMAKE_POST_LINK += copy 3rdparty/Qxlnt/Qxlnt/Qxlnt.lib .\debug\
LIBS+= .\debug/Qxlnt.lib
} else {
LIBS+= .\release/Qxlnt.lib
QMAKE_POST_LINK += copy 3rdparty/Qxlnt/Qxlnt/release/Qxlnt.dll .\release\
}
}



SOURCES += \
    Controller/application_manager.cpp \
    Model/sheetdatatablemodel.cpp \
    Utils/exceltool.cpp \
    View/chartwidget.cpp \
    View/dataanalysisdialog.cpp \
    View/mainview.cpp \
    View/loginwindow.cpp \
    View/classes.cpp \
    Model/settings.cpp \
    View/settings_dialog.cpp \
    main.cpp


HEADERS += \
    Controller/application_manager.hpp \
    Model/settings.hpp \
    Model/settings_data.hpp \
    Model/sheetdatatablemodel.hpp \
    Utils/exceltool.hpp \
    View/chartwidget.hpp \
    View/classes.hpp \
    View/dataanalysisdialog.hpp \
    View/loginwindow.hpp \
    View/mainview.hpp \
    Utils/settings_data.hpp \
    Utils/singleton_factory.hpp \
    View/settingsdialog.hpp


FORMS += \
    View/chartwidget.ui \
    View/dataanalysisdialog.ui \
    View/mainview.ui \
    View/loginwindow.ui \
    View/classes.ui \
    View/settings_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Files/ResultTab.qml



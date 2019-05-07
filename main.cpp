#include <QApplication>
#include "Controller/settings_manager.h"
#include <Utils/pythread.h>

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    Settings_Manager Launcher;
    Launcher.StartProgram();

    return app.exec();
}

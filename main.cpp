#include <QApplication>
#include "Controller/settings_manager.hpp"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    Settings_Manager Launcher;
    Launcher.startProgram();

    return app.exec();
}

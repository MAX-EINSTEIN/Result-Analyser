#include <QApplication>
#include "Controller/application_manager.hpp"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    Application_Manager Launcher;
    Launcher.startProgram();

    return app.exec();
}

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <vector>
#include <string>
#include "View/classes.hpp"
#include "View/settingsdialog.hpp"
#include "View/dataanalysisdialog.hpp"
#include "Utils/exceltool.hpp"

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView();

    void setSidebar(Classes *sidebar);

    void setCentralView();

    void setMaxStreams(size_t maxStreams);

    void setMaxSubjects(int maxSubjects);

    void setSettings(Settings_Dialog *settings);

    void setSplitter(std::vector<std::string> streamslist, std::vector<std::string> subjectslist);

    void setDataAnalysisScreen(DataAnalysisDialog *dataAnalysisScreen);

public slots:
    void newFile();
    void openFile();
    void closeFile();
    void exit();
    void print();
    void undo();
    void redo();
    void openSettings();
    void visitHomeView();
    void visitStudentsView();
    void visitScoresView();
    void visitResultsView();
    void visitPerformanceReport();
    void logIn();
    void logOut();

signals:
    std::string fileOpened(std::string filename);
private:
    Ui::MainView *ui;
    Classes * _sidebar;
    Settings_Dialog * _settings;
    DataAnalysisDialog* _dataAnalysisScreen;
    size_t streamsCount;
    int subjectsCount;
    QString _filename;
    bool _loginStatus;
};


#endif // MAINVIEW_H


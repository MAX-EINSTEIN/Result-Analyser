#include "View/mainview.h"
#include "View/themewidget.h"
#include "ui_mainview.h"
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDebug>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    _settings(nullptr)
{
    ui->setupUi(this);

    if(!centralWidget())
    QMainWindow::setCentralWidget(ui->dw_Central);

    ui->s_subject->setFixedWidth(ui->dw_Central->maximumWidth());

    QString menuStyle = "QMenuBar::item:selected { background: white; } QMenuBar::item:pressed {  background: rgb(194, 138, 254); }";
    ui->menuBar->setStyleSheet(menuStyle);

    QString actionStyle = "QToolButton:hover {color : rgb(194, 138, 254); }";
    this->setStyleSheet(actionStyle);  

    QQuickView *view = new QQuickView();
    view->setSource(QUrl("qrc:/qml/Files/HomeTab.qml"));
    auto home_tab_context = view->rootContext();
    home_tab_context->setContextProperty("MainView",this);
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    ui->verticalLayout_3->addWidget(container);

    QQuickView *result = new QQuickView();
    result->setSource(QUrl("qrc:/qml/Files/ResultTab.qml"));
    auto result_tab_context = result->rootContext();
    result_tab_context->setContextProperty("MainView",this);
    QWidget * r_container = QWidget::createWindowContainer(result,this);
    r_container->setFocusPolicy(Qt::TabFocus);
    ui->horizontalLayout_3->addWidget(r_container);

    ThemeWidget *widget = new ThemeWidget();
    ui->horizontalLayout->addWidget(widget);

    ui->tw_Students->setTabEnabled(0,true);
    ui->tw_Students->setTabEnabled(1,true);
    ui->tw_Students->setTabEnabled(2,true);
    ui->tw_Students->setTabEnabled(3,true);
    ui->tw_Students->setTabEnabled(4,true);

    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(openSettings()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->actionPrint, SIGNAL(triggered()), this, SLOT(print()));
    connect(ui->actionHome, SIGNAL(triggered()), this, SLOT(VisitHomeView()));
    connect(ui->actionStudents, SIGNAL(triggered()), this, SLOT(VisitStudentsView()));
    connect(ui->actionScores, SIGNAL(triggered()), this, SLOT(VisitScoresView()));
    connect(ui->actionResults, SIGNAL(triggered()),this, SLOT(VisitResultsView()));
}

MainView::~MainView()
{
    delete ui;
}

void MainView::setSidebar(Classes *sidebar)
{
    _sidebar = sidebar;
    ui->lo_Classes->addWidget(_sidebar);
}

void MainView::setCentralView()
{

}


void MainView::setMaxStreams(size_t maxStreams)
{
    streamsCount = maxStreams;
}

void MainView::setMaxSubjects(int maxSubjects)
{
    subjectsCount = maxSubjects;
}


void MainView::setSplitter(std::vector<std::string> streamslist,std::vector<std::string> subjectslist)
{
    for(size_t i=0;i<streamslist.size();i++)
    {
        ui->cb_Stream->addItem(streamslist[i].c_str());
    }
    for(size_t i=0;i<subjectslist.size();i++)
    {
        ui->cb_Subjects->addItem(subjectslist[i].c_str());
    }
}


void MainView::newFile()
{

}

void MainView::openFile()
{
    _filename = QFileDialog::getOpenFileName(this,"Choose a excel document",QDir::homePath(),"Old Excel Files (*.xls) ;;  New Excel Files(*.xlsl)");
    fileOpened(_filename.toStdString());
}

void MainView::closeFile()
{

}

void MainView::exit()
{
    this->close();
}

void MainView::print()
{
    QPrinter printer;
    printer.setPrinterName("Choose Desired Printing Options");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    //ui->textEdit->print(&printer);
}

void MainView::Undo()
{

}

void MainView::Redo()
{

}


void MainView::openSettings()
{
    if(_settings != nullptr)
    {
        _settings->show();
    }
}

void MainView::VisitHomeView()
{
    ui->tw_Students->setCurrentIndex(0);
}

void MainView::VisitStudentsView()
{
    ui->tw_Students->setCurrentIndex(1);
}

void MainView::VisitScoresView()
{
    ui->tw_Students->setCurrentIndex(2);
}

void MainView::VisitResultsView()
{
    ui->tw_Students->setCurrentIndex(3);
}

void MainView::visitPerformanceReport()
{
    ui->tw_Students->setCurrentIndex(4);
}

void MainView::logIn()
{
    _loginStatus = true;
}

void MainView::logOut()
{
    _loginStatus = false;
}

void MainView::setSettings(Settings_Dialog *settings)
{
    _settings = settings;
}



#include "ui_mainview.h"
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QtDebug>
#include "View/mainview.hpp"
#include "View/chartwidget.hpp"
#include "Model/sheetdatatablemodel.hpp"

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

    ChartWidget *widget = new ChartWidget();
    ui->horizontalLayout->addWidget(widget);

    ui->tw_Students->setTabEnabled(0,true);
    ui->tw_Students->setTabEnabled(1,false);
    ui->tw_Students->setTabEnabled(2,false);
    ui->tw_Students->setTabEnabled(3,false);
    ui->tw_Students->setTabEnabled(4,true);
    visitHomeView();

    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(openSettings()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));
    connect(ui->actionPrint, SIGNAL(triggered()), this, SLOT(print()));
    connect(ui->actionHome, SIGNAL(triggered()), this, SLOT(visitHomeView()));
    connect(ui->actionStudents, SIGNAL(triggered()), this, SLOT(visitStudentsView()));
    connect(ui->actionScores, SIGNAL(triggered()), this, SLOT(visitScoresView()));
    connect(ui->actionResults, SIGNAL(triggered()),this, SLOT(visitResultsView()));
}

MainView::~MainView()
{
    delete ui;
    delete _sidebar;
    delete _settings;
    delete _dataAnalysisScreen;
}

void MainView::setSidebar(Classes *sidebar)
{
    _sidebar = sidebar;
    ui->lo_Classes->addWidget(_sidebar);
}

void MainView::newFile()
{

}

void MainView::openFile()
{
    // Prompt for choosing an excel file
    // [Only excel files from MS excel 2007 onwards are supported]
    _filename = QFileDialog::getOpenFileName(this,"Choose an excel document",QDir::homePath(),"Excel Files(*.xlsx)");
    qDebug(_filename.toStdString().c_str());

    // Enabling tabs and setting current tab to scores tab
    ui->tw_Students->setTabEnabled(1,true);
    ui->tw_Students->setTabEnabled(2,true);
    ui->tw_Students->setTabEnabled(3,true);
    ui->tw_Students->setTabEnabled(4,true);
    visitScoresView();

    SheetData list = ExcelTool::read(_filename.toStdString());
    FieldList fields = ExcelTool::readHeaders(_filename.toStdString());
    _dataAnalysisScreen = new DataAnalysisDialog(this, fields);
    _dataAnalysisScreen->show();

    // Setting up the table view with the model
    SheetDataTableModel *model = new SheetDataTableModel(this, std::make_unique<SheetData>(list));
    ui->tv_scores->verticalHeader()->hide();
    ui->tv_scores->setModel(model);
}

void MainView::closeFile()
{
    // Remove all rows and columns from table view
    ui->tv_scores->clearSpans();
    ui->tv_scores->setModel(nullptr);

    // Disable tabs and got to HomeView
    ui->tw_Students->setTabEnabled(1,false);
    ui->tw_Students->setTabEnabled(2,false);
    ui->tw_Students->setTabEnabled(3,false);
    visitHomeView();
}

void MainView::exit()
{
    this->close();
    this->~MainView();
}

void MainView::print()
{
    QPrinter printer;
    printer.setPrinterName("Choose Desired Printing Options");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    //ui->textEdit->print(&printer);
}

void MainView::undo()
{

}

void MainView::redo()
{

}


void MainView::openSettings()
{
    if(_settings != nullptr){
        _settings->show();
    }
}

void MainView::visitHomeView()
{
    ui->tw_Students->setCurrentIndex(0);
}

void MainView::visitStudentsView()
{
    ui->tw_Students->setCurrentIndex(1);
}

void MainView::visitScoresView()
{
    ui->tw_Students->setCurrentIndex(2);
}

void MainView::visitResultsView()
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



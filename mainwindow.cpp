#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Projects Manager");
    projectsWindow = new ProjectsWindow;

    connect(ui->projectsWindowButton, SIGNAL(clicked()), this, SLOT(openProjectsWindow()));
    connect(projectsWindow, SIGNAL(openMainMenu()), this, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openProjectsWindow()
{
    hide();
    projectsWindow->show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    projectsWindow = new ProjectsWindow;

    connect(ui->projectsWindowButton, SIGNAL(clicked()), this, SLOT(openProjectsWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openProjectsWindow()
{
    projectsWindow->show();
}

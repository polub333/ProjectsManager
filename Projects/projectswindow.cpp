#include "projectswindow.h"
#include "ui_projectswindow.h"

ProjectsWindow::ProjectsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsWindow)
{
    ui->setupUi(this);
}

ProjectsWindow::~ProjectsWindow()
{
    delete ui;
}

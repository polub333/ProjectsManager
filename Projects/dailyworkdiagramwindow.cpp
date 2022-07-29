#include "dailyworkdiagramwindow.h"
#include "ui_dailyworkdiagramwindow.h"

DailyWorkDiagramWindow::DailyWorkDiagramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyWorkDiagramWindow)
{
    ui->setupUi(this);

    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT([this](){this->hide;}));
}

DailyWorkDiagramWindow::~DailyWorkDiagramWindow()
{
    delete ui;
}

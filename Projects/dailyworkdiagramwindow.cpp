#include "dailyworkdiagramwindow.h"
#include "ui_dailyworkdiagramwindow.h"

DailyWorkDiagramWindow::DailyWorkDiagramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyWorkDiagramWindow)
{
    ui->setupUi(this);

    connect(ui->exitButton, &QPushButton::clicked, this, [this](){this->hide();});
}

DailyWorkDiagramWindow::~DailyWorkDiagramWindow()
{
    delete ui;
}

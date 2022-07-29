#include "burndowndiagramwindow.h"
#include "ui_burndowndiagramwindow.h"

BurnDownDiagramWindow::BurnDownDiagramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BurnDownDiagramWindow)
{
    ui->setupUi(this);
}

BurnDownDiagramWindow::~BurnDownDiagramWindow()
{
    delete ui;
}

#include "burndowndiagramwindow.h"
#include "ui_burndowndiagramwindow.h"

BurnDownDiagramWindow::BurnDownDiagramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BurnDownDiagramWindow)
{
    ui->setupUi(this);

    connect(ui->exitButton, &QPushButton::clicked, this, [this](){this->hide();});
}

BurnDownDiagramWindow::~BurnDownDiagramWindow()
{
    delete ui;
}

void BurnDownDiagramWindow::addEntry(const Entry& entry)
{
    entries.push_back(entry);
}

void BurnDownDiagramWindow::setStartDate(const QDate& _startDate)
{
    startDate = _startDate;
}

void BurnDownDiagramWindow::setEndDate(const QDate& _endDate)
{
    endDate = _endDate;
}

void BurnDownDiagramWindow::setWorkAmount(const int& _workAmount)
{
    workAmount = _workAmount;
}

void BurnDownDiagramWindow::draw()
{
    drawBurnDownLine();
    drawPercentLines();
    drawDateLines();
    drawEntries();
}

void BurnDownDiagramWindow::drawBurnDownLine()
{

}

void BurnDownDiagramWindow::drawPercentLines()
{

}

void BurnDownDiagramWindow::drawDateLines()
{

}

void BurnDownDiagramWindow::drawEntries()
{

}

#include "dailyworkdiagramwindow.h"
#include "ui_dailyworkdiagramwindow.h"

DailyWorkDiagramWindow::DailyWorkDiagramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyWorkDiagramWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    pixelPerDay = 35;
    pixelPerGap = 3;
    sceneHeight = 380 - 25;
    columnsColor = QColor(175, 238, 238);
    linesColor = QColor(192, 192, 192);

    connect(ui->exitButton, &QPushButton::clicked, this, [this](){this->hide();});
}

DailyWorkDiagramWindow::~DailyWorkDiagramWindow()
{
    delete ui;
}

void DailyWorkDiagramWindow::draw()
{
    sceneWidth = calculateSceneWidth();
    maxWorkAmount = findMaxWorkAmount();

    ui->graphicsView->setSceneRect(-sceneWidth / 2, -sceneHeight / 2,
                                   sceneWidth, sceneHeight);

    for(auto it = entries.begin(); it != entries.end(); ++it){
        drawEntry(it);
    }
    drawPercentLines();
}

int DailyWorkDiagramWindow::calculateSceneWidth() const
{
    QDateTime startDateTime, endDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    int duration = startDateTime.daysTo(endDateTime) + 1;
    int _sceneWidth = duration * pixelPerDay;
    return _sceneWidth;
}

int DailyWorkDiagramWindow::findMaxWorkAmount() const
{
    int _maxWorkAmount = 0;
    for(auto it = entries.begin(); it != entries.end(); ++it){
        if((*it).getWorkAmount() > _maxWorkAmount){
            _maxWorkAmount = (*it).getWorkAmount();
        }
    }
    return _maxWorkAmount;
}

void DailyWorkDiagramWindow::drawEntry(const std::vector<Entry>::iterator& entryIt)
{
    QDateTime startDateTime, endDateTime, currentDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    currentDateTime.setDate(entryIt->getDate());
    int duration = startDateTime.daysTo(endDateTime) + 1;
    int daysGone = startDateTime.daysTo(currentDateTime) + 1;
    double percX = (double) daysGone / duration;
    double percY = (double) entryIt->getWorkAmount() / (double) maxWorkAmount;

    int x = sceneWidth * percX - sceneWidth / 2;
    int y = -sceneHeight * percY + sceneHeight / 2;

    int xCoord = x - pixelPerDay / 2 + pixelPerGap;

    scene->addRect(xCoord, y, pixelPerDay - 2 * pixelPerGap, sceneHeight / 2 - y,
                   QPen(Qt::NoPen), QBrush(columnsColor));

    QDate date = entryIt->getDate();
    QString dateString = QString::number(date.day()) + "." +
                         QString::number(date.month());
    QGraphicsTextItem* dateTextItem = new QGraphicsTextItem(dateString);
    dateTextItem->setPos(xCoord + 2, sceneHeight / 2 - 20);
    QFont font;
    font.setPixelSize(10);
    dateTextItem->setFont(font);
    scene->addItem(dateTextItem);
}

void DailyWorkDiagramWindow::drawPercentLines()
{
    scene->addLine(-sceneWidth / 2, -sceneHeight / 4,
                   sceneWidth / 2, -sceneHeight / 4, QPen(linesColor));
    scene->addLine(-sceneWidth / 2, 0,
                   sceneWidth / 2, 0, QPen(linesColor));
    scene->addLine(-sceneWidth / 2, sceneHeight / 4,
                   sceneWidth / 2, sceneHeight / 4, QPen(linesColor));

    QFont font;
    font.setPixelSize(10);

    QGraphicsTextItem* text75Percent = new QGraphicsTextItem(
                QString::number((double) maxWorkAmount * 0.75));
    QGraphicsTextItem* text50Percent = new QGraphicsTextItem(
                QString::number((double) maxWorkAmount * 0.5));
    QGraphicsTextItem* text25Percent = new QGraphicsTextItem(
                QString::number((double) maxWorkAmount * 0.25));
    text75Percent->setFont(font);
    text50Percent->setFont(font);
    text25Percent->setFont(font);

    text75Percent->setPos(-sceneWidth/2, -sceneHeight/4);
    text50Percent->setPos(-sceneWidth/2, 0);
    text25Percent->setPos(-sceneWidth/2, sceneHeight/4);

    scene->addItem(text75Percent);
    scene->addItem(text50Percent);
    scene->addItem(text25Percent);
}

void DailyWorkDiagramWindow::clear()
{
    entries.clear();
    scene->clear();
}

void DailyWorkDiagramWindow::addEntry(const Entry& entry)
{
    entries.push_back(entry);
}

void DailyWorkDiagramWindow::setStartDate(const QDate& _startDate)
{
    startDate = _startDate;
}

void DailyWorkDiagramWindow::setEndDate(const QDate& _endDate)
{
    endDate = _endDate;
}

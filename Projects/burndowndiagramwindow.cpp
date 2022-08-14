#include "burndowndiagramwindow.h"
#include "ui_burndowndiagramwindow.h"

BurnDownDiagramWindow::BurnDownDiagramWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BurnDownDiagramWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    pixelPerDay = 35;
    sceneHeight = 380 - 25;
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    linesColor = QColor(192, 192, 192);
    dotsColor = QColor(255, 102, 0);
    dotRadius = 3;

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
    scene->clear();

    QDateTime startDateTime, endDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    int duration = startDateTime.daysTo(endDateTime) + 1;
    sceneWidth = duration * pixelPerDay;

    ui->graphicsView->setSceneRect(-sceneWidth / 2, -sceneHeight / 2,
                                   sceneWidth, sceneHeight);
    drawBurnDownLine();
    drawPercentLines();
    drawDateLines();
    drawEntries();
}

void BurnDownDiagramWindow::drawBurnDownLine()
{
    QDateTime startDateTime, endDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    int duration = startDateTime.daysTo(endDateTime) + 1;
    sceneWidth = duration * pixelPerDay;
    previousDotPos = QPointF(-sceneWidth / 2, -sceneHeight / 2);
    scene->addLine(-sceneWidth/2, -sceneHeight/2,
                   sceneWidth/2, sceneHeight/2, QPen(Qt::blue));
}

void BurnDownDiagramWindow::drawPercentLines()
{
    scene->addLine(-sceneWidth/2, -sceneHeight/4,
                   sceneWidth/2, -sceneHeight/4, QPen(linesColor));
    scene->addLine(-sceneWidth/2, 0, sceneWidth/2, 0, QPen(linesColor));
    scene->addLine(-sceneWidth/2, sceneHeight/4,
                   sceneWidth/2, sceneHeight/4, QPen(linesColor));

    QFont font;
    font.setPixelSize(10);

    QGraphicsTextItem* text75Percent = new QGraphicsTextItem("75%");
    QGraphicsTextItem* text50Percent = new QGraphicsTextItem("50%");
    QGraphicsTextItem* text25Percent = new QGraphicsTextItem("25%");
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

void BurnDownDiagramWindow::drawDateLines()
{
    QFont font;
    font.setPixelSize(7);
    int i = 1;
    QDateTime startDateTime, endDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    int duration = startDateTime.daysTo(endDateTime) + 1;
    for(QDate date = startDate; date <= endDate; date = date.addDays(1)){
        double perc = (double) i / duration;
        int xPos = sceneWidth * perc - sceneWidth/2;
        scene->addLine(xPos, -sceneHeight/2, xPos, sceneHeight/2, QPen(linesColor));

        QString dateString = QString::number(date.day()) + "." +
                             QString::number(date.month()) + "." +
                             QString::number(date.year() % 100);
        QGraphicsTextItem* dateText = new QGraphicsTextItem(dateString);
        dateText->setFont(font);
        dateText->setPos(xPos-12, sceneHeight/2 - 20);
        scene->addItem(dateText);
        ++i;
    }
}

void BurnDownDiagramWindow::drawEntries()
{
    int workDone = 0;
    QDateTime startDateTime, entryDateTime, endDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    int duration = startDateTime.daysTo(endDateTime) + 1;
    for(auto it = entries.begin(); it != entries.end(); ++it){
        workDone += it->getWorkAmount();
        entryDateTime.setDate(it->getDate());
        int daysGone = startDateTime.daysTo(entryDateTime) + 1;
        double percX = (double) daysGone / duration;
        double percY = (double) workDone / workAmount;
        double x = sceneWidth * percX - sceneWidth / 2;
        double y = sceneHeight * percY - sceneHeight / 2;
        scene->addEllipse(x - dotRadius, y - dotRadius, 2 * dotRadius,
                          2 * dotRadius, QPen(Qt::NoPen), QBrush(dotsColor));

        scene->addLine(previousDotPos.x(), previousDotPos.y(),
                       x, y, QPen(dotsColor));
        previousDotPos = QPointF(x, y);
    }
}

void BurnDownDiagramWindow::clear()
{
    entries.clear();
    scene->clear();
}

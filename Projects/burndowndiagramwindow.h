#ifndef BURNDOWNDIAGRAMWINDOW_H
#define BURNDOWNDIAGRAMWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <vector>

#include <Projects/entry.h>

namespace Ui {
class BurnDownDiagramWindow;
}

class BurnDownDiagramWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BurnDownDiagramWindow(QWidget *parent = nullptr);
    ~BurnDownDiagramWindow();

    void addEntry(const Entry& entry);
    void setStartDate(const QDate& _startDate);
    void setEndDate(const QDate& _endDate);
    void setWorkAmount(const int& _workAmount);
    void draw();
    void clear();

private:
    Ui::BurnDownDiagramWindow *ui;

    QGraphicsScene* scene;
    int pixelPerDay;
    int sceneHeight;
    int sceneWidth;
    QColor linesColor;
    QColor dotsColor;
    int dotRadius;
    QPointF previousDotPos;

    std::vector<Entry> entries;
    QDate startDate;
    QDate endDate;
    int workAmount;

    void drawBurnDownLine();
    void drawPercentLines();
    void drawDateLines();
    void drawEntries();
};

#endif // BURNDOWNDIAGRAMWINDOW_H

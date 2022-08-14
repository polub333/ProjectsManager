#ifndef DAILYWORKDIAGRAMWINDOW_H
#define DAILYWORKDIAGRAMWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <vector>

#include <Projects/entry.h>

namespace Ui {
class DailyWorkDiagramWindow;
}

class DailyWorkDiagramWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DailyWorkDiagramWindow(QWidget *parent = nullptr);
    ~DailyWorkDiagramWindow();

    void draw();
    void clear();
    void addEntry(const Entry& entry);
    void setStartDate(const QDate& _startDate);
    void setEndDate(const QDate& _endDate);

private:
    Ui::DailyWorkDiagramWindow *ui;
    QGraphicsScene* scene;

    QDate startDate;
    QDate endDate;

    int pixelPerDay;
    int pixelPerGap;
    int sceneHeight;
    int sceneWidth;
    int maxWorkAmount;
    QColor columnsColor;
    QColor linesColor;

    std::vector<Entry> entries;

    int calculateSceneWidth() const;
    int findMaxWorkAmount() const;
    void drawEntry(const std::vector<Entry>::iterator& entryIt);
    void drawPercentLines();
};

#endif // DAILYWORKDIAGRAMWINDOW_H

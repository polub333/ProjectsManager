#ifndef DAILYWORKSCENE_H
#define DAILYWORKSCENE_H

#include <QGraphicsScene>

#include <vector>

class DailyWorkScene: public QGraphicsScene
{
    Q_OBJECT
public:
    DailyWorkScene();
    void addPoint(const QPointF& point);
    void deletePoints();
    void draw();

private:
    std::vector<QPointF> points;
    qreal maxWork;

    int sceneHeight;

    void drawPoint(const QPointF& point);

};

#endif // DAILYWORKSCENE_H

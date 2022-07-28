#ifndef BURNDOWNSCENE_H
#define BURNDOWNSCENE_H

#include <QGraphicsScene>

#include <vector>

class BurnDownScene: public QGraphicsScene
{
    Q_OBJECT
public:
    BurnDownScene();
    void draw();
    void addPoint(const QPointF& point);
    void deletePoints();
private:
    std::vector<QPointF> points;

    void drawBurnDownLine();
    void drawPointsAndLines();
    void drawPoint(const qreal& x, const qreal& y);
    void drawLine(const QPointF& point1, const QPointF& point2);
};

#endif // BURNDOWNSCENE_H

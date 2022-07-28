#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include <vector>

class Scene: public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
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

#endif // SCENE_H

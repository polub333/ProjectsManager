#include "burndownscene.h"

BurnDownScene::BurnDownScene()
{

}

void BurnDownScene::draw()
{
    drawBurnDownLine();
    drawPointsAndLines();
}

void BurnDownScene::addPoint(const QPointF& point)
{
    points.push_back(point);
}

void BurnDownScene::deletePoints()
{
    points.clear();
}

void BurnDownScene::drawBurnDownLine()
{
    addLine(0, 0, 196, 126, QPen(Qt::blue));
}

void BurnDownScene::drawPointsAndLines()
{
    QPointF previousPoint;
    auto it = points.begin();
    if(it == points.end()){
        return;
    }
    drawPoint((*it).x(), (*it).y());
    drawLine(QPointF(0, 0), (*it));
    previousPoint = (*it);
    ++it;
    for(; it != points.end(); ++it){
        drawPoint((*it).x(), (*it).y());
        drawLine(previousPoint, (*it));
        previousPoint = (*it);
    }
}

void BurnDownScene::drawPoint(const qreal& x, const qreal& y)
{
    addRect(x-2, y-2, 5, 5, QPen(Qt::NoPen), QBrush(Qt::red));
}

void BurnDownScene::drawLine(const QPointF& point1, const QPointF& point2)
{
    addLine(point1.x(), point1.y(), point2.x(), point2.y(), QPen(Qt::red));
}

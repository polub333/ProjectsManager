#include "dailyworkscene.h"

DailyWorkScene::DailyWorkScene()
{
    maxWork = 0;
    sceneHeight = 126 - 1;
}

void DailyWorkScene::addPoint(const QPointF& point)
{
    points.push_back(point);
}

void DailyWorkScene::deletePoints()
{
    //addRect(0, 0, this->width(), this->height(), QPen(Qt::NoPen), QBrush(Qt::white));
    //clear();
    points.clear();
}

void DailyWorkScene::draw()
{
    for(auto it = points.begin(); it != points.end(); ++it){
        if((*it).y() > maxWork){
            maxWork = (*it).y();
        }
    }
    for(auto it = points.begin(); it != points.end(); ++it){
        drawPoint((*it));
    }
}

void DailyWorkScene::drawPoint(const QPointF& point)
{
    qreal y = (double) (point.y() / maxWork) * (double) sceneHeight;
    addRect(point.x() - 1, sceneHeight - y, 3, y, QPen(Qt::NoPen), QBrush(Qt::blue));
}

#include "subproject.h"

Subproject::Subproject()
{
    done = false;
    workDone = 0;
}

void Subproject::addWorkDone(const int& work)
{
    workDone += work;
    if(workDone == workAmount){
        done = true;
    }
}

void Subproject::setName(const QString& _name)
{
    name = _name;
}

void Subproject::setDate(const QDate& _date)
{
    date = _date;
}

void Subproject::setWorkAmount(const int& _workAmount)
{
    workAmount = _workAmount;
}

void Subproject::setWorkDone(const int& _workDone)
{
    workDone = _workDone;
}

void Subproject::setDone(const bool& _done)
{
    done = _done;
}

QString Subproject::getName() const
{
    return name;
}

QDate Subproject::getDate() const
{
    return date;
}

int Subproject::getWorkAmount() const
{
    return workAmount;
}

int Subproject::getWorkDone() const
{
    return workDone;
}

bool Subproject::isDone() const
{
    return done;
}

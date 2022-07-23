#include "subproject.h"

Subproject::Subproject()
{

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

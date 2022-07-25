#include "entry.h"

Entry::Entry()
{

}

void Entry::setDate(const QDate& _date)
{
    date = _date;
}

void Entry::setProjectName(const QString& _projectName)
{
    projectName = _projectName;
}

void Entry::setWorkAmount(const int& _workAmount)
{
    workAmount = _workAmount;
}

QDate Entry::getDate() const
{
    return date;
}

QString Entry::getProjectName() const
{
    return projectName;
}

int Entry::getWorkAmount() const
{
    return workAmount;
}

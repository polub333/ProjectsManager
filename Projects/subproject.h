#ifndef SUBPROJECT_H
#define SUBPROJECT_H

#include <QString>
#include <QDate>

class Subproject
{
public:
    Subproject();

    void setName(const QString& _name);
    void setDate(const QDate& _date);
    void setWorkAmount(const int& _workAmount);
    void setWorkDone(const int& _workDone);
    void setDone(const bool& _done);

    QString getName() const;
    QDate getDate() const;
    int getWorkAmount() const;
    int getWorkDone() const;
    bool isDone() const;

private:
    QString name;
    QDate date;
    int workAmount;
    int workDone;
    bool done;
};

#endif // SUBPROJECT_H

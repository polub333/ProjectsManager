#ifndef ENTRY_H
#define ENTRY_H

#include <QDate>
#include <QString>

class Entry
{
public:
    Entry();

    void setDate(const QDate& _date);
    void setProjectName(const QString& _projectName);
    void setWorkAmount(const int& _workAmount);

    QDate getDate() const;
    QString getProjectName() const;
    int getWorkAmount() const;
private:
    QDate date;
    QString projectName;
    int workAmount;
};

#endif // ENTRY_H

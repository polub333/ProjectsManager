#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDate>

#include <vector>
#include <memory>

#include <Projects/subproject.h>

class Project
{
public:
    Project();

private:
    std::vector<std::unique_ptr<Subproject>> subprojects;

    QString name;
    QString description;

    QDate startDate;
    QDate endDate;
    int behindScheduleDays;
    int behinScheduleWorkAmount;
    QDate expectedEndDate;

    int workAmount;
    int workDone;
    int workRemaining;
    int startDailyWorkAmount;
    int currentDailyWorkAmount;
    int requiredDailyWorkAmount;

    int dailyReward;
    int chainrewardMultiplier;
    int maxDailyReward;
    int currentDailyReward;
    int currentChainLength;
    int totalProjectReward;

};

#endif // PROJECT_H

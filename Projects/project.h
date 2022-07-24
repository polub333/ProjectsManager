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

    void addSubproject(const std::unique_ptr<Subproject> _subproject);

    void setName(const QString& _name);
    void setDescription(const QString& _description);

    void setStartDate(const QDate& _startDate);
    void setEndDate(const QDate& _endDate);
    void setBehindScheduleDays(const int& _beihindSceduleDays);
    void setBehindScheduleWorkAmount(const int& _behindSceduleWorkAmount);
    void setExpectedEndDate(const QDate& _expectedEndDate);

    void setWorkAmount(const int& _workAmount);
    void setWorkDone(const int& _workDone);
    void setWorkRemaining(const int& _workRemaining);
    void setStartDailyWorkAmount(const int& _startDailyWorkAmount);
    void setCurrentDailyWorkAmount(const int& _currentDailyWorkAmount);
    void setRequiredDailyWorkAmount(const int& _requiredDailyWorkAmount);

    void setDailyReward(const int& _dailyReward);
    void setChainRewardMultiplier(const int& _chainRewardMultiplier);
    void setMaxDailyReward(const int& _maxDailyReward);
    void setCurrentDailyReward(const int& _currentDailyReward);
    void setCurrentChainLength(const int& _currentChainLength);
    void setTotalProjectReward(const int& _totalProjectReward);

    QString getName() const;
    QString getDescription() const;

    QDate getStartDate() const;
    QDate getEndDate() const;
    int getBehindSceduleDays() const;
    int getBehindSceduleWorkAmount() const;
    QDate getExpectedEndDate() const;

    int getWorkAmount() const;
    int getWorkDone() const;
    int getWorkRemaining() const;
    int getStartDailyWorkAmount() const;
    int getCurrentDailyWorkAmount() const;
    int getRequiredDailyWorkAmount() const;

    int getDailyReward() const;
    int getChainRewardMultiplier() const;
    int getMaxDailyReward() const;
    int getCurrentDailyReward() const;
    int getCurrentChainLength() const;
    int getTotalProjectReward() const;

private:
    std::vector<std::unique_ptr<Subproject>> subprojects;

    QString name;
    QString description;

    QDate startDate;
    QDate endDate;
    int behindScheduleDays;
    int behindScheduleWorkAmount;
    QDate expectedEndDate;

    int workAmount;
    int workDone;
    int workRemaining;
    int startDailyWorkAmount;
    int currentDailyWorkAmount;
    int requiredDailyWorkAmount;

    int dailyReward;
    int chainRewardMultiplier;
    int maxDailyReward;
    int currentDailyReward;
    int currentChainLength;
    int totalProjectReward;

};

#endif // PROJECT_H

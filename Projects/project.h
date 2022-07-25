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

    void addSubproject(std::unique_ptr<Subproject> _subproject);
    std::vector<std::unique_ptr<Subproject>>::const_iterator getSubprojectsBeginIterator() const;
    std::vector<std::unique_ptr<Subproject>>::const_iterator getSubprojectsEndIterator() const;

    void addReward(const double& reward);

    void setName(const QString& _name);
    void setDescription(const QString& _description);

    void setStartDate(const QDate& _startDate);
    void setEndDate(const QDate& _endDate);
    void setBehindScheduleDays(const int& _beihindSceduleDays);
    void setBehindScheduleWorkAmount(const int& _behindSceduleWorkAmount);
    void setExpectedEndDate(const QDate& _expectedEndDate);
    void setDaysGone(const int& _daysGone);
    void setDaysRemaining(const int& _daysRemaining);

    void setWorkAmount(const int& _workAmount);
    void setWorkDone(const int& _workDone);
    void setWorkRemaining(const int& _workRemaining);
    void setStartDailyWorkAmount(const double& _startDailyWorkAmount);
    void setCurrentDailyWorkAmount(const double& _currentDailyWorkAmount);
    void setRequiredDailyWorkAmount(const double& _requiredDailyWorkAmount);

    void setDailyReward(const double& _dailyReward);
    void setChainRewardMultiplier(const double& _chainRewardMultiplier);
    void setMaxDailyReward(const double& _maxDailyReward);
    void setCurrentDailyReward(const double& _currentDailyReward);
    void setCurrentChainLength(const int& _currentChainLength);
    void setPreviousEntry(const QDate& _previousEntry);
    void setTotalProjectReward(const double& _totalProjectReward);

    QString getName() const;
    QString getDescription() const;

    QDate getStartDate() const;
    QDate getEndDate() const;
    int getBehindSceduleDays() const;
    int getBehindSceduleWorkAmount() const;
    QDate getExpectedEndDate() const;
    int getDaysGone() const;
    int getDaysRemaining() const;

    int getWorkAmount() const;
    int getWorkDone() const;
    int getWorkRemaining() const;
    double getStartDailyWorkAmount() const;
    double getCurrentDailyWorkAmount() const;
    double getRequiredDailyWorkAmount() const;

    double getDailyReward() const;
    double getChainRewardMultiplier() const;
    double getMaxDailyReward() const;
    double getCurrentDailyReward() const;
    int getCurrentChainLength() const;
    QDate getPreviousEntry() const;
    double getTotalProjectReward() const;

private:
    std::vector<std::unique_ptr<Subproject>> subprojects;

    QString name;
    QString description;

    QDate startDate;
    QDate endDate;
    int behindScheduleDays;
    int behindScheduleWorkAmount;
    QDate expectedEndDate;
    int daysGone;
    int daysRemaining;

    int workAmount;
    int workDone;
    int workRemaining;
    double startDailyWorkAmount;
    double currentDailyWorkAmount;
    double requiredDailyWorkAmount;

    double dailyReward;
    double chainRewardMultiplier;
    double maxDailyReward;
    double currentDailyReward;
    int currentChainLength;
    QDate previousEntry;
    double totalProjectReward;

};

#endif // PROJECT_H

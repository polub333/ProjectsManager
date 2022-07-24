#include "project.h"

Project::Project()
{

}

void Project::addSubproject(std::unique_ptr<Subproject> subproject)
{
    subprojects.push_back(std::move(subproject));
}

std::vector<std::unique_ptr<Subproject>>::const_iterator
Project::getSubprojectsBeginIterator() const
{
    return subprojects.begin();
}

std::vector<std::unique_ptr<Subproject>>::const_iterator
Project::getSubprojectsEndIterator() const
{
    return subprojects.end();
}

void Project::setName(const QString& _name)
{
    name = _name;
}

void Project::setDescription(const QString& _description)
{
    description = _description;
}

void Project::setStartDate(const QDate& _startDate)
{
   startDate = _startDate;
}

void Project::setEndDate(const QDate& _endDate)
{
    endDate = _endDate;
}

void Project::setBehindScheduleDays(const int& _behindScheduleDays)
{
    behindScheduleDays = _behindScheduleDays;
}

void Project::setBehindScheduleWorkAmount(const int& _behindScheduleWorkAmount)
{
    behindScheduleWorkAmount = _behindScheduleWorkAmount;
}

void Project::setExpectedEndDate(const QDate& _expectedEndDate)
{
    expectedEndDate = _expectedEndDate;
}

void Project::setDaysGone(const int& _daysGone)
{
    daysGone = _daysGone;
}

void Project::setDaysRemaining(const int& _daysRemaining)
{
    daysRemaining = _daysRemaining;
}

void Project::setWorkAmount(const int& _workAmount)
{
    workAmount = _workAmount;
}

void Project::setWorkDone(const int& _workDone)
{
    workDone = _workDone;
}

void Project::setWorkRemaining(const int& _workRemaining)
{
    workRemaining = _workRemaining;
}

void Project::setStartDailyWorkAmount(const int& _startDailyWorkAmount)
{
    startDailyWorkAmount = _startDailyWorkAmount;
}

void Project::setCurrentDailyWorkAmount(const int& _currentDailyWorkAmount)
{
    currentDailyWorkAmount = _currentDailyWorkAmount;
}

void Project::setRequiredDailyWorkAmount(const int& _requiredDailyWorkAmount)
{
    requiredDailyWorkAmount = _requiredDailyWorkAmount;
}

void Project::setDailyReward(const int& _dailyReward)
{
    dailyReward = _dailyReward;
}

void Project::setChainRewardMultiplier(const int& _chainRewardMultiplier)
{
    chainRewardMultiplier = _chainRewardMultiplier;
}

void Project::setMaxDailyReward(const int& _maxDailyReward)
{
    maxDailyReward =_maxDailyReward;
}

void Project::setCurrentDailyReward(const int& _currentDailyReward)
{
    currentDailyReward = _currentDailyReward;
}

void Project::setCurrentChainLength(const int& _currentChainLength)
{
    currentChainLength = _currentChainLength;
}

void Project::setTotalProjectReward(const int& _totalProjectReward)
{
    totalProjectReward = _totalProjectReward;
}

QString Project::getName() const
{
    return name;
}

QString Project::getDescription() const
{
    return description;
}

QDate Project::getStartDate() const
{
    return startDate;
}

QDate Project::getEndDate() const
{
    return endDate;
}

int Project::getBehindSceduleDays() const
{
    return behindScheduleDays;
}

int Project::getBehindSceduleWorkAmount() const
{
    return behindScheduleWorkAmount;
}

QDate Project::getExpectedEndDate() const
{
    return expectedEndDate;
}

int Project::getDaysGone() const
{
    return daysGone;
}

int Project::getDaysRemaining() const
{
    return daysRemaining;
}

int Project::getWorkAmount() const
{
    return workAmount;
}

int Project::getWorkDone() const
{
    return workDone;
}

int Project::getWorkRemaining() const
{
    return workRemaining;
}

int Project::getStartDailyWorkAmount() const
{
    return startDailyWorkAmount;
}

int Project::getCurrentDailyWorkAmount() const
{
    return currentDailyWorkAmount;
}

int Project::getRequiredDailyWorkAmount() const
{
    return requiredDailyWorkAmount;
}

int Project::getDailyReward() const
{
    return dailyReward;
}

int Project::getChainRewardMultiplier() const
{
    return chainRewardMultiplier;
}

int Project::getMaxDailyReward() const
{
    return maxDailyReward;
}

int Project::getCurrentDailyReward() const
{
    return currentDailyReward;
}

int Project::getCurrentChainLength() const
{
    return currentChainLength;
}

int Project::getTotalProjectReward() const
{
    return totalProjectReward;
}


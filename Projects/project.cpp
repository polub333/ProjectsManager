#include "project.h"

Project::Project()
{
    workDone = 0;
    currentChainLength = 0;
    totalProjectReward = 0;
    previousEntry = QDate(1, 1, 1);
    done = false;
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

void Project::addReward(const double& reward)
{
    totalProjectReward += reward;
}

void Project::addWorkDone(const int& _work)
{
    int work = _work;
    workDone += work;
    if(workDone >= workAmount){
        workDone = workAmount;
        done = true;
    }
    for(auto it = subprojects.begin(); it != subprojects.end(); ++it){
        int workRemaining = (*it)->getWorkAmount() - (*it)->getWorkDone();
        if(workRemaining >= work){
            (*it)->addWorkDone(work);
            break;
        }
        else{
            (*it)->addWorkDone(workRemaining);
            work -= workRemaining;
        }
    }
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

void Project::setStartDailyWorkAmount(const double& _startDailyWorkAmount)
{
    startDailyWorkAmount = _startDailyWorkAmount;
}

void Project::setCurrentDailyWorkAmount(const double& _currentDailyWorkAmount)
{
    currentDailyWorkAmount = _currentDailyWorkAmount;
}

void Project::setRequiredDailyWorkAmount(const double& _requiredDailyWorkAmount)
{
    requiredDailyWorkAmount = _requiredDailyWorkAmount;
}

void Project::setDailyReward(const double& _dailyReward)
{
    dailyReward = _dailyReward;
}

void Project::setChainRewardMultiplier(const double& _chainRewardMultiplier)
{
    chainRewardMultiplier = _chainRewardMultiplier;
}

void Project::setMaxDailyReward(const double& _maxDailyReward)
{
    maxDailyReward =_maxDailyReward;
}

void Project::setCurrentDailyReward(const double& _currentDailyReward)
{
    currentDailyReward = _currentDailyReward;
}

void Project::setCurrentChainLength(const int& _currentChainLength)
{
    currentChainLength = _currentChainLength;
}

void Project::setPreviousEntry(const QDate& _previousEntry)
{
    previousEntry = _previousEntry;
}

void Project::setTotalProjectReward(const double& _totalProjectReward)
{
    totalProjectReward = _totalProjectReward;
}

void Project::setDone(const bool& _done)
{
    done = _done;
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

double Project::getStartDailyWorkAmount() const
{
    return startDailyWorkAmount;
}

double Project::getCurrentDailyWorkAmount() const
{
    return currentDailyWorkAmount;
}

double Project::getRequiredDailyWorkAmount() const
{
    return requiredDailyWorkAmount;
}

double Project::getDailyReward() const
{
    return dailyReward;
}

double Project::getChainRewardMultiplier() const
{
    return chainRewardMultiplier;
}

double Project::getMaxDailyReward() const
{
    return maxDailyReward;
}

double Project::getCurrentDailyReward() const
{
    return currentDailyReward;
}

int Project::getCurrentChainLength() const
{
    return currentChainLength;
}

QDate Project::getPreviousEntry() const
{
    return previousEntry;
}

double Project::getTotalProjectReward() const
{
    return totalProjectReward;
}

bool Project::isDone() const
{
    return done;
}

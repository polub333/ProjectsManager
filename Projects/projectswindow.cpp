#include "projectswindow.h"
#include "ui_projectswindow.h"

ProjectsWindow::ProjectsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsWindow)
 //   selectedProject(*(new Project()))
{
    ui->setupUi(this);
    currentDateTime = QDateTime::currentDateTime();

    createProjectFromFile("projects/project1.txt");
    createProjectFromFile("projects/project2.txt");


    readEntries("entries");
    processEntries(QDate(currentDateTime.date()));
    calculateProjects();

    showProjectInfo();

}

ProjectsWindow::~ProjectsWindow()
{
    delete ui;
}

void ProjectsWindow::selectProject(
        const std::vector<std::unique_ptr<Project>>::iterator iterator)
{
    selectedProjectIt = iterator;
}

std::vector<std::unique_ptr<Project>>::iterator
ProjectsWindow::findProjectByName(const QString& name)
{
    for(auto it = projects.begin(); it != projects.end(); ++it){
        if((*it)->getName() == name){
            return it;
        }
    }
    return projects.end();
}

void ProjectsWindow::calculateProjects()
{
    for(auto it = projects.begin(); it != projects.end(); ++it){
        calculateProject(it);
    }
}

void ProjectsWindow::calculateProject(std::vector<std::unique_ptr<Project>>::iterator projectIt)
{
    calculateProjectDateAndWork(projectIt);
    calculateProjectReward(projectIt);
}

void ProjectsWindow::calculateProjectDateAndWork(
        std::vector<std::unique_ptr<Project>>::iterator projectIt)
{
    QDateTime startDate, endDate;
    startDate.setDate((*projectIt)->getStartDate());
    endDate.setDate((*projectIt)->getEndDate());

    int duration = startDate.daysTo(endDate) + 1;
    int daysGone = startDate.daysTo(currentDateTime);
    daysGone = checkAndSetProjectDaysGoneOrDaysRemaining(daysGone, duration);

    int daysRemaining = currentDateTime.daysTo(endDate) + 1;
    daysRemaining = checkAndSetProjectDaysGoneOrDaysRemaining(daysRemaining, duration);

    int workAmount = (*projectIt)->getWorkAmount();
    int workDone = (*projectIt)->getWorkDone();
    int workRemaining = workAmount - workDone;
    workRemaining = checkAndSetProjectWorkRemaining(workRemaining);

    double expectedWorkDone = (double) workAmount / duration * daysGone;
    double workDoneDifference = (double) expectedWorkDone - workDone;
    /*
    if(workDoneDifference > workRemaining){
        workDoneDifference = workRemaining;
    }
    */
    int behindScheduleDays = workDoneDifference / (*projectIt)->getStartDailyWorkAmount();
    int behindScheduleWorkAmount = workDoneDifference;
    double currentDailyWorkAmount = checkAndSetProjectDailyWorkAmount(workDone, daysGone);
    double requiredDailyWorkAmount =
            checkAndSetProjectDailyWorkAmount(workRemaining, daysRemaining);

    QDate expectedEndDate;
    if(workDone == 0){
        expectedEndDate = QDate(1, 1, 1);
    }
    else{
        int daysRequired = workRemaining / currentDailyWorkAmount;
        QDateTime expectedEndDateTime = currentDateTime.addDays(daysRequired - 1);
        expectedEndDate = expectedEndDateTime.date();
    }

    (*projectIt)->setBehindScheduleDays(behindScheduleDays);
    (*projectIt)->setBehindScheduleWorkAmount(behindScheduleWorkAmount);
    (*projectIt)->setExpectedEndDate(expectedEndDate);
    (*projectIt)->setDaysGone(daysGone);
    (*projectIt)->setDaysRemaining(daysRemaining);

    (*projectIt)->setWorkRemaining(workRemaining);
    (*projectIt)->setCurrentDailyWorkAmount(currentDailyWorkAmount);
    (*projectIt)->setRequiredDailyWorkAmount(requiredDailyWorkAmount);
}

void ProjectsWindow::calculateProjectReward(
        std::vector<std::unique_ptr<Project>>::iterator projectIt)
{
    double currentChainMultiplier = (double)(*projectIt)->getCurrentChainLength() * (double)
                                 (*projectIt)->getChainRewardMultiplier();
    double currentDailyReward =
            (double)(*projectIt)->getDailyReward() * (1 + currentChainMultiplier);
    (*projectIt)->setCurrentDailyReward(currentDailyReward);
}

int ProjectsWindow::checkAndSetProjectDaysGoneOrDaysRemaining(
        const int& days, const int& duration) const
{
    if(days < 0){
        return 0;
    }
    else if(days > duration){
        return duration;
    }
    return days;
}

int ProjectsWindow::checkAndSetProjectWorkRemaining(const int& workRemaining) const
{
    if(workRemaining < 0){
        return 0;
    }
    return workRemaining;
}

double ProjectsWindow::checkAndSetProjectDailyWorkAmount(
        const int& work, const int& days) const
{
    if(days == 0){
        return 0;
    }
    else{
        return (double) work / days;
    }
}

void ProjectsWindow::processEntries(const QDate& maxDate)
{
    for(auto it = entries.begin(); it != entries.end(); ++it){
        if((*it)->getDate() <= maxDate){
            processEntry(it);
        }
    }
}

void ProjectsWindow::processEntry(
        std::vector<std::unique_ptr<Entry>>::iterator entryIt)
{
    std::vector<std::unique_ptr<Project>>::iterator projectIt = projects.end();
    for(auto it = projects.begin(); it != projects.end(); ++it){
        if((*it)->getName() == (*entryIt)->getProjectName()){
            projectIt = it;
        }
    }
    if(projectIt == projects.end()){
        qDebug()<<"No such project from entry projectName";
        return;
    }
    (*projectIt)->setWorkDone((*projectIt)->getWorkDone() + (*entryIt)->getWorkAmount());
    QDateTime previousEntryDate, currentEntryDate;
    previousEntryDate.setDate((*projectIt)->getPreviousEntry());
    currentEntryDate.setDate((*entryIt)->getDate());
    int daysTo = previousEntryDate.daysTo(currentEntryDate);
    if(daysTo <= 2){
        if(daysTo != 0){
            (*projectIt)->setCurrentChainLength((*projectIt)->getCurrentChainLength() + 1);
            (*projectIt)->addReward((*projectIt)->getCurrentDailyReward());
        }
    }
    else{
        (*projectIt)->setCurrentChainLength(1);
        (*projectIt)->addReward((*projectIt)->getCurrentDailyReward());
    }
    (*projectIt)->setPreviousEntry(currentEntryDate.date());
    calculateProject(projectIt);
}

void ProjectsWindow::readEntries(const QString& path)
{
    for(std::filesystem::recursive_directory_iterator it(path.toStdString()), end;
        it != end; ++it){
        if(it->path().extension() == ".txt"){
            readEntry(it->path().string());
        }
    }
}

void ProjectsWindow::readEntry(const std::string& path)
{
    std::fstream entryFile(path, std::ios_base::in);
    std::string str, str2, str3;
    while(!entryFile.eof()){
        std::unique_ptr<Entry> entry = std::make_unique<Entry>();
        getline(entryFile, str);
        getline(entryFile, str2);
        getline(entryFile, str3);
        entry->setDate(QDate(std::stoi(str3), std::stoi(str2), std::stoi(str)));
        getline(entryFile, str);
        auto projectIt = findProjectByName(QString::fromStdString(str));
        if(projectIt == projects.end()){
            qDebug()<<"No such prject";
            return;
        }
        entry->setProjectName(QString::fromStdString(str));
        getline(entryFile, str);
        entry->setWorkAmount(stoi(str));
        entries.push_back(std::move(entry));
    }
    entryFile.close();
}

void ProjectsWindow::showProjectInfo()
{
    showProjectNameInfo();
    showProjectDateInfo();
    showProjectWorkInfo();
    showProjectRewardInfo();
    showProjectSubprojects();
}

void ProjectsWindow::showProjectNameInfo()
{
    ui->nameLabel->setText((*selectedProjectIt)->getName());
    ui->descriptionLabel->setText((*selectedProjectIt)->getDescription());
}

void ProjectsWindow::showProjectDateInfo()
{
    QDate startDate = (*selectedProjectIt)->getStartDate();
    QDate endDate = (*selectedProjectIt)->getEndDate();
    QDate expectedEndDate = (*selectedProjectIt)->getExpectedEndDate();
    QString stringStartDate = QString::number(startDate.day()) + "/" +
                              QString::number(startDate.month()) + "/" +
                              QString::number(startDate.year());
    QString stringEndDate = QString::number(endDate.day()) + "/" +
                            QString::number(endDate.month()) + "/" +
                            QString::number(endDate.year());
    QString stringExpectedEndDate = QString::number(expectedEndDate.day()) + "/" +
                                    QString::number(expectedEndDate.month()) + "/" +
                                    QString::number(expectedEndDate.year());
    ui->startDateLabel->setText(stringStartDate);
    ui->endDateLabel->setText(stringEndDate);
    ui->expectedEndDateLabel->setText(stringExpectedEndDate);

    QString behindScheduleDaysString = QString::number((*selectedProjectIt)->
                                                        getBehindSceduleDays());
    QString behindScheduleWorkString = QString::number((*selectedProjectIt)->
                                                        getBehindSceduleWorkAmount());
    ui->behindScheduleDaysLabel->setText(behindScheduleDaysString);
    ui->behinScheduleWorkLabel->setText(behindScheduleWorkString);

    QString daysGone = QString::number((*selectedProjectIt)->getDaysGone());
    QString daysRemaining = QString::number((*selectedProjectIt)->getDaysRemaining());
    ui->daysGoneLabel->setText(daysGone);
    ui->daysRemainingLabel->setText(daysRemaining);
}

void ProjectsWindow::showProjectWorkInfo()
{
    int workAmount = (*selectedProjectIt)->getWorkAmount();
    int workDone = (*selectedProjectIt)->getWorkDone();
    ui->progressBar->setValue((double)workDone / workAmount * 100);
    ui->workAmountLabel->setText(QString::number(workAmount));
    ui->workDoneLabel->setText(QString::number(workDone));
    ui->workRemainingLabel->setText(QString::number((*selectedProjectIt)->getWorkRemaining()));
    ui->startDailyWorkLabel->setText(QString::number((*selectedProjectIt)->
                                                      getStartDailyWorkAmount()));
    ui->currentDailyWorkLabel->setText(QString::number((*selectedProjectIt)->
                                                        getCurrentDailyWorkAmount()));
    ui->requiredDailyWorkLabel->setText(QString::number((*selectedProjectIt)->
                                                         getRequiredDailyWorkAmount()));
}

void ProjectsWindow::showProjectRewardInfo()
{
    ui->dailyRewardLabel->setText(QString::number((*selectedProjectIt)->getDailyReward()));
    ui->chainMultiplierLabel->setText(QString::number((*selectedProjectIt)->
                                                       getChainRewardMultiplier()));
    ui->maxDailyRewardLabel->setText(QString::number((*selectedProjectIt)->
                                                      getMaxDailyReward()));
    ui->currentDailyRewardLabel->setText(QString::number((*selectedProjectIt)->
                                                          getCurrentDailyReward()));
    ui->currentChainLengthLabel->setText(QString::number((*selectedProjectIt)->
                                                          getCurrentChainLength()));
    double currentChainMultiplier = (double)(*selectedProjectIt)->getCurrentChainLength() *
                                            (*selectedProjectIt)->getChainRewardMultiplier();
    ui->currentChainMultiplierLabel->setText(QString::number(currentChainMultiplier));
    ui->totalRewardLabel->setText(QString::number((*selectedProjectIt)->
                                                   getTotalProjectReward()));
}

void ProjectsWindow::showProjectSubprojects()
{
    auto begin = (*selectedProjectIt)->getSubprojectsBeginIterator();
    auto end = (*selectedProjectIt)->getSubprojectsEndIterator();
    for(auto it = begin; it != end; ++it){
        showSubprojectInfo(it);
    }
}

void ProjectsWindow::showSubprojectInfo(
        std::vector<std::unique_ptr<Subproject>>::const_iterator subprojectIt)
{
    QString name = (*subprojectIt)->getName();
    int workAmount = (*subprojectIt)->getWorkAmount();
    int workDone = (*subprojectIt)->getWorkDone();
    QDate date = (*subprojectIt)->getDate();
    QString stringDate = QString::number(date.day()) + "/" +
                         QString::number(date.month()) + "/" +
                         QString::number(date.year());

    QWidget* widget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* nameAndDateLayout = new QHBoxLayout();
    QHBoxLayout* workLayout = new QHBoxLayout();
    QVBoxLayout* workStaticLayout = new QVBoxLayout();
    QVBoxLayout* workDinamicLayout = new QVBoxLayout();

    QLabel* nameLabel = new QLabel(widget);
    nameLabel->setText(name);
    nameAndDateLayout->addWidget(nameLabel);
    QLabel* dateLabel = new QLabel(widget);
    dateLabel->setText(stringDate);
    nameAndDateLayout->addWidget(dateLabel);

    QProgressBar* progressBar = new QProgressBar(widget);
    progressBar->setValue((double) workDone / workAmount * 100);

    QLabel* workAmountLabel = new QLabel(widget);
    QLabel* workAmountStaticLabel = new QLabel(widget);
    workAmountLabel->setText(QString::number(workAmount));
    workAmountStaticLabel->setText("Work Amount");
    workStaticLayout->addWidget(workAmountStaticLabel);
    workDinamicLayout->addWidget(workAmountLabel);

    QLabel* workDoneLabel = new QLabel(widget);
    QLabel* workDoneStaticLabel = new QLabel(widget);
    workDoneLabel->setText(QString::number(workDone));
    workDoneStaticLabel->setText("Work Done");
    workStaticLayout->addWidget(workDoneStaticLabel);
    workDinamicLayout->addWidget(workDoneLabel);

    workLayout->addLayout(workStaticLayout);
    workLayout->addLayout(workDinamicLayout);
    mainLayout->addLayout(nameAndDateLayout);
    mainLayout->addWidget(progressBar);
    mainLayout->addLayout(workLayout);
    widget->setLayout(mainLayout);
    ui->subprojectsLayout->addWidget(widget);
}

void ProjectsWindow::createProjectFromFile(const QString& path)
{
    std::fstream file(path.toStdString(), std::ios_base::in);
    std::string str;
    std::string str2;
    std::string str3;
    std::unique_ptr<Project> project = std::make_unique<Project>();
    std::getline(file, str);
    project->setName(QString::fromStdString(str));
    std::getline(file, str);
    project->setDescription(QString::fromStdString(str));
    std::getline(file, str);
    std::getline(file, str2);
    std::getline(file, str3);
    QDate startDate;
    startDate.setDate(std::stoi(str3), std::stoi(str2), std::stoi(str));
    project->setStartDate(startDate);
    std::getline(file, str);
    std::getline(file, str2);
    std::getline(file, str3);
    QDate endDate;
    endDate.setDate(std::stoi(str3), std::stoi(str2), std::stoi(str));
    project->setEndDate(endDate);
    std::getline(file, str);
    project->setWorkAmount(stoi(str));
    QDateTime startDateTime, endDateTime;
    startDateTime.setDate(startDate);
    endDateTime.setDate(endDate);
    int duration = startDateTime.daysTo(endDateTime) + 1;
    project->setStartDailyWorkAmount((double)stod(str) / duration);
    project->setWorkDone(0);
    std::getline(file, str);
    project->setDailyReward(stod(str));
    project->setCurrentDailyReward(stod(str));
    project->setCurrentChainLength(0);
    std::getline(file, str);
    project->setChainRewardMultiplier(stod(str));
    project->setPreviousEntry(QDate(1, 1, 1));
    std::getline(file, str);
    project->setMaxDailyReward(stod(str));
    project->setTotalProjectReward(0);
    std::getline(file, str);
    int subprojects = stoi(str);
    for(int i=0;i<subprojects;++i){
        std::unique_ptr<Subproject> subproject = std::make_unique<Subproject>();
        std::getline(file, str);
        subproject->setName(QString::fromStdString(str));
        std::getline(file, str);
        std::getline(file, str2);
        std::getline(file, str3);
        QDate endSubprojectDate;
        endSubprojectDate.setDate(std::stoi(str3), std::stoi(str2), std::stoi(str));
        subproject->setDate(endSubprojectDate);
        subproject->setDone(false);
        std::getline(file, str);
        subproject->setWorkAmount(stoi(str));
        project->addSubproject(std::move(subproject));
    }
    projects.push_back(std::move(project));
    selectProject(projects.end() - 1);
    file.close();
}

void ProjectsWindow::createTestProject()
{
    std::unique_ptr<Project> project = std::make_unique<Project>();
    project->setName("Test project");
    project->setDescription("Test project description");
    project->setStartDate(QDate(2022, 07, 24));
    project->setEndDate(QDate(2022, 07, 25));
    project->setBehindScheduleDays(0);
    project->setBehindScheduleWorkAmount(0);
    project->setExpectedEndDate(project->getEndDate());
    project->setDaysGone(0);
    project->setDaysRemaining(100000);
    project->setWorkAmount(100);
    project->setWorkDone(50);
    project->setWorkRemaining(project->getWorkAmount() - project->getWorkDone());
    project->setStartDailyWorkAmount(project->getWorkAmount() / 10);
    project->setCurrentDailyWorkAmount(1000);
    project->setRequiredDailyWorkAmount(1);
    project->setDailyReward(-10);
    project->setChainRewardMultiplier(111);
    project->setMaxDailyReward(1e9);
    project->setCurrentDailyReward(-1);
    project->setCurrentChainLength(-1000);
    project->setTotalProjectReward(10000000);

    std::unique_ptr<Subproject> sub1 = std::make_unique<Subproject>();
    std::unique_ptr<Subproject> sub2 = std::make_unique<Subproject>();

    sub1->setName("SUB1");
    sub1->setDate(QDate(2025, 01, 29));
    sub1->setWorkAmount(100);
    sub1->setWorkDone(10);

    sub2->setName("SUB2");
    sub2->setDate(QDate(1991, 10, 15));
    sub2->setWorkAmount(100);
    sub2->setWorkDone(110);

    project->addSubproject(std::move(sub1));
    project->addSubproject(std::move(sub2));

    projects.push_back(std::move(project));
}

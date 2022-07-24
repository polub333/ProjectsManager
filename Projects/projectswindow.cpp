#include "projectswindow.h"
#include "ui_projectswindow.h"

ProjectsWindow::ProjectsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsWindow)
 //   selectedProject(*(new Project()))
{
    ui->setupUi(this);
    currentDateTime = QDateTime::currentDateTime();
    createTestProject();
    selectProject();
    showProjectInfo();
}

ProjectsWindow::~ProjectsWindow()
{
    delete ui;
}

void ProjectsWindow::selectProject()
{
    selectedProjectIt = projects.begin();
    //auto sp = projects[0].get();
    //selectedProject = *(*projects.begin());
}

void ProjectsWindow::showProjectInfo()
{
    showProjectNameInfo();
    showProjectDateInfo();
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
    projects.push_back(std::move(project));
}

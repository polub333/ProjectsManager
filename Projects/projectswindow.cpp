#include "projectswindow.h"
#include "ui_projectswindow.h"

ProjectsWindow::ProjectsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsWindow)
 //   selectedProject(*(new Project()))
{
    ui->setupUi(this);
//    selectedProject = Project();
    qDebug()<<1;
    createTestProject();
    qDebug()<<projects.size();
    selectProject();
    qDebug()<<projects.size();
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
    ui->nameLabel->setText((*selectedProjectIt)->getName());
    ui->descriptionLabel->setText((*selectedProjectIt)->getDescription());
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

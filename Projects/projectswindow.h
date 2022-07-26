#ifndef PROJECTSWINDOW_H
#define PROJECTSWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QStyle>

#include <vector>
#include <set>
#include <algorithm>
#include <memory>
#include <fstream>
#include <filesystem>
#include <string>

#include <Projects/project.h>
#include <Projects/subproject.h>
#include <Projects/entry.h>
#include <Projects/burndownscene.h>
#include <Projects/dailyworkscene.h>
#include <Projects/createprojectwindow.h>
#include <Projects/burndowndiagramwindow.h>
#include <Projects/dailyworkdiagramwindow.h>

namespace Ui {
class ProjectsWindow;
}

class ProjectsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectsWindow(QWidget *parent = nullptr);
    ~ProjectsWindow();

private:
    Ui::ProjectsWindow *ui;

    CreateProjectWindow* createProjectWindow;
    BurnDownDiagramWindow* burnDownDiagramWindow;
    DailyWorkDiagramWindow* dailyWorkDiagramWindow;

    BurnDownScene* burnDownScene;
    int sceneWidth;
    int sceneHeight;
    DailyWorkScene* dailyWorkScene;

    QDateTime currentDateTime;

    std::vector<std::unique_ptr<Project>> projects;
    std::vector<std::unique_ptr<Project>>::iterator selectedProjectIt;
    std::vector<std::unique_ptr<Project>>::iterator findProjectByName(const QString& name);
    std::set<QString> getProjectsNames();

    std::vector<std::unique_ptr<Entry>> entries;

    void updateData();
    void readData();
    void saveProjects();
    void saveProject(std::vector<std::unique_ptr<Project>>::iterator projectIt);
    void saveEntries();
    void saveEntry(std::vector<std::unique_ptr<Entry>>::iterator entryIt);


    void updateScreen();
    void showProjects();
    void showProjectInfo();
    void showBurnDownDiagram();
    void showDailyWorkDiagram();
    void showCurrentDate();
    void showProjectNameInfo();
    void showProjectDateInfo();
    void showProjectWorkInfo();
    void showProjectRewardInfo();
    void showProjectSubprojects();
    void showSubprojectInfo(
            std::vector<std::unique_ptr<Subproject>>::const_iterator subprojectIt);

    void selectProject(const std::vector<std::unique_ptr<Project>>::iterator iterator);
    void createTestProject();
    void readProjects();
    void createProjectFromFile(const QString& path);

    void readEntries(const QString& path);
    void readEntry(const std::string& path);
    void uniteSameDayEntries();
    void processEntries(const QDate& maxDate);
    void processEntry(std::vector<std::unique_ptr<Entry>>::iterator entryIt);
    void createDiagramPoints();

    void calculateProjects();
    void calculateProject(std::vector<std::unique_ptr<Project>>::iterator projectIt);
    void calculateProjectDateAndWork(std::vector<std::unique_ptr<Project>>::iterator projectIt);
    void calculateProjectReward(std::vector<std::unique_ptr<Project>>::iterator projectIt);

    void setBurnDownDiagramInfo();
    void setBurnDownDiagramEntries();
    void setBurnDownDiagramProjectInfo();

    void setDailyWorkDiagramInfo();
    void setDailyWorkDiagramEntries();
    void setDailyWorkDiagramProjectInfo();

    int checkAndSetProjectDaysGoneOrDaysRemaining(const int& days, const int& duration) const;
    int checkAndSetProjectWorkRemaining(const int& workRemaining) const;
    double checkAndSetProjectDailyWorkAmount(const int& work, const int& days) const;
    bool isEntryDataValid(const int& day, const int& month,
                          const int& year, const int& work) const;

    void clearLayout(QLayout* layout);

private slots:
    void addNewEntry();
    void mainMenuButtonClicked();
    void createNewProjectButtonClicked();
    void showBurnDownDiagramButtonClicked();
    void showDailyWorkDiagramButtonClicked();
    void saveData();

    void newProjectCreated();

signals:
    void openMainMenu();
};

#endif // PROJECTSWINDOW_H

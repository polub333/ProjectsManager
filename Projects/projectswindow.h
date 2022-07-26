#ifndef PROJECTSWINDOW_H
#define PROJECTSWINDOW_H

#include <QWidget>

#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>
#include <string>

#include <Projects/project.h>
#include <Projects/subproject.h>
#include <Projects/entry.h>

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

    std::vector<std::unique_ptr<Project>> projects;
    std::vector<std::unique_ptr<Project>>::iterator selectedProjectIt;
    std::vector<std::unique_ptr<Project>>::iterator findProjectByName(const QString& name);

    std::vector<std::unique_ptr<Entry>> entries;

    void showProjectInfo();
    void showProjectNameInfo();
    void showProjectDateInfo();
    void showProjectWorkInfo();
    void showProjectRewardInfo();
    void showProjectSubprojects();
    void showSubprojectInfo(
            std::vector<std::unique_ptr<Subproject>>::const_iterator subprojectIt);

    void selectProject(const std::vector<std::unique_ptr<Project>>::iterator iterator);
    void createTestProject();
    void createProjectFromFile(const QString& path);

    void readEntries(const QString& path);
    void readEntry(const std::string& path);
    void processEntries(const QDate& maxDate);
    void processEntry(std::vector<std::unique_ptr<Entry>>::iterator entryIt);

    void calculateProjects();
    void calculateProject(std::vector<std::unique_ptr<Project>>::iterator projectIt);
    void calculateProjectDateAndWork(std::vector<std::unique_ptr<Project>>::iterator projectIt);
    void calculateProjectReward(std::vector<std::unique_ptr<Project>>::iterator projectIt);

    int checkAndSetProjectDaysGoneOrDaysRemaining(const int& days, const int& duration) const;
    int checkAndSetProjectWorkRemaining(const int& workRemaining) const;
    double checkAndSetProjectDailyWorkAmount(const int& work, const int& days) const;

    QDateTime currentDateTime;

private slots:
    void addNewEntry();
    void mainMenuButtonClicked();

signals:
    void openMainMenu();
};

#endif // PROJECTSWINDOW_H

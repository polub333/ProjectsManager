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

    void showProjectInfo();
    void showProjectNameInfo();
    void showProjectDateInfo();
    void showProjectWorkInfo();
    void showProjectRewardInfo();
    void showProjectsSubprojects();
    void showSubprojectInfo(
            std::vector<std::unique_ptr<Subproject>>::const_iterator subprojectIt);

    void selectProject(const std::vector<std::unique_ptr<Project>>::iterator iterator);
    void createTestProject();
    void createProjectFromFile(const QString& path);

    void readEntries(const QString& path);
    void readEntry(const std::string& path);

    void recalculateProjects();

    QDateTime currentDateTime;
};

#endif // PROJECTSWINDOW_H

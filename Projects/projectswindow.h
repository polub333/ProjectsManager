#ifndef PROJECTSWINDOW_H
#define PROJECTSWINDOW_H

#include <QWidget>

#include <vector>

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

    std::vector<Project*> projects;
};

#endif // PROJECTSWINDOW_H

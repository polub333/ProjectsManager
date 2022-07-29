#ifndef CREATEPROJECTWINDOW_H
#define CREATEPROJECTWINDOW_H

#include <QWidget>
#include <QMessageBox>

#include <vector>
#include <set>
#include <fstream>

#include <Projects/subproject.h>

namespace Ui {
class CreateProjectWindow;
}

class CreateProjectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProjectWindow(QWidget *parent = nullptr);
    ~CreateProjectWindow();

    void init(std::set<QString> _projectsNames);

private:
    Ui::CreateProjectWindow *ui;
    std::vector<std::unique_ptr<Subproject>> subprojects;
    std::vector<std::unique_ptr<Subproject>>::iterator selectedSubprojectIt;
    int countSubprojectsWorkAmount();

    std::set<QString> projectsNames;

    void updateSubprojects();
    void selectSubproject(std::vector<std::unique_ptr<Subproject>>::iterator subprojectIt);
    void showSubprojectInfo();

    bool checkSubprojectData();

    void clearLayout(QLayout* layout);

private slots:
    void submitButtonClicked();
    void cancelButtonClicked();
    void newSubprojectButtonClicked();
    void okSubprojectButtonClicked();
    void deleteSubprojectButtonClicked();
signals:
    void newProjectCreated();
};

#endif // CREATEPROJECTWINDOW_H

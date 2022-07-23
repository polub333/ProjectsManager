#ifndef PROJECTSWINDOW_H
#define PROJECTSWINDOW_H

#include <QWidget>

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
};

#endif // PROJECTSWINDOW_H

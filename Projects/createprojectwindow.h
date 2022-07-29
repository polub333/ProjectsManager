#ifndef CREATEPROJECTWINDOW_H
#define CREATEPROJECTWINDOW_H

#include <QWidget>

namespace Ui {
class CreateProjectWindow;
}

class CreateProjectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProjectWindow(QWidget *parent = nullptr);
    ~CreateProjectWindow();

private:
    Ui::CreateProjectWindow *ui;
};

#endif // CREATEPROJECTWINDOW_H

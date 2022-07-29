#ifndef DAILYWORKDIAGRAMWINDOW_H
#define DAILYWORKDIAGRAMWINDOW_H

#include <QWidget>

namespace Ui {
class DailyWorkDiagramWindow;
}

class DailyWorkDiagramWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DailyWorkDiagramWindow(QWidget *parent = nullptr);
    ~DailyWorkDiagramWindow();

private:
    Ui::DailyWorkDiagramWindow *ui;
};

#endif // DAILYWORKDIAGRAMWINDOW_H

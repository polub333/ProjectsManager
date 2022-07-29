#ifndef BURNDOWNDIAGRAMWINDOW_H
#define BURNDOWNDIAGRAMWINDOW_H

#include <QWidget>

namespace Ui {
class BurnDownDiagramWindow;
}

class BurnDownDiagramWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BurnDownDiagramWindow(QWidget *parent = nullptr);
    ~BurnDownDiagramWindow();

private:
    Ui::BurnDownDiagramWindow *ui;
};

#endif // BURNDOWNDIAGRAMWINDOW_H

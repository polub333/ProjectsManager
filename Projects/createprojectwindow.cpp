#include "createprojectwindow.h"
#include "ui_createprojectwindow.h"

CreateProjectWindow::CreateProjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProjectWindow)
{
    ui->setupUi(this);

    ui->subprojectsLayout->setAlignment(Qt::AlignTop);

    connect(ui->submitButton, SIGNAL(clicked()), this, SLOT(submitButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->newSubprojectButton, SIGNAL(clicked()),
            this, SLOT(newSubprojectButtonClicked()));
    connect(ui->okSubprojectButton, SIGNAL(clicked()), this, SLOT(okSubprojectButtonClicked()));
    connect(ui->deleteSubprojectButton, SIGNAL(clicked()),
            this, SLOT(deleteSubprojectButtonClicked()));

    selectedSubprojectIt = subprojects.end();

}

CreateProjectWindow::~CreateProjectWindow()
{
    delete ui;
}

void CreateProjectWindow::init()
{
    ui->nameLineEdit->setText("");
    ui->descriptionLineEdit->setText("");
    ui->startDateDayLineEdit->setText("");
    ui->startDateMonthLineEdit->setText("");
    ui->startDateYearLineEdit->setText("");
    ui->endDateDayLineEdit->setText("");
    ui->endDateMonthLineEdit->setText("");
    ui->endDateYearLineEdit->setText("");
    ui->workAmountLineEdit->setText("");
    ui->dailyRewardLineEdit->setText("");
    ui->chainMultiplierLineEdit->setText("");
    ui->maxRewardLineEdit->setText("");

    ui->subprojectNameLineEdit->setText("");
    ui->subprojectDateDayLineEdit->setText("");
    ui->subprojectDateMonthLineEdit->setText("");
    ui->subprojectDateYearLineEdit->setText("");
    ui->subprojectWorkAmountLineEdit->setText("");

    clearLayout(ui->subprojectsLayout);
    showSubprojectInfo();

}

void CreateProjectWindow::updateSubprojects()
{
    clearLayout(ui->subprojectsLayout);
    for(auto it = subprojects.begin(); it != subprojects.end(); ++it){
        QWidget* widget = new QWidget(this);
        QHBoxLayout* layout = new QHBoxLayout();
        QLabel* name = new QLabel(this);
        name->setText((*it)->getName());
        QPushButton* button = new QPushButton(this);
        button->setText("Edit");
        connect(button, &QPushButton::clicked, this, [this, it](){this->selectSubproject(it);});
        layout->addWidget(name);
        layout->addWidget(button);
        widget->setLayout(layout);
        ui->subprojectsLayout->addWidget(widget);
    }
    showSubprojectInfo();
}

void CreateProjectWindow::selectSubproject(
        std::vector<std::unique_ptr<Subproject>>::iterator subprojectIt)
{
    selectedSubprojectIt = subprojectIt;
    showSubprojectInfo();
}

void CreateProjectWindow::showSubprojectInfo()
{
    if(selectedSubprojectIt == subprojects.end()){
        ui->subprojectNameLineEdit->setText("");
        ui->subprojectDateDayLineEdit->setText("");
        ui->subprojectDateMonthLineEdit->setText("");
        ui->subprojectDateYearLineEdit->setText("");
        ui->subprojectWorkAmountLineEdit->setText("");
        ui->subprojectNameLineEdit->setDisabled(true);
        ui->subprojectDateDayLineEdit->setDisabled(true);
        ui->subprojectDateMonthLineEdit->setDisabled(true);
        ui->subprojectDateYearLineEdit->setDisabled(true);
        ui->subprojectWorkAmountLineEdit->setDisabled(true);
        ui->okSubprojectButton->setDisabled(true);
        ui->deleteSubprojectButton->setDisabled(true);
    }
    else{
        ui->subprojectNameLineEdit->setText((*selectedSubprojectIt)->getName());
        ui->subprojectDateDayLineEdit->setText(
                    QString::number((*selectedSubprojectIt)->getDate().day()));
        ui->subprojectDateMonthLineEdit->setText(
                    QString::number((*selectedSubprojectIt)->getDate().month()));
        ui->subprojectDateYearLineEdit->setText(
                    QString::number((*selectedSubprojectIt)->getDate().year()));
        ui->subprojectWorkAmountLineEdit->setText(
                    QString::number((*selectedSubprojectIt)->getWorkAmount()));
        ui->subprojectNameLineEdit->setDisabled(false);
        ui->subprojectDateDayLineEdit->setDisabled(false);
        ui->subprojectDateMonthLineEdit->setDisabled(false);
        ui->subprojectDateYearLineEdit->setDisabled(false);
        ui->subprojectWorkAmountLineEdit->setDisabled(false);
        ui->okSubprojectButton->setDisabled(false);
        ui->deleteSubprojectButton->setDisabled(false);
    }
}

bool CreateProjectWindow::checkSubprojectData()
{
    int year = ui->subprojectDateYearLineEdit->text().toInt();
    int month = ui->subprojectDateMonthLineEdit->text().toInt();
    int day = ui->subprojectDateDayLineEdit->text().toInt();
    int work = ui->subprojectWorkAmountLineEdit->text().toInt();
    if(!QDate::isValid(year, month, day) || work < 0){
        return false;
    }
    return true;
}

void CreateProjectWindow::submitButtonClicked()
{

}

void CreateProjectWindow::cancelButtonClicked()
{
    hide();
}

void CreateProjectWindow::newSubprojectButtonClicked()
{
    std::unique_ptr<Subproject> subproject = std::make_unique<Subproject>();
    subproject->setName("Subproject");
    subproject->setDate(QDate(1, 1, 1));
    subproject->setWorkAmount(0);
    subprojects.push_back(std::move(subproject));
    selectedSubprojectIt = subprojects.end() - 1;
    updateSubprojects();
}

void CreateProjectWindow::okSubprojectButtonClicked()
{
    if(selectedSubprojectIt == subprojects.end()){
        return;
    }
    if(!checkSubprojectData()){
        QMessageBox msg(QMessageBox::Critical, "Invalid Data",
                        "Some of the entered data is invalid", QMessageBox::Ok);
        msg.exec();
    }
    else{
        (*selectedSubprojectIt)->setName(ui->subprojectNameLineEdit->text());
        (*selectedSubprojectIt)->setDate(QDate(ui->subprojectDateYearLineEdit->text().toInt(),
                                         ui->subprojectDateMonthLineEdit->text().toInt(),
                                         ui->subprojectDateDayLineEdit->text().toInt()));
        (*selectedSubprojectIt)->setWorkAmount(ui->subprojectWorkAmountLineEdit->text().toInt());
        updateSubprojects();
    }
}

void CreateProjectWindow::deleteSubprojectButtonClicked()
{
    if(selectedSubprojectIt == subprojects.end()){
        return;
    }
    subprojects.erase(selectedSubprojectIt);
    selectedSubprojectIt = subprojects.end();
    updateSubprojects();
}

void CreateProjectWindow::clearLayout(QLayout* layout)
{
    QLayoutItem* lItem = layout->takeAt(0);
    while(lItem != nullptr){
        if(lItem->layout() != nullptr){
            clearLayout(lItem->layout());
            delete lItem->layout();
        }
        else{
            delete lItem->widget();
        }
        lItem = layout->takeAt(0);
    }
    delete lItem;
}

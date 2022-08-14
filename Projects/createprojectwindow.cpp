#include "createprojectwindow.h"
#include "ui_createprojectwindow.h"

CreateProjectWindow::CreateProjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProjectWindow)
{
    ui->setupUi(this);

    setWindowTitle("Create Project");
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

int CreateProjectWindow::countSubprojectsWorkAmount()
{
    int res = 0;
    for(auto it = subprojects.begin(); it != subprojects.end() ;++it){
        res += (*it)->getWorkAmount();
    }
    return res;
}

void CreateProjectWindow::init(std::set<QString> _projectsNames)
{
    projectsNames = _projectsNames;

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


bool CreateProjectWindow::checkProjectData()
{
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionLineEdit->text();

    bool *ok1 = new bool, *ok2 = new bool, *ok3 = new bool, *ok4 = new bool, *ok5 = new bool,
         *ok6 = new bool, *ok7 = new bool, *ok8 = new bool, *ok9 = new bool, *ok10 = new bool;

    int startDateDay = ui->startDateDayLineEdit->text().toInt(ok1);
    int startDateMonth = ui->startDateMonthLineEdit->text().toInt(ok2);
    int startDateYear = ui->startDateYearLineEdit->text().toInt(ok3);
    int endDateDay = ui->endDateDayLineEdit->text().toInt(ok4);
    int endDateMonth = ui->endDateMonthLineEdit->text().toInt(ok5);
    int endDateYear = ui->endDateYearLineEdit->text().toInt(ok6);

    int workAmount = ui->workAmountLineEdit->text().toInt(ok7);
    double dailyReward = ui->dailyRewardLineEdit->text().toDouble(ok8);
    double chainMultiplier = ui->chainMultiplierLineEdit->text().toDouble(ok9);
    double maxDailyReward = ui->maxRewardLineEdit->text().toDouble(ok10);

    QDateTime startDate, endDate;
    startDate.setDate(QDate(startDateYear, startDateMonth, startDateDay));
    endDate.setDate(QDate(endDateYear, endDateMonth, endDateDay));

    QMessageBox msg(QMessageBox::Critical, "Invalid Data",
                    "Some of entered data is invalid:\n", QMessageBox::Ok);
    bool aborted = false;

    if(name == "" || description == "" || !(*ok1) || !(*ok2) || !(*ok3) || !(*ok4) ||!(*ok5) ||
       !(*ok6) || !(*ok7) || !(*ok8) || !(*ok9) || !(*ok10)){
        msg.setText(msg.text() + "Fields cannot be empty and data fields must be valid\n");
        aborted = true;
    }
    if(projectsNames.find(name) != projectsNames.end()){
        msg.setText(msg.text() + "Project with such name already exists\n");
        aborted = true;
    }
    if(!QDate::isValid(startDateYear, startDateMonth, startDateDay)){
        msg.setText(msg.text() + "Invalid start date\n");
        aborted = true;
    }
    if(!QDate::isValid(endDateYear, endDateMonth, endDateDay)){
        msg.setText(msg.text() + "Invalid end date\n");
        aborted = true;
    }
    if(endDate < startDate){
        msg.setText(msg.text() + "End date cannot be less than start date\n");
        aborted = true;
    }
    if(workAmount <= 0){
        msg.setText(msg.text() + "Work amount couldn't be less than 1\n");
        aborted = true;
    }
    if(maxDailyReward < dailyReward){
        msg.setText(msg.text() + "Maximal daily reward couldn't be less than daily reward\n");
        aborted = true;
    }
    if(countSubprojectsWorkAmount() != workAmount && subprojects.size() != 0){
        msg.setText(msg.text() + "Sum of work amounts of subprojects must be equal to " +
                                 "project's work amount\n");
        aborted = true;
    }

    if(aborted){
        msg.exec();
        return false;
    }
    return true;
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
    QString name = ui->nameLineEdit->text();
    QString description = ui->descriptionLineEdit->text();

    int startDateDay = ui->startDateDayLineEdit->text().toInt();
    int startDateMonth = ui->startDateMonthLineEdit->text().toInt();
    int startDateYear = ui->startDateYearLineEdit->text().toInt();
    int endDateDay = ui->endDateDayLineEdit->text().toInt();
    int endDateMonth = ui->endDateMonthLineEdit->text().toInt();
    int endDateYear = ui->endDateYearLineEdit->text().toInt();

    int workAmount = ui->workAmountLineEdit->text().toInt();
    double dailyReward = ui->dailyRewardLineEdit->text().toDouble();
    double chainMultiplier = ui->chainMultiplierLineEdit->text().toDouble();
    double maxDailyReward = ui->maxRewardLineEdit->text().toDouble();

    if(!checkProjectData()){
        return;
    }

    QString path = "Projects/" + name + ".txt";
    std::fstream file(path.toStdString(), std::ios_base::out);
    file<<name.toStdString()<<std::endl;
    file<<description.toStdString()<<std::endl;
    file<<startDateDay<<std::endl;
    file<<startDateMonth<<std::endl;
    file<<startDateYear<<std::endl;
    file<<endDateDay<<std::endl;
    file<<endDateMonth<<std::endl;
    file<<endDateYear<<std::endl;
    file<<workAmount<<std::endl;
    file<<dailyReward<<std::endl;
    file<<chainMultiplier<<std::endl;
    file<<maxDailyReward<<std::endl;
    file<<subprojects.size()<<std::endl;
    for(auto it = subprojects.begin(); it != subprojects.end(); ++it){
        file<<(*it)->getName().toStdString()<<std::endl;
        QDate date = (*it)->getDate();
        file<<date.day()<<std::endl;
        file<<date.month()<<std::endl;
        file<<date.year()<<std::endl;
        file<<workAmount<<std::endl;
    }
    file.close();
    emit newProjectCreated();
    hide();
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

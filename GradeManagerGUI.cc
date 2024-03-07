//
// Created by Justin Daludado on 2024-02-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GradeManagerGUI.h" resolved

#include "GradeManagerGUI.h"
#include "ui_GradeManagerGUI.h"



GradeManagerGUI::GradeManagerGUI(QWidget *parent) :
    QWidget(parent), ui(new Ui::GradeManagerGUI) {
    ui->setupUi(this);
    connect(ui->addCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::openAddCourseDialog);
    connect(ui->courseListWidget, &QListWidget::itemSelectionChanged, this, &GradeManagerGUI::updateCourseInfo);
    populateCourseList();
}

GradeManagerGUI::~GradeManagerGUI() {
    delete ui;
}

void GradeManagerGUI::openAddCourseDialog() const
{
    auto *addCourseDialog = new AddCourseDialog;
    connect(addCourseDialog, &AddCourseDialog::courseDataSubmitted, this, &GradeManagerGUI::handleCourseData);
    addCourseDialog->setModal(true);
    addCourseDialog->exec();
}

void GradeManagerGUI::handleCourseData(const QString &courseName, const QString &courseCode, const QString &courseDescription, const QString &courseCredits) {
    Course* course = new Course(courseName.toStdString(), courseCode.toStdString(), courseDescription.toStdString(), "Fall", courseCredits.toFloat());
    gradeManager.addCourse(course);
    populateCourseList();
}

void GradeManagerGUI::populateCourseList() const {
    ui->courseListWidget->clear();
    auto courses = gradeManager.getCourses();
    for (const auto& course : courses) {
        ui->courseListWidget->addItem(QString::fromStdString(course->getCourseName()));
    }
}

void GradeManagerGUI::updateCourseInfo() const {
    QListWidgetItem* selectedItem = ui->courseListWidget->currentItem();
    if (selectedItem) {
        std::string selectedCourseName = selectedItem->text().toStdString();
        for (const auto& course : gradeManager.getCourses()) {
            if (course->getCourseName() == selectedCourseName) {
                // Assuming courseInfoWidget is a QTextEdit or similar widget
                ui->courseInfoWidget->setText(QString::fromStdString(course->print()));
                break;
            }
        }
    }
}
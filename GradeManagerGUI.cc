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
    populateCourseList();
}

GradeManagerGUI::~GradeManagerGUI() {
    delete ui;
}

void GradeManagerGUI::openAddCourseDialog() {
    auto *addCourseDialog = new AddCourseDialog;
    connect(addCourseDialog, &AddCourseDialog::courseDataSubmitted, this, &GradeManagerGUI::handleCourseData);
    addCourseDialog->setModal(true);
    addCourseDialog->exec();
}

void GradeManagerGUI::handleCourseData(const QString &courseName, const QString &courseCode, const QString &courseDescription, const QString &courseCredits) {
    // Handle course data here
    // You can access the course data from the dialog with the parameters
    // You can use the gradeManager object to add the course to the database
    Course course(courseName.toStdString(), courseCode.toStdString(), courseDescription.toStdString(), courseCredits.toStdString());
    gradeManager.addCourse(&course);
    populateCourseList();
}

void GradeManagerGUI::populateCourseList() {
    ui->courseListWidget->clear();
    auto courses = gradeManager.getCourses();
    for (const auto& course : courses) {
        ui->courseListWidget->addItem(QString::fromStdString(course->getCourseName()));
    }
}
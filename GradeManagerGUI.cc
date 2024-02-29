//
// Created by Justin Daludado on 2024-02-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GradeManagerGUI.h" resolved

#include "GradeManagerGUI.h"
#include "ui_GradeManagerGUI.h"



GradeManagerGUI::GradeManagerGUI(QWidget *parent) :
    QWidget(parent), ui(new Ui::GradeManagerGUI) {
    ui->setupUi(this);
    GradeManager gradeManager;
    gradeManager.openDatabase();

    connect(ui->addCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::openAddCourseDialog);
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
    cout << "Course Name: " << courseName.toStdString() << endl;
    cout << "Course Code: " << courseCode.toStdString() << endl;
    cout << "Course Description: " << courseDescription.toStdString() << endl;
    cout << "Course Credits: " << courseCredits.toStdString() << endl;
}
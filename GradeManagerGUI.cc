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
    AddCourseDialog addCourseDialog;
    addCourseDialog.setModal(true);
    addCourseDialog.exec();
}

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
    connect(ui->removeCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::removeSelectedCourse);
    connect(ui->editCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::editSelectedCourse);
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

void GradeManagerGUI::handleCourseData(const QString &courseName, const QString &courseCode, const QString &courseInstructor,
        const QString &courseCredits, const QString &courseTerm) {
    for (auto& course : gradeManager.getCourses()) {
        if (course->getCourseName() == courseName.toStdString()) {
            // Update existing course
            course->setCourseCode(courseCode.toStdString());
            course->setProf(courseInstructor.toStdString());
            course->setTerm(courseTerm.toStdString());
            course->setCreditWorth(courseCredits.toFloat());
            gradeManager.updateCourseInDatabase(course);
            populateCourseList();
            return;
        }
    }
    // Add new course
    Course* course = new Course(courseName.toStdString(), courseCode.toStdString(), courseInstructor.toStdString(), courseTerm.toStdString(), courseCredits.toFloat());
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
                ui->courseInfoWidget->setText(QString::fromStdString(course->print()));
                break;
            }
        }
    }
}

void GradeManagerGUI::removeSelectedCourse()  {
    QListWidgetItem* selectedItem = ui->courseListWidget->currentItem();
    if (selectedItem) {
        string selectedCourseName = selectedItem->text().toStdString();
        gradeManager.removeCourse(selectedCourseName);
        populateCourseList();
        ui->courseInfoWidget->clear();
    }
}

void GradeManagerGUI::editSelectedCourse() {
    QListWidgetItem* selectedItem = ui->courseListWidget->currentItem();
    if (selectedItem) {
        std::string selectedCourseName = selectedItem->text().toStdString();
        for (const auto& course : gradeManager.getCourses()) {
            if (course->getCourseName() == selectedCourseName) {
                auto *addCourseDialog = new AddCourseDialog(course);
                connect(addCourseDialog, &AddCourseDialog::courseDataSubmitted, this, &GradeManagerGUI::handleCourseData);
                addCourseDialog->setModal(true);
                addCourseDialog->exec();
                break;
            }
        }
    }
}
//
// Created by Justin Daludado on 2024-02-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GradeManagerGUI.h" resolved

#include "GradeManagerGUI.h"
#include "AddCourseDialog.h"
#include "AddGradeDialog.h"
#include "ui_GradeManagerGUI.h"

#include <QMessageBox>


GradeManagerGUI::GradeManagerGUI(QWidget *parent) :
    QWidget(parent), ui(new Ui::GradeManagerGUI) {
    ui->setupUi(this);
    vector<Course*> courses = gradeManager.getCourses();
    addGradeDialog = new AddGradeDialog(courses);
    connect(ui->addCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::openAddCourseDialog);
    connect(ui->courseListWidget, &QListWidget::itemSelectionChanged, this, &GradeManagerGUI::updateCourseInfo);
    connect(ui->removeCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::removeSelectedCourse);
    connect(ui->editCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::editSelectedCourse);
    populateCourseList();
    connect(ui->addGradeButton, &QPushButton::clicked, this, &GradeManagerGUI::openAddGradeDialog);
    connect(ui->courseListWidget, &QListWidget::itemSelectionChanged, this, &GradeManagerGUI::populateGradeList);
}

GradeManagerGUI::~GradeManagerGUI() {
    delete ui;
}

// Course Handling

void GradeManagerGUI::openAddCourseDialog() const
{
    auto *addCourseDialog = new AddCourseDialog;
    connect(addCourseDialog, &AddCourseDialog::courseDataSubmitted, this, &GradeManagerGUI::handleCourseData);
    addCourseDialog->setModal(true);
    addCourseDialog->exec();
}

void GradeManagerGUI::handleCourseData(const QString &originalCourseName, const QString &courseName, const QString &courseCode, const QString &courseInstructor,
        const QString &courseCredits, const QString &courseTerm) {
    for (auto& course : gradeManager.getCourses()) {
        if (course->getCourseName() == originalCourseName.toStdString()) {
            // Update existing course
            course->setCourseName(courseName.toStdString());
            course->setCourseCode(courseCode.toStdString());
            course->setProf(courseInstructor.toStdString());
            course->setTerm(courseTerm.toStdString());
            course->setCreditWorth(courseCredits.toFloat());
            gradeManager.updateCourseInDatabase(originalCourseName.toStdString(), course);
            populateCourseList();
            ui->courseInfoWidget->clear();
            return;
        }
    }
    // Add new course
    auto* course = new Course(courseName.toStdString(), courseCode.toStdString(), courseInstructor.toStdString(), courseTerm.toStdString(), courseCredits.toFloat());
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
        string selectedCourseName = selectedItem->text().toStdString();
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
        string selectedCourseName = selectedItem->text().toStdString();
        for (const auto& course : gradeManager.getCourses()) {
            if (course->getCourseName() == selectedCourseName) {
                auto *addCourseDialog = new AddCourseDialog(course);
                connect(addCourseDialog, &AddCourseDialog::courseDataSubmitted, this, [this](const QString &originalCourseName, const QString &courseName, const QString &courseCode, const QString &courseInstructor,
                    const QString &courseCredits, const QString &courseTerm) {
                    handleCourseData(originalCourseName, courseName, courseCode, courseInstructor, courseCredits, courseTerm);
                });
                addCourseDialog->setModal(true);
                addCourseDialog->exec();
                break;
            }
        }
    }
}

// Grade Handling
void GradeManagerGUI::openAddGradeDialog() const {
    std::vector<Course*> courses = gradeManager.getCourses();
    if (courses.empty()) {
        QMessageBox::information(nullptr, "No Courses", "You must add a course before adding a grade.");
        return;
    }
    connect(addGradeDialog, &AddGradeDialog::gradeDataSubmitted, this, &GradeManagerGUI::handleGradeData);
    addGradeDialog->setModal(true);
    addGradeDialog->exec();
}

void GradeManagerGUI::handleGradeData(const QString &originalGradeName, const QString &gradeName, const QString &gradeType, const QString &gradeMark, const QString &gradeWeight) {
    std::string selectedCourseCode = addGradeDialog->getSelectedCourseCode().toStdString();
    for (auto& course : gradeManager.getCourses()) {
        if (course->getCourseCode() == selectedCourseCode) {
            // Create a new grade
            auto* grade = new Grade(gradeMark.toStdString(), gradeName.toStdString(), gradeType.toStdString(), gradeWeight.toFloat());
            // Add the new grade to the course
            course->addGrade(grade);
            // Add the new grade to the database
            gradeManager.addGradeToDatabase(course, grade);
            // Update the grade list widget
            populateGradeList();
            return;
        }
    }
}

void GradeManagerGUI::populateGradeList() const {
    ui->gradeListWidget->clear();
    QListWidgetItem* selectedItem = ui->courseListWidget->currentItem();
    if (selectedItem) {
        std::string selectedCourseName = selectedItem->text().toStdString();
        for (const auto& course : gradeManager.getCourses()) {
            if (course->getCourseName() == selectedCourseName) {
                for (const auto& grade : course->getGrades()) {
                    ui->gradeListWidget->addItem(QString::fromStdString(grade->getName()));
                }
                break;
            }
        }
    }

}

void GradeManagerGUI::updateGradeInfo() const {
    QListWidgetItem* selectedGrade = ui->gradeListWidget->currentItem();
    if (selectedGrade) {
        string selectedGradeName = selectedGrade->text().toStdString();
        string selectedCourseCode = addGradeDialog->getSelectedCourseCode().toStdString();
        for (auto &course : gradeManager.getCourses()) {
            if (course->getCourseCode() == selectedCourseCode) {
                for (auto& grade : course->getGrades()) {
                    if (selectedGradeName == grade->getName()) {
                        ui->gradeInfoWidget->setText(QString::fromStdString(grade->print()));
                        return;
                    }
                }
            }
        }
    }
}
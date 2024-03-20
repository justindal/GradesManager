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
    // vector<Course*> courses = gradeManager.getCourses();
    // addGradeDialog = new AddGradeDialog(courses);
    connect(ui->addCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::openAddCourseDialog);
    connect(ui->courseListWidget, &QListWidget::itemSelectionChanged, this, &GradeManagerGUI::updateCourseInfo);
    connect(ui->removeCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::removeSelectedCourse);
    connect(ui->editCourseButton, &QPushButton::clicked, this, &GradeManagerGUI::editSelectedCourse);
    populateCourseList();
    connect(ui->addGradeButton, &QPushButton::clicked, this, &GradeManagerGUI::openAddGradeDialog);
    connect(ui->courseListWidget, &QListWidget::itemSelectionChanged, this, &GradeManagerGUI::populateGradeList);
    connect(ui->gradeListWidget, &QListWidget::itemSelectionChanged, this, &GradeManagerGUI::updateGradeInfoWidget);
    connect(ui->removeGradeButton, &QPushButton::clicked, this, &GradeManagerGUI::removeSelectedGrade);
    connect(ui->editGradeButton, &QPushButton::clicked, this, &GradeManagerGUI::editSelectedGrade);
}

GradeManagerGUI::~GradeManagerGUI() {
    delete ui;
}

Course* GradeManagerGUI::getSelectedCourse() const {
    if (ui->courseListWidget->currentItem()) {
        const auto selectedName = ui->courseListWidget->currentItem()->text().toStdString();
        for (const auto& course : gradeManager.getCourses()) {
            if (course->getCourseName() == selectedName) {
                return course;
            }
        }
    }
    return nullptr;
}

Grade* GradeManagerGUI::getSelectedGrade() const {
    if (ui->gradeListWidget->currentItem()) {
        const auto selectedName = ui->gradeListWidget->currentItem()->text().toStdString();
        for (const auto& course : gradeManager.getCourses()) {
            for (const auto& grade : course->getGrades()) {
                if (grade->getName() == selectedName) {
                    return grade;
                }
            }
        }
    }
    return nullptr;
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

    auto *addGradeDialog = new AddGradeDialog(courses);
    connect(addGradeDialog, &AddGradeDialog::gradeDataSubmitted, this, &GradeManagerGUI::handleGradeData);
    addGradeDialog->setModal(true);
    addGradeDialog->exec();
}

void GradeManagerGUI::handleGradeData(const QString &originalGradeName, const QString &gradeName, const QString &gradeType, const QString &gradeMark, const QString &gradeWeight) {
    for (auto& course : gradeManager.getCourses()) {
        if (course->getCourseCode() == getSelectedCourse()->getCourseCode()) {
            for (auto& grade : course->getGrades()) {
                if (grade->getName() == originalGradeName.toStdString()) {
                    // Update existing grade
                    grade->setName(gradeName.toStdString());
                    grade->setType(gradeType.toStdString());
                    grade->setMark(gradeMark.toStdString());
                    grade->setWeight(gradeWeight.toFloat());
                    gradeManager.updateGradeInDatabase(course->getCourseName(), originalGradeName.toStdString(), grade);
                    populateGradeList();
                    ui->gradeInfoWidget->clear();
                    return;
                }
            }
            // Add new grade
            auto* grade = new Grade(gradeName.toStdString(), gradeType.toStdString(), gradeMark.toStdString(), gradeWeight.toFloat());
            course->addGrade(grade);
            gradeManager.addGradeToDatabase(course, grade);
            populateGradeList();
            return;
        }
    }
}

void GradeManagerGUI::populateGradeList() const {
    ui->gradeListWidget->clear();
    if (getSelectedCourse()) {
        for (const auto& grade : getSelectedCourse()->getGrades()) {
            ui->gradeListWidget->addItem(QString::fromStdString(grade->getName()));
        }
    }

}

void GradeManagerGUI::updateGradeInfoWidget() const {
    if (getSelectedGrade()) {
        ui->gradeInfoWidget->setText(QString::fromStdString(getSelectedGrade()->print()));
    }
}

void GradeManagerGUI::removeSelectedGrade() {
    if (getSelectedGrade()) {
        string selectedCourseName = getSelectedCourse()->getCourseName();
        string selectedGradeName = getSelectedGrade()->getName();
        getSelectedCourse()->removeGrade(getSelectedGrade());
        gradeManager.removeGradeFromDatabase(selectedCourseName, selectedGradeName);
        populateGradeList();
        ui->gradeInfoWidget->clear();
    }
}

void GradeManagerGUI::editSelectedGrade() {
    if (getSelectedGrade()) {
        string selectedCourseName = getSelectedCourse()->getCourseName();
        string selectedGradeName = getSelectedGrade()->getName();
        auto courses = gradeManager.getCourses();
        auto *addGradeDialog = new AddGradeDialog(courses, getSelectedGrade());
        connect(addGradeDialog, &AddGradeDialog::gradeDataSubmitted, this, [this](const QString &originalGradeName, const QString &gradeName, const QString &gradeType, const QString &gradeMark, const QString &gradeWeight) {
            handleGradeData(originalGradeName, gradeName, gradeType, gradeMark, gradeWeight);
        });
        addGradeDialog->setModal(true);
        addGradeDialog->exec();
    }
}
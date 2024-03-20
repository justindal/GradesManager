#include "AddCourseDialog.h"
#include "ui_GradeManagerGUI.h"
#include <QFormLayout>
#include <QMessageBox>


AddCourseDialog::AddCourseDialog(const Course* course, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Course");

    const auto layout = new QFormLayout(this);

    courseNameEdit = new QLineEdit(this);
    layout->addRow("Course Name:", courseNameEdit);
    // Add QLineEdit fields for other course details
    courseCodeEdit = new QLineEdit(this);
    layout->addRow("Course Code:", courseCodeEdit);

    courseInstructorEdit = new QLineEdit(this);
    layout->addRow("Instructor:", courseInstructorEdit);

    courseTermEdit = new QLineEdit(this);
    layout->addRow("Term:", courseTermEdit);

    courseCreditsEdit = new QLineEdit(this);
    layout->addRow("Credit Worth:", courseCreditsEdit);

    const auto submitButton = new QPushButton("Submit", this);
    layout->addWidget(submitButton);

    if (course) {
        originalCourseName = QString::fromStdString(course->getCourseName());
        courseNameEdit->setText(QString::fromStdString(course->getCourseName()));
        courseCodeEdit->setText(QString::fromStdString(course->getCourseCode()));
        courseInstructorEdit->setText(QString::fromStdString(course->getProf()));
        courseTermEdit->setText(QString::fromStdString(course->getTerm()));
        courseCreditsEdit->setText(QString::number(course->getCreditWorth()));
        setWindowTitle("Edit Course");
    }

    connect(submitButton, &QPushButton::clicked, this, &AddCourseDialog::submitForm);
}

void AddCourseDialog::submitForm() {
    const QString courseName = courseNameEdit->text();
    const QString courseCode = courseCodeEdit->text();
    const QString courseInstructor = courseInstructorEdit->text();
    const QString courseTerm = courseTermEdit->text();
    const QString courseCredits = courseCreditsEdit->text();

    if (courseName.isEmpty() || courseCode.isEmpty() || courseInstructor.isEmpty() || courseTerm.isEmpty() || courseCredits.isEmpty()) {
        QMessageBox::information(this, "Empty Fields", "Please fill all the fields before submitting.");
        return;
    }

    emit courseDataSubmitted(originalCourseName, courseNameEdit->text(), courseCodeEdit->text(), courseInstructorEdit->text(),
        courseCreditsEdit->text(), courseTermEdit->text());
    accept();  // Close the dialog
}
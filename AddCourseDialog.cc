#include "AddCourseDialog.h"
#include "ui_GradeManagerGUI.h"


AddCourseDialog::AddCourseDialog(Course* course, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Course");

    auto layout = new QFormLayout(this);

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

    auto submitButton = new QPushButton("Submit", this);
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
    // Handle form submission here
    // You can access the text entered in the QLineEdit with courseNameEdit->text()
    emit courseDataSubmitted(originalCourseName, courseNameEdit->text(), courseCodeEdit->text(), courseInstructorEdit->text(),
        courseCreditsEdit->text(), courseTermEdit->text());
    accept();  // Close the dialog
}
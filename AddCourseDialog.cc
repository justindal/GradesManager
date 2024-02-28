#include "AddCourseDialog.h"

AddCourseDialog::AddCourseDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Course");

    auto layout = new QFormLayout(this);

    courseNameEdit = new QLineEdit(this);
    layout->addRow("Course Name:", courseNameEdit);

    // Add QLineEdit fields for other course details
    auto courseCodeEdit = new QLineEdit(this);
    layout->addRow("Course Code:", courseCodeEdit);

    auto courseDescriptionEdit = new QLineEdit(this);
    layout->addRow("Course Description:", courseDescriptionEdit);

    auto courseCreditsEdit = new QLineEdit(this);
    layout->addRow("Course Credits:", courseCreditsEdit);

    auto submitButton = new QPushButton("Submit", this);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &AddCourseDialog::submitForm);
}

void AddCourseDialog::submitForm() {
    // Handle form submission here
    // You can access the text entered in the QLineEdit with courseNameEdit->text()

    accept();  // Close the dialog
}
#include "AddGradeDialog.h"
#include "GradeManagerGUI.h"
#include "ui_GradeManagerGUI.h"
#include <QPushButton>
#include <QFormLayout>


AddGradeDialog::AddGradeDialog(vector<Course*>& courses, Grade* grade, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Grade");

    const auto layout = new QFormLayout(this);

    // drop down for course selection
    courseSelection = new QComboBox(this);
    layout->addRow("Course:", courseSelection);

    for (const auto& course : courses) {
        courseSelection->addItem(QString::fromStdString(course->getCourseCode()));
    }

    gradeNameEdit = new QLineEdit(this);
    layout->addRow("Grade Name:", gradeNameEdit);

    gradeTypeEdit = new QLineEdit(this);
    layout->addRow("Grade Type:", gradeTypeEdit);

    gradeMarkEdit = new QLineEdit(this);
    layout->addRow("Grade Mark:", gradeMarkEdit);

    gradeWeightEdit = new QLineEdit(this);
    layout->addRow("Grade Weight:", gradeWeightEdit);

    const auto submitButton = new QPushButton("Submit", this);
    layout->addWidget(submitButton);

    if (grade) {
        originalGradeName = QString::fromStdString(grade->getName());
        gradeNameEdit->setText(QString::fromStdString(grade->getName()));
        gradeTypeEdit->setText(QString::fromStdString(grade->getType()));
        gradeMarkEdit->setText(QString::fromStdString(grade->getMark()));
        gradeWeightEdit->setText(QString::number(grade->getWeight()));
        setWindowTitle("Edit Grade");
    }

    connect(submitButton, &QPushButton::clicked, this, &AddGradeDialog::submitForm);
}

void AddGradeDialog::submitForm() {
    emit gradeDataSubmitted(originalGradeName, gradeNameEdit->text(), gradeTypeEdit->text(), gradeMarkEdit->text(), gradeWeightEdit->text());
    accept();
}

QString AddGradeDialog::getSelectedCourseCode() const {
    return courseSelection->currentText();
}
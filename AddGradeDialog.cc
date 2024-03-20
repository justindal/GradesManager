#include "AddGradeDialog.h"
#include "GradeManagerGUI.h"
#include "ui_GradeManagerGUI.h"
#include <QFormLayout>
#include <QMessageBox>


AddGradeDialog::AddGradeDialog(const vector<Course*>& courses, const Grade* grade, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Grade");

    const auto layout = new QFormLayout(this);

    if (!grade) {
        courseSelection = new QComboBox(this);
        layout->addRow("Course:", courseSelection);
        for (const auto& course : courses) {
            courseSelection->addItem(QString::fromStdString(course->getCourseCode()));
        }
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
    const QString gradeName = gradeNameEdit->text();
    const QString gradeType = gradeTypeEdit->text();
    const QString gradeMark = gradeMarkEdit->text();
    const QString gradeWeight = gradeWeightEdit->text();

    // Check if any of the fields are empty
    if (gradeName.isEmpty() || gradeType.isEmpty() || gradeMark.isEmpty() || gradeWeight.isEmpty()) {
        QMessageBox::information(this, "Empty Fields", "Please fill all the fields before submitting.");
        return;
    }

    emit gradeDataSubmitted(originalGradeName, gradeNameEdit->text(), gradeTypeEdit->text(), gradeMarkEdit->text(), gradeWeightEdit->text());
    accept();
}

QString AddGradeDialog::getSelectedCourseCode() const {
    return courseSelection->currentText();
}
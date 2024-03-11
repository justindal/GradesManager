#ifndef ADDCOURSEDIALOG_H
#define ADDCOURSEDIALOG_H

#include <QDialog>
#include <QLineEdit>


#include "Course.h"

class AddCourseDialog final: public QDialog {
    Q_OBJECT

public:
    explicit AddCourseDialog(Course* course = nullptr, QWidget *parent = nullptr);

private:
    QLineEdit *courseNameEdit;
    QLineEdit *courseCodeEdit;
    QLineEdit *courseInstructorEdit;
    QLineEdit *courseCreditsEdit;
    QLineEdit *courseTermEdit;
    QString originalCourseName;

private slots:
        void submitForm();

signals:
    void courseDataSubmitted(const QString &originalCourseName, const QString &courseName, const QString &courseCode, const QString &courseInstructor,
        const QString &courseCredits, const QString &courseTerm);
};

#endif // ADDCOURSEDIALOG_H
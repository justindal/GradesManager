#ifndef ADDCOURSEDIALOG_H
#define ADDCOURSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class AddCourseDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddCourseDialog(QWidget *parent = nullptr);

private:
    QLineEdit *courseNameEdit;
    QLineEdit *courseCodeEdit;
    QLineEdit *courseInstructorEdit;
    QLineEdit *courseCreditsEdit;
    QLineEdit *courseTermEdit;

private slots:
        void submitForm();

signals:
    void courseDataSubmitted(const QString &courseName, const QString &courseCode, const QString &courseInstructor,
        const QString &courseCredits, const QString &courseTerm);
};

#endif // ADDCOURSEDIALOG_H
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
    QLineEdit *courseDescriptionEdit;
    QLineEdit *courseCreditsEdit;

private slots:
        void submitForm();

signals:
    void courseDataSubmitted(const QString &courseName, const QString &courseCode, const QString &courseDescription,
        const QString &courseCredits);
};

#endif // ADDCOURSEDIALOG_H
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

    private slots:
        void submitForm();

private:
private:
    QLineEdit *courseNameEdit;
    QLineEdit *courseCodeEdit;
    QLineEdit *courseDescriptionEdit;
    QLineEdit *courseCreditsEdit;
};

#endif // ADDCOURSEDIALOG_H
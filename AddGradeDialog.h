#ifndef ADDGRADEDIALOG_H
#define ADDGRADEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "Grade.h"
#include "Course.h"

class AddGradeDialog final: public QDialog {
    Q_OBJECT

public:
    explicit AddGradeDialog(vector<Course*> &courses, Grade* grade = nullptr, QWidget *parent = nullptr);
    [[nodiscard]] QString getSelectedCourseCode() const;

private:
    QComboBox *courseSelection;
    QLineEdit *gradeNameEdit;
    QLineEdit *gradeTypeEdit;
    QLineEdit *gradeMarkEdit;
    QLineEdit *gradeWeightEdit;
    QString originalGradeName;

private slots:
    void submitForm();

signals:
    void gradeDataSubmitted(const QString &original, const QString &gradeName, const QString &gradeType, const QString &gradeMark, const QString &gradeWeight);

};



#endif //ADDGRADEDIALOG_H

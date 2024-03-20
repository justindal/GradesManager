//
// Created by Justin Daludado on 2024-02-28.
//

#ifndef GRADEMANAGERGUI_H
#define GRADEMANAGERGUI_H

#include <QWidget>
#include <QString>
#include <QtWidgets/qlistwidget.h>

#include "AddCourseDialog.h"
#include "AddGradeDialog.h"
#include "GradeManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GradeManagerGUI; }
QT_END_NAMESPACE

class GradeManagerGUI final: public QWidget {
Q_OBJECT

public:
    explicit GradeManagerGUI(QWidget *parent = nullptr);
    ~GradeManagerGUI() override;
    Course* getSelectedCourse() const;
    Grade* getSelectedGrade() const;
    void updateOverallGradeLabel() const;

private slots:
    void openAddCourseDialog() const;
    void handleCourseData(const QString &originalCourseName, const QString &courseName, const QString &courseCode, const QString &courseInstructor,
        const QString &courseCredits, const QString &courseTerm);
    void populateCourseList() const;
    void updateCourseInfo() const;
    void removeSelectedCourse();
    void editSelectedCourse();

    void openAddGradeDialog() const;
    void handleGradeData(const QString &originalGradeName, const QString &gradeName, const QString &gradeType, const QString &gradeMark, const QString &gradeWeight);
    void populateGradeList() const;
    void updateGradeInfoWidget() const;
    void removeSelectedGrade();
    void editSelectedGrade();

private:
    Ui::GradeManagerGUI *ui;
    GradeManager gradeManager;
};


#endif //GRADEMANAGERGUI_H

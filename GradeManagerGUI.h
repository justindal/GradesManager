//
// Created by Justin Daludado on 2024-02-28.
//

#ifndef GRADEMANAGERGUI_H
#define GRADEMANAGERGUI_H

#include <QWidget>
#include "GradeManager.h"
#include "AddCourseDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GradeManagerGUI; }
QT_END_NAMESPACE

class GradeManagerGUI : public QWidget {
Q_OBJECT

public:
    explicit GradeManagerGUI(QWidget *parent = nullptr);
    ~GradeManagerGUI() override;

private slots:
    void openAddCourseDialog() const;
    void handleCourseData(const QString &courseName, const QString &courseCode, const QString &courseInstructor,
        const QString &courseCredits, const QString &courseTerm);
    void populateCourseList() const;
    void updateCourseInfo() const;
    void removeSelectedCourse();
    void editSelectedCourse();

private:
    Ui::GradeManagerGUI *ui;
    GradeManager gradeManager;
};


#endif //GRADEMANAGERGUI_H

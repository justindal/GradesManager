#include "GradeManager.h"

int main()
{
    GradeManager *gradeManager = new GradeManager();
    gradeManager->loadCourses();
    gradeManager->printCourses();
    delete gradeManager;
    return 0;
}
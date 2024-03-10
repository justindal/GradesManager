#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include <string>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include "Course.h"

using namespace std;

class GradeManager {

public:
    // Constructors and Destructors
    GradeManager();
    ~GradeManager();

    // Database Methods
    bool openDatabase();
    void closeDatabase();
    bool executeSQL(const string& sql) const;
    bool initializeDatabase() const;

    // Accessors
    [[nodiscard]] vector<Course*> getCourses() const;
    void setCourses(const vector<Course*>& courses);

    // Other Methods
    void addCourse(Course* course);
    Course* removeCourse(const string& courseName);
    void printCourses() const;
    void addGradeToCourse(int index, Grade* grade);
    void removeGradeFromCourse(int courseIndex, int gradeIndex);
    void readCoursesFromDatabase();
    void updateCourseInDatabase(const string& courseName, Course* course) const;

private:
    std::vector<Course*> courses;
    QSqlDatabase db;
};



#endif //GRADEMANAGER_H

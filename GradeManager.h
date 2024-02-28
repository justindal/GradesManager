#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <vector>
#include <string>
#include <sqlite3.h>
#include "Course.h"


class GradeManager {

public:
    // Constructors and Destructors
    GradeManager();
    ~GradeManager();
    // Database Methods
    bool openDatabase();
    void closeDatabase() const;
    bool executeSQL(const std::string& sql) const;

    // Accessors
    [[nodiscard]] std::vector<Course*> getCourses() const;
    void setCourses(const std::vector<Course*>& courses);

    // Other Methods
    void addCourse(Course* course);
    Course* removeCourse(int index);
    void printCourses() const;
    void addGradeToCourse(int index, Grade* grade);
    void removeGradeFromCourse(int courseIndex, int gradeIndex);

private:
    std::vector<Course*> courses;
    sqlite3* db;
};



#endif //GRADEMANAGER_H

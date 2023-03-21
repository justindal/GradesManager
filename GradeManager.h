#ifndef GRADEMANAGER_H
#define GRADEMANAGER_H

#include <string>
#include <vector>
#include <iostream>

#include "Grade.h"
#include "Course.h"

using namespace std;

class GradeManager
{
    public:
        // Constructors and Destructors
        GradeManager();

        // Accessors
        vector<Course *> getCourses() const;
        void setCourses(vector<Course *>& courses);

        // Other Methods
        void addCourse(Course *course);
        void removeCourse(Course *course);
        void printCourses() const;
        void printCourse(Course *course) const;
        void printGrades(Course *course) const;
        void printGrade(Grade *grade) const;
        bool saveCourses() const;
        bool loadCourses();


    private:
        vector<Course *> courses;
        int numCourses;

};


#endif

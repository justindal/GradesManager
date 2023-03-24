#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Grade.h"

using namespace std;

class Course
{
    public:
        // Constructors and Destructors
        Course(const string& courseName, const string& prof, const string& term);

        // Accessors
        string getCourseName() const;
        void setCourseName(const string& courseName);
        int getNumGrades() const;
        void setNumGrades(int numGrades);
        vector<Grade *> getGrades() const;
        void setGrades(vector<Grade *>& grades);
        string getProf() const;
        void setProf(const string& prof);
        string getTerm() const;
        void setTerm(const string& term);
        float getMark() const;
        void setMark(float mark);
        Grade *getGradeAt(int index) const;

        // Other Methods
        void addGrade(Grade *grade);
        Grade* removeGrade(int index);
        void printGrades() const;
        void printCourse() const;
        void print() const;
        void printLetterGrade() const;
        void calculateMark();

        // Overloaded Operators
        friend ostream& operator<<(ostream& out, const Course& course);


        

    private:
        string courseName;
        int numGrades;
        vector<Grade *> grades;
        string prof;
        string term;
        float mark;
};

#endif
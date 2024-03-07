#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>

#include "Grade.h"

using namespace std;

class Course
{
    public:
        // Constructors and Destructors
        Course(const string& courseName, const string& courseCode, const string& prof, const string& term,
            float creditWorth);
        Course(const string& courseName, const string& courseCode, const string& prof, const string& term,
           const int numGrades, const float mark, const float creditWorth);
        Course();
        ~Course();

        // Accessors
        [[nodiscard]] string getCourseName() const;
        void setCourseName(const string& courseName);
        [[nodiscard]] int getNumGrades() const;
        void setNumGrades(int numGrades);
        [[nodiscard]] vector<Grade *> getGrades() const;
        void setGrades(vector<Grade *>& grades);
        [[nodiscard]] string getProf() const;
        void setProf(const string& prof);
        [[nodiscard]] string getTerm() const;
        void setTerm(const string& term);
        [[nodiscard]] float getMark() const;
        void setMark(float mark);
        [[nodiscard]] Grade *getGradeAt(int index) const;
        [[nodiscard]] string getCourseCode() const;
        void setCourseCode(const string& courseCode);
        [[nodiscard]] float getAverage() const;
        [[nodiscard]] float getCreditWorth() const;
        void setCreditWorth(float creditWorth);

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
        string courseCode;
        int numGrades{};
        vector<Grade *> grades;
        string prof;
        string term;
        float mark{};
        float creditWorth{};
};

#endif

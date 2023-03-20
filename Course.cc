#include "Course.h"

Course::Course(const string &courseName, const string &prof, const string &term)
{
    this->courseName = courseName;
    this->prof = prof;
    this->term = term;
    numGrades = 0;
}

string Course::getCourseName() const
{
    return courseName;
}

void Course::setCourseName(const string &courseName)
{
    this->courseName = courseName;
}

int Course::getNumGrades() const
{
    return numGrades;
}

void Course::setNumGrades(int numGrades)
{
    this->numGrades = numGrades;
}

vector<Grade *> Course::getGrades() const
{
    return grades;
}

void Course::setGrades(vector<Grade *> &grades)
{
    this->grades = grades;
}

string Course::getProf() const
{
    return prof;
}

void Course::setProf(const string &prof)
{
    this->prof = prof;
}

string Course::getTerm() const
{
    return term;
}

void Course::setTerm(const string &term)
{
    this->term = term;
}

float Course::getMark() const
{
    return mark;
}

void Course::setMark(float mark)
{
    this->mark = mark;
}

void Course::addGrade(Grade *grade)
{
    grades.push_back(grade);
    numGrades++;
}

Grade *Course::removeGrade(int index)
{
    Grade *grade = grades[index];
    grades.erase(grades.begin() + index);
    numGrades--;
    return grade;
}

void Course::printGrades() const
{
    for (int i = 0; i < numGrades; i++)
    {
        cout << "Grade " << i + 1 << ": " << grades[i]->getName() << " - " << grades[i]->getMark() << "%" << endl;
    }
}

void Course::printCourse() const
{
    cout << "Course Name: " << courseName << endl;
    cout << "Professor: " << prof << endl;
    cout << "Term: " << term << endl;
    cout << "Number of Grades: " << numGrades << endl;
    cout << "Average Mark: " << mark << "%" << endl;
}

void Course::printLetterGrade() const
{
    if (mark >= 90)
    {
        cout << "Letter Grade: A+" << endl;
    }
    else if (mark >= 85)
    {
        cout << "Letter Grade: A" << endl;
    }
    else if (mark >= 80)
    {
        cout << "Letter Grade: A-" << endl;
    }
    else if (mark >= 77)
    {
        cout << "Letter Grade: B+" << endl;
    }
    else if (mark >= 73)
    {
        cout << "Letter Grade: B" << endl;
    }
    else if (mark >= 70)
    {
        cout << "Letter Grade: B-" << endl;
    }
    else if (mark >= 67)
    {
        cout << "Letter Grade: C+" << endl;
    }
    else if (mark >= 63)
    {
        cout << "Letter Grade: C" << endl;
    }
    else if (mark >= 60)
    {
        cout << "Letter Grade: C-" << endl;
    }
    else if (mark >= 57)
    {
        cout << "Letter Grade: D+" << endl;
    }
    else if (mark >= 53)
    {
        cout << "Letter Grade: D" << endl;
    }
    else if (mark >= 50)
    {
        cout << "Letter Grade: D-" << endl;
    }
    else
    {
        cout << "Letter Grade: F" << endl;
    }
}
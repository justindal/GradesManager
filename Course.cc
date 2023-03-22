#include "Course.h"
#include <ostream>

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
    string mark = grade->getMark();
    int numerator = stoi(mark.substr(0, mark.find("/")));
    int denominator = stoi(mark.substr(mark.find("/") + 1));
    float percentage = (float) numerator / (float) denominator * 100;
    grade->setPercentageMark(percentage);
    calculateMark();
    grade->calculateLetterGrade();
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
        grades[i]->print();
    }
}

void Course::printCourse() const
{
    cout << "COURSE NAME: " << courseName << endl;
    cout << "--------------------------" << endl;
    cout << "Professor: " << prof << endl;
    cout << "Term: " << term << endl;
    cout << "Number of Grades: " << numGrades << endl;
    cout << "Current Course Average: " << mark << "%" << endl;
    cout << "GRADES: " << endl;
    cout << "--------------------------" << endl;
    printGrades();
    
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

void Course::calculateMark()
{
    // Calculate the average mark of all the grades using the percentage mark and the weight
    float total = 0;
    for (int i = 0; i < numGrades; i++)
    {
        total += grades[i]->getPercentageMark() * grades[i]->getWeight();
    }
    mark = total;
}

ostream &operator<<(ostream &out, const Course &course)
{
    out << "courseName: " <<course.getCourseName() << ':' << endl;
    out << '{' << endl;
    out << "\t" << "numGrades: " << course.getNumGrades() << ',' << endl;
    out << "\t" << "prof: " << course.getProf() << ',' <<endl;
    out << "\t" << "term: " << course.getTerm() << ',' <<endl;
    out << "\t" << "grades: " << endl;
    out << "\t" << '{' << endl;
    for (int i = 0; i < course.getNumGrades(); i++)
    {
        out << *course.getGrades()[i] << endl;
    }
    out << "\t}" << endl;
    out << '}' << endl;
    return out;
}
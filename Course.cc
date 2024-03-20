//
// Created by Justin Daludado on 2024-02-25.
//

#include "Course.h"

#include <iomanip>
#include <sstream>

Course::Course(const string& courseName, const string& courseCode, const string& prof, const string& term, const float creditWorth) {
    this->courseName = courseName;
    this->courseCode = courseCode;
    this->prof = prof;
    this->term = term;
    this->creditWorth = creditWorth;
}

Course::Course(const string& courseName, const string& courseCode, const string& prof, const string& term,
    const int numGrades, const float mark, const float creditWorth) {
    this->courseName = courseName;
    this->courseCode = courseCode;
    this->prof = prof;
    this->term = term;
    this->numGrades = numGrades;
    this->mark = mark;
    this->creditWorth = creditWorth;
}

Course::Course() {
    this->courseName = "";
    this->courseCode = "";
    this->prof = "";
    this->term = "";
}

// Accessors
[[nodiscard]] string Course::getCourseName() const {
    return courseName;
}

void Course::setCourseName(const string& courseName) {
    this->courseName = courseName;
}

[[nodiscard]] int Course::getNumGrades() const {
    return numGrades;
}

void Course::setNumGrades(const int numGrades) {
    this->numGrades = numGrades;
}

[[nodiscard]] vector<Grade *> Course::getGrades() const {
    return grades;
}

void Course::setGrades(const vector<Grade *>& grades) {
    this->grades = grades;
}

[[nodiscard]] string Course::getProf() const {
    return prof;
}

void Course::setProf(const string& prof) {
    this->prof = prof;
}

[[nodiscard]] string Course::getTerm() const {
    return term;
}

void Course::setTerm(const string& term) {
    this->term = term;
}

[[nodiscard]] float Course::getMark() const {
    return mark;
}

void Course::setMark(const float mark) {
    this->mark = mark;
}

[[nodiscard]] Grade *Course::getGradeAt(const int index) const {
    return grades.at(index);
}

[[nodiscard]] string Course::getCourseCode() const {
    return courseCode;
}

void Course::setCourseCode(const string& courseCode) {
    this->courseCode = courseCode;
}

[[nodiscard]] float Course::getCreditWorth() const {
    return creditWorth;
}

void Course::setCreditWorth(const float creditWorth) {
    this->creditWorth = creditWorth;
}

[[nodiscard]] float Course::getAverage() const {
    float sum = 0;

    if (getNumGrades() == 0)
        return 0;

    for (auto & grade : grades) {
        string mark = grade->getMark();
        const unsigned int slashIndex = mark.find('/');
        sum += stof(mark.substr(0, slashIndex)) / stof(mark.substr(slashIndex + 1)) * grade->getWeight();
    }
    return sum / numGrades;
}

// Other Methods
void Course::addGrade(Grade *grade) {
    grades.push_back(grade);
    numGrades++;
}

Grade* Course::removeGrade(const int index) {
    Grade* grade = grades.at(index);
    grades.erase(grades.begin() + index);
    numGrades--;
    return grade;
}

Grade* Course::removeGrade(Grade *grade) {
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        if (*it == grade) {
            grades.erase(it);
            numGrades--;
            return grade;
        }
    }
    return nullptr;
}

void Course::printGrades() const {
    for (auto & grade : grades) {
        cout << *grade << endl;
    }
}

void Course::printCourse() const {
    cout << "Course Name: " << courseName << endl;
    cout << "Course Code: " << courseCode << endl;
    cout << "Professor: " << prof << endl;
    cout << "Term: " << term << endl;
    cout << "Mark: " << mark << endl;
    cout << "Number of Grades: " << numGrades << endl;
    printGrades();
}

string Course::print() const {
    ostringstream output;
    output << std::fixed << std::setprecision(2);
    output << "Course Name: " << courseName << "\n\n";
    output << "Course Code: " << courseCode << "\n\n";
    output << "Professor: " << prof << "\n\n";
    output << "Term: " << term << "\n\n";
    output << "Credit Worth: " << creditWorth << "\n\n";
    output << "Mark: " << getAverage() * 100 << "%\n\n";

    return output.str();
}

// Overloaded Operators
ostream& operator<<(ostream& out, const Course& course) {
    out << "Course Name: " << course.courseName << endl;
    out << "Course Code: " << course.courseCode << endl;
    out << "Professor: " << course.prof << endl;
    out << "Term: " << course.term << endl;
    out << "Mark: " << course.mark << endl;
    out << "Number of Grades: " << course.numGrades << endl;
    for (auto & grade : course.grades) {
        out << *grade << endl;
    }
    return out;
}

Course::~Course() {
    for (const auto & grade : grades) {
        delete grade;
    }
}
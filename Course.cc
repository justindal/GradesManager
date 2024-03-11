//
// Created by Justin Daludado on 2024-02-25.
//

#include "Course.h"

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

void Course::setGrades(vector<Grade *>& grades) {
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
    // todo
    return 0;
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

    string output = "Course Name: " + courseName + "\n\n" +
                    "Course Code: " + courseCode + "\n\n" +
                    "Professor: " + prof + "\n\n" +
                    "Term: " + term + "\n\n" +
                    "Credit Worth: " + to_string(creditWorth) + "\n\n" +
                        "Mark: " + to_string(mark);
    return output;

}

void Course::printLetterGrade() const {
    cout << "Course Name: " << courseName << endl;
    cout << "Course Code: " << courseCode << endl;
    cout << "Professor: " << prof << endl;
    cout << "Term: " << term << endl;
    cout << "Mark: " << mark << endl;
    for (auto & grade : grades) {
        cout << *grade << endl;
    }
}

void Course::calculateMark() {
    // todo
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
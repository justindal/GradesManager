//
// Created by Justin Daludado on 2024-02-25.
//

#include "Grade.h"

Grade::Grade(const string& mark, const string& name, const string& type, float weight) {
    this->mark = mark;
    this->name = name;
    this->type = type;
    this->weight = weight;
}

Grade::Grade() {
    this->mark = "";
    this->name = "";
    this->type = "";
    this->weight = 0;
}

string Grade::getMark() const {
    return mark;
}

void Grade::setMark(const string& mark) {
    this->mark = mark;
}

string Grade::getName() const {
    return name;
}

void Grade::setName(const string& name) {
    this->name = name;
}

string Grade::getType() const {
    return type;
}

void Grade::setType(const string& type) {
    this->type = type;
}

float Grade::getWeight() const {
    return weight;
}

void Grade::setWeight(float weight) {
    this->weight = weight;
}

void Grade::printGrade() const {
    cout << "Name: " << name << endl;
    cout << "Type: " << type << endl;
    cout << "Mark: " << mark << endl;
    cout << "Weight: " << weight << endl;
}

string Grade::print() const {
    string output;
    output += "Name: " + name + "\n";
    output += "Type: " + type + "\n";
    output += "Mark: " + mark + "\n";
    output += "Weight: " + to_string(weight) + "\n";
    return output;
}

void Grade::calculateLetterGrade() {
    // if (percentageMark >= 90) {
    //     letterGrade = "A+";
    // } else if (percentageMark >= 85) {
    //     letterGrade = "A";
    // } else if (percentageMark >= 80) {
    //     letterGrade = "A-";
    // } else if (percentageMark >= 77) {
    //     letterGrade = "B+";
    // } else if (percentageMark >= 73) {
    //     letterGrade = "B";
    // } else if (percentageMark >= 70) {
    //     letterGrade = "B-";
    // } else if (percentageMark >= 67) {
    //     letterGrade = "C+";
    // } else if (percentageMark >= 63) {
    //     letterGrade = "C";
    // } else if (percentageMark >= 60) {
    //     letterGrade = "C-";
    // } else if (percentageMark >= 57) {
    //     letterGrade = "D+";
    // } else if (percentageMark >= 53) {
    //     letterGrade = "D";
    // } else if (percentageMark >= 50) {
    //     letterGrade = "D-";
    // } else {
    //     letterGrade = "F";
    // }
}

ostream& operator<<(ostream& out, const Grade& grade) {
    out << "Name: " << grade.name << endl;
    out << "Type: " << grade.type << endl;
    out << "Mark: " << grade.mark << endl;
    out << "Weight: " << grade.weight << endl;
    return out;
}
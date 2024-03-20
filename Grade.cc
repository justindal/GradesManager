//
// Created by Justin Daludado on 2024-02-25.
//

#include "Grade.h"
#include <iomanip>
#include <sstream>

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
    ostringstream output;
    output << std::fixed << std::setprecision(2);
    output << "Name: " << name << "\n\n";
    output << "Type: " << type << "\n\n";
    output << "Mark: " << mark << "\n\n";
    output << "Weight: " << weight * 100 << "%\n";
    return output.str();
}


ostream& operator<<(ostream& out, const Grade& grade) {
    out << "Name: " << grade.name << endl;
    out << "Type: " << grade.type << endl;
    out << "Mark: " << grade.mark << endl;
    out << "Weight: " << grade.weight << endl;
    return out;
}
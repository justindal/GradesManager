//
// Created by Justin Daludado on 2024-02-25.
//

#ifndef GRADE_H
#define GRADE_H

#include <iostream>
#include <string>

using namespace std;

class Grade {
public:
    // Constructors and Destructors
    Grade(const string& mark, const string& name, const string& type, float weight, const string& letterGrade);
    Grade(const string& mark, const string& name, const string& type, float weight);
    Grade();

    // Accessors
    [[nodiscard]] string getMark() const;
    void setMark(const string& mark);
    [[nodiscard]] string getName() const;
    void setName(const string& name);
    [[nodiscard]] string getType() const;
    void setType(const string& type);
    [[nodiscard]] string getLetterGrade() const;
    void setLetterGrade(const string& letterGrade);
    [[nodiscard]] float getWeight() const;
    void setWeight(float weight);
    [[nodiscard]] float getPercentageMark() const;
    void setPercentageMark(float percentageMark);

    // Other Methods
    void printGrade() const;
    void print() const;
    void calculateLetterGrade();

    // Overloaded Operators
    friend ostream& operator<<(ostream& out, const Grade& grade);

private:
    string mark;
    string name;
    string type;
    string letterGrade;
    float weight;
    float percentageMark{};
};



#endif //GRADE_H

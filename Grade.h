#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Grade
{
    public:
        // Constructors and Destructors
        Grade(string mark, string name, string type, float weight);

        // Accessors
        string getMark() const;
        void setMark(string mark);
        string getName() const;
        void setName(const string& name);
        string getType() const;
        void setType(const string& type);
        string getLetterGrade() const;
        void setLetterGrade(const string& letterGrade);
        float getWeight() const;
        void setWeight(float weight);

        // Other Methods
        void printGrade() const;

        //
        friend ostream& operator<<(ostream& out, const Grade& grade);

    private:
        string mark;
        string name;
        string type;
        string letterGrade;
        float weight;
};

#endif
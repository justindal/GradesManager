#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <iostream>

using namespace std;

class Grade
{
    public:
        // Constructors and Destructors
        Grade();
        ~Grade();

        // Accessors
        float getMark() const;
        void setMark(float mark);
        string getName() const;
        void setName(const string& name);
        string getType() const;
        void setType(const string& type);
        string getLetterGrade() const;
        void setLetterGrade(const string& letterGrade);

    private:
        float mark;
        string name;
        string type;
        string letterGrade;
        float weight;
};

#endif
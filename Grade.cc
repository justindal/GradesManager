#include "Grade.h"
#include <istream>

Grade::Grade(const string& mark, const string& name, const string& type, float weight, const string& letterGrade)
{
    this->mark = mark;
    this->name = name;
    this->type = type;
    this->weight = weight;
    this->letterGrade = letterGrade;
}

Grade::Grade(const string& mark, const string& name, const string& type, float weight)
{
    this->mark = mark;
    this->name = name;
    this->type = type;
    this->weight = weight;
}

// default constructor
Grade::Grade()
{
    mark = "";
    name = "";
    type = "";
    weight = 0;
    letterGrade = "";
}

string Grade::getMark() const
{
    return mark;
}

void Grade::setMark(string mark)
{
    this->mark = mark;
    calculateLetterGrade();
}

string Grade::getName() const
{
    return name;
}

void Grade::setName(const string &name)
{
    this->name = name;
}

string Grade::getType() const
{
    return type;
}

void Grade::setType(const string &type)
{
    this->type = type;
}

string Grade::getLetterGrade() const
{
    return letterGrade;
}

void Grade::setLetterGrade(const string &letterGrade)
{
    this->letterGrade = letterGrade;
}

float Grade::getWeight() const
{
    return weight;
}

void Grade::setWeight(float weight)
{
    this->weight = weight;
}

float Grade::getPercentageMark() const
{
    return percentageMark;
}

void Grade::setPercentageMark(float percentageMark)
{
    this->percentageMark = percentageMark;
}

void Grade::printGrade() const
{
    cout << "Name: " << name << endl;
    cout << "Type: " << type << endl;
    cout << "Mark: " << mark << endl;
    cout << "Weight: " << weight << endl;
    cout << "Letter Grade: " << letterGrade << endl;
}

void Grade::print() const
{
    cout << name << ": " << percentageMark << "% (" << letterGrade << ")" << endl;
}

void Grade::calculateLetterGrade()
{
    if (percentageMark >= 90)
    {
        letterGrade = "A+";
    }
    else if (percentageMark >= 85)
    {
        letterGrade = "A";
    }
    else if (percentageMark >= 80)
    {
        letterGrade = "A-";
    }
    else if (percentageMark >= 77)
    {
        letterGrade = "B+";
    }
    else if (percentageMark >= 73)
    {
        letterGrade = "B";
    }
    else if (percentageMark >= 70)
    {
        letterGrade = "B-";
    }
    else if (percentageMark >= 67)
    {
        letterGrade = "C+";
    }
    else if (percentageMark >= 63)
    {
        letterGrade = "C";
    }
    else if (percentageMark >= 60)
    {
        letterGrade = "C-";
    }
    else if (percentageMark >= 57)
    {
        letterGrade = "D+";
    }
    else if (percentageMark >= 53)
    {
        letterGrade = "D";
    }
    else if (percentageMark >= 50)
    {
        letterGrade = "D-";
    }
    else
    {
        letterGrade = "F";
    }
}

ostream &operator<<(ostream &out, const Grade &grade)
{
    out << "\t\tname: " << grade.getName() << ":" << endl;
    out << "\t\t{" << endl;
    out << "\t\t\tmark: " << grade.getMark() << ',' <<endl;
    out << "\t\t\ttype: " << grade.getType() << ',' <<endl;
    out << "\t\t\tweight: " << grade.getWeight() << ',' <<endl;
    out << "\t\t\tletter grade: " << grade.getLetterGrade() <<endl;
    out << "\t\t}" << endl;
    return out;
}


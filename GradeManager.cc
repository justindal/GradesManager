#include "GradeManager.h"

GradeManager::GradeManager() { numCourses = 0; }


vector<Course *> GradeManager::getCourses() const { return courses; }

void GradeManager::setCourses(vector<Course *> &courses)
{
    this->courses = courses;
}

void GradeManager::addCourse(Course *course)
{
    courses.push_back(course);
    numCourses++;
}

Course *GradeManager::removeCourse(int index)
{
    Course *course = courses[index-1];
    courses.erase(courses.begin() + index-1);
    numCourses--;
    return course;
}

int GradeManager::getNumCourses() const { return numCourses; }

void GradeManager::setNumCourses(int numCourses)
{
    this->numCourses = numCourses;
}

void GradeManager::printCourses() const
{
    if (numCourses == 0)
    {
        cout << "No courses loaded!" << endl;
        return;
    }

    cout << "Currently Loaded Courses:" << endl;
    for (int i = 0; i < numCourses; i++)
    {
        cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
    }
}

void GradeManager::printCourse(Course *course) const
{
    cout << *course << endl;
}

void GradeManager::printGrades(Course *course) const { course->printGrades(); }

void GradeManager::printGrade(Grade *grade) const { cout << *grade << endl; }

bool GradeManager::saveCourses() const
{
    ofstream file;
    file.open("courses.txt");
    if (file.is_open())
    {
        file << "numCourses: " << numCourses << ',' << endl;
        for (int i = 0; i < numCourses; i++)
        {
            file << *courses[i] << endl;
        }
        file.close();
        cout << "Courses saved successfully!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool GradeManager::loadCourses()
{
    ifstream file;
    string line;
    string courseName;
    string prof;
    string term;
    int numGrades;
    string name;
    string mark;
    string type;
    double weight;
    string letterGrade;
    Grade *grade = new Grade();
    Course *course = new Course();
    file.open("courses.txt");
    cout << "Loading courses.txt as follows..." << endl;

    // check if file contains data
    if (file.peek() == ifstream::traits_type::eof())
    {
        cout << "File is empty!" << endl;
        return false;
    }

    if (file.is_open())
    {
        getline(file, line);
        numCourses = stoi(line.substr(line.find(":") + 1, line.find(",") - 1));
        cout << "numCourses: " << numCourses <<endl;
        for (int i = 0; i < numCourses; i++)
        {
            getline(file, line);
            courseName = line.substr(line.find(":") + 2, line.find(","));
            courseName.pop_back();
            cout << "courseName: " << courseName << endl;
            getline(file, line);
            getline(file, line);
            numGrades = stoi(line.substr(line.find(":") + 1, line.find(",") - 1));
            cout << "numGrades: " << numGrades << endl;
            getline(file, line);
            prof = line.substr(line.find(":") + 2, line.find(","));
            prof.pop_back();
            cout << "prof: " << prof << endl;
            getline(file, line);
            term = line.substr(line.find(":") + 2, line.find(","));
            term.pop_back();
            cout << "term: " << term << endl;
            course->setCourseName(courseName);
            course->setProf(prof);
            course->setTerm(term);
            getline(file, line);
            getline(file, line);

            for (int j = 0; j < numGrades; j++)
            {
                // keep reading lines if there is a bracket or empty line
                while (line.find("{") != string::npos || line.find("}") != string::npos || line.empty())
                {
                    getline(file, line);
                }
                name = line.substr(line.find(":") + 2, line.find(",") - 1);
                name.pop_back();
                cout << "name: " << name << endl;
                getline(file, line);
                getline(file, line);
                mark = line.substr(line.find(":") + 2, line.find(",") - 1);
                mark.pop_back();
                cout << "mark: " << mark << endl;
                getline(file, line);
                type = line.substr(line.find(":") + 2, line.find(",") - 1);
                type.pop_back();
                cout << "type: " << type << endl;
                getline(file, line);
                weight = stod(line.substr(line.find(":") + 1, line.find(",") - 1));
                cout << "weight: " << weight << endl;
                getline(file, line);
                letterGrade = line.substr(line.find(":") + 2, line.find("\n"));
                cout << "letterGrade: " << letterGrade << endl;
                getline(file, line);
                cout << "\n" << endl;
                grade->setMark(mark);
                grade->setType(type);
                grade->setWeight(weight);
                grade->setName(name);
                grade->setLetterGrade(letterGrade);
                course->addGrade(grade);
            }
            if (numGrades == 0)
            {
                getline(file, line);
                getline(file, line);
                getline(file, line);
            }
            else 
            {
                getline(file, line);
                getline(file, line);
                getline(file, line);
                getline(file, line);
            }
            if (course != nullptr)
            {
                courses.push_back(course);
            }
            cin.clear();
            cout << "course " << i + 1 << " loaded successfully!" << endl;
        }
        delete grade;
        file.close();
        cout << "loaded successfully!" << endl;
        return true;
    }
    return false;
}

Course *GradeManager::getCourseAt(int index) const { return courses[index-1]; }

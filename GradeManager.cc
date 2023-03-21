#include "GradeManager.h"

GradeManager::GradeManager()
{
    numCourses = 0;
}

vector<Course *> GradeManager::getCourses() const
{
    return courses;
}

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
    Course *course = courses[index];
    courses.erase(courses.begin() + index);
    numCourses--;
    return course;
}

void GradeManager::printCourses() const
{
    for (int i = 0; i < numCourses; i++)
    {
        courses[i]->printCourse();
    }
}

void GradeManager::printCourse(Course *course) const
{
    cout << *course << endl;
}

void GradeManager::printGrades(Course *course) const
{
    course->printGrades();
}

void GradeManager::printGrade(Grade *grade) const
{
    cout << *grade << endl;
}

bool GradeManager::saveCourses() const
{
    ofstream file;
    file.open("courses.txt");
    if (file.is_open())
    {
        for (int i = 0; i < numCourses; i++)
        {
            file << *courses[i] << endl;
        }
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool GradeManager::loadCourses()
{
    return false;
}
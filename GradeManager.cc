#include "GradeManager.h"
#include <string>

GradeManager::GradeManager() { numCourses = 0; }

vector<Course *> GradeManager::getCourses() const { return courses; }

void GradeManager::setCourses(vector<Course *> &courses) {
  this->courses = courses;
}

void GradeManager::addCourse(Course *course) {
  courses.push_back(course);
  numCourses++;
}

Course *GradeManager::removeCourse(int index) {
  Course *course = courses[index];
  courses.erase(courses.begin() + index);
  numCourses--;
  return course;
}

int GradeManager::getNumCourses() const { return numCourses; }

void GradeManager::setNumCourses(int numCourses) {
  this->numCourses = numCourses;
}

void GradeManager::printCourses() const {
  for (int i = 0; i < numCourses; i++) {
    courses[i]->printCourse();
  }
}

void GradeManager::printCourse(Course *course) const {
  cout << *course << endl;
}

void GradeManager::printGrades(Course *course) const { course->printGrades(); }

void GradeManager::printGrade(Grade *grade) const { cout << *grade << endl; }

bool GradeManager::saveCourses() const {
  ofstream file;
  file.open("courses.txt");
  if (file.is_open()) {
    file << "numCourses: " << numCourses << ',' << endl;
    for (int i = 0; i < numCourses; i++) {
      file << *courses[i] << endl;
    }
    file.close();
    cout << "Courses saved successfully!" << endl;
    return true;
  } else {
    return false;
  }
}

bool GradeManager::loadCourses() {
  /*

      numCourses: 2,
courseName: Software Engineering:
{
      numGrades: 2,
      prof: Jun,
      term: Winter 2023,
      grades:
      {
              name: Assignment 1:
              {
                      mark: 10/10,
                      type: Assignment,
                      weight: 0.1,
                      letter grade:
              }

              name: Test 1:
              {
                      mark: 10/14,
                      type: Test,
                      weight: 0.4,
                      letter grade:
              }

      }
}

courseName: Intro:
{
      numGrades: 2,
      prof: Jun,
      term: Winter 2023,
      grades:
      {
              name: Assignment 1:
              {
                      mark: 10/10,
                      type: Assignment,
                      weight: 0.5,
                      letter grade:
              }

              name: Test 1:
              {
                      mark: 15/24,
                      type: Test,
                      weight: 0.3,
                      letter grade:
              }

      }
}


  */

  ifstream file;
  file.open("courses.txt");
  cout << "Loading courses.txt as follows..." << endl;
  if (file.is_open()) {
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
    int coursesAdded = 0;

    getline(file, line);
    numCourses = stoi(line.substr(line.find(":") + 1, line.find(",")));

    while (getline(file, line)) {
      if (line.find("courseName") != string::npos) {
        courseName = line.substr(line.find(":") + 1, line.find("\n"));
        courseName.pop_back();
        cout << "Course Name: " << courseName << endl;
        getline(file, line);
        getline(file, line);
        numGrades = stoi(line.substr(line.find(":") + 1, line.find(",")));
        cout << "Number of Grades: " << numGrades << endl;
        getline(file, line);
        prof = line.substr(line.find(":") + 1);
        prof.pop_back();
        cout << "Professor: " << prof << endl;
        getline(file, line);
        term = line.substr(line.find(":") + 1);
        term.pop_back();
        cout << "Term: " << term << endl;
        cout << "\n" << endl;
        getline(file, line);
        for (int i = 0; i < numGrades; i++)
        {
          getline(file, line);
          // skip empty lines and brackets
          while (line.empty() || line.find("{") != string::npos || line.find("}") != string::npos)
          {
            getline(file, line);
          }

          name = line.substr(line.find(":") + 1, line.find("\n"));
          name.pop_back();
          cout << "Grade Name: " << name << endl;
          getline(file, line);
          getline(file, line);
          mark = line.substr(line.find(":") + 1, line.find("\n"));
          mark.pop_back();
          cout << "Mark: " << mark << endl;
          getline(file, line);
          type = line.substr(line.find(":") + 1, line.find("\n"));
          type.pop_back();
          cout << "Type: " << type << endl;
          getline(file, line);
          string g = line.substr(line.find(":") + 1, line.find("\n"));
          cout << "Weight: " << g << endl;

          getline(file, line);
          letterGrade = line.substr(line.find(":") + 1, line.find("\n"));
          letterGrade.pop_back();
          cout << "Letter Grade: " << letterGrade << endl;

          cout << "\n" << endl;
        }

        
        Course *course = new Course(courseName, prof, term);
        Grade *grade = new Grade(mark, name, type, weight);
        course->addGrade(grade);
        addCourse(course);
        delete grade;
        delete course;
        coursesAdded++;
        cout << "\n" << endl;
      }
    }
    file.close();
  }
  return false;
}
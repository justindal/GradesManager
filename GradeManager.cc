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
    cout << "\n" << endl;
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
  int coursesAdded = 0;
  file.open("courses.txt");
  cout << "Loading courses.txt as follows..." << endl;
  if (file.is_open()) {
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
        Course *course = new Course(courseName, prof, term);
        for (int i = 0; i < numGrades; i++) {
          getline(file, line);
          // skip empty lines and brackets
          while (line.empty() || line.find("{") != string::npos ||
                 line.find("}") != string::npos) {
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
          string tmp = line.substr(line.find(": ") + 2, line.find("\n"));
          tmp.pop_back();
          weight = stod(tmp);
          cout << "Weight: " << weight << endl;

          getline(file, line);
          letterGrade = line.substr(line.find(":") + 1, line.find("\n"));
          cout << "Letter Grade: " << letterGrade << endl;

          cout << "\n" << endl;

          Grade *grade = new Grade(name, mark, type, weight, letterGrade);
          course->addGrade(grade);
        }
        if (course != nullptr) {
          courses.push_back(course);
          coursesAdded++;
        }
      }
    }
    file.close();
  }
  return false;
}
#include "GradeManager.h"

void showOptions();

int main()
{
    GradeManager *gradeManager = new GradeManager();
    gradeManager->loadCourses();
    gradeManager->printCourses();
    cout << endl;

    int choice = -1;

    while (choice != 0)
    {
        showOptions();
        cin >> choice;
        cin.ignore();
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            string courseName;
            string prof;
            string term;

            cout << "Enter course name: ";
            getline(cin, courseName);
            cout << "Enter professor name: ";
            getline(cin, prof);
            cout << "Enter term: ";
            getline(cin, term);

            Course *course = new Course(courseName, prof, term);
            gradeManager->addCourse(course);
            cout << "Course added successfully!" << endl;
        }
        break;
        case 2:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            gradeManager->removeCourse(courseIndex);
            cout << "Course removed successfully!" << endl;
        }
        break;
        case 3:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course information would you like printed? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            course->printCourse();
        }
        break;
        case 4:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course grades would you like printed? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            course->printGrades();
        }

        break;
        case 5:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course grade would you like printed? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            course->printGrades();
            int gradeIndex;
            cout << "\nwhich grade would you like printed? Enter grade index: ";
            cin >> gradeIndex;
            cin.ignore();
            Grade *grade = course->getGradeAt(gradeIndex);
            grade->printGrade();
        }
            break;
        case 6:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course would you like to add a grade to? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            string mark, name, type;
            float weight;
            cout << "Enter grade name: ";
            getline(cin, name);
            cout << "Enter grade mark: ";
            getline(cin, mark);
            cout << "Enter grade type: ";
            getline(cin, type);
            cout << "Enter grade weight: ";
            cin >> weight;
            cin.ignore();
            Grade *grade = new Grade(mark, name, type, weight);
            course->addGrade(grade);
            cout << "Grade added!" << endl;
        }
            break;
        case 7:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course would you like to remove a grade from? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            course->printGrades();
            int gradeIndex;
            cout << "\nwhich grade would you like to remove? Enter grade index: ";
            cin >> gradeIndex;
            cin.ignore();
            course->removeGrade(gradeIndex);
            cout << "Grade removed!" << endl;
        }
            break;
        case 8:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course would you like to edit a grade from? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            course->printGrades();
            int gradeIndex;
            cout << "\nwhich grade would you like to edit? Enter grade index: ";
            cin >> gradeIndex;
            cin.ignore();
            Grade *grade = course->getGradeAt(gradeIndex);
            string mark, name, type;
            float weight;
            cout << "Enter grade name: ";
            getline(cin, name);
            cout << "Enter grade mark: ";
            getline(cin, mark);
            cout << "Enter grade type: ";
            getline(cin, type);
            cout << "Enter grade weight: ";
            cin >> weight;
            cin.ignore();
            grade->setName(name);
            grade->setMark(mark);
            grade->setType(type);
            grade->setWeight(weight);
            cout << "Grade edited!" << endl;
        }
            break;
        case 9:
        {
            gradeManager->printCourses();
            int courseIndex;
            cout << "\nwhich course would you like to edit? Enter course index: ";
            cin >> courseIndex;
            cin.ignore();
            Course *course = gradeManager->getCourseAt(courseIndex);
            string courseName;
            string prof;
            string term;
            cout << "Enter course name: ";
            getline(cin, courseName);
            cout << "Enter professor name: ";
            getline(cin, prof);
            cout << "Enter term: ";
            getline(cin, term);
            course->setCourseName(courseName);
            course->setProf(prof);
            course->setTerm(term);
            cout << "Course edited!" << endl;
        }
            break;
        case 10:
            gradeManager->printCourses();
            break;
        case 11:
            cout << "Courses cleared!" << endl;
            break;
        default:
            gradeManager->saveCourses();
            cout << "Exiting..." << endl;
            break;
        }
    }

    delete gradeManager;
    return 0;
}

void showOptions()
{
    cout << endl;
        cout << "MENU" << endl;
        cout << "1.  Add Course" << endl;
        cout << "2.  Remove Course" << endl;
        cout << "3.  Print Course" << endl;
        cout << "4.  Print Grades" << endl;
        cout << "5.  Print Grade" << endl;
        cout << "6.  Add Grade" << endl;
        cout << "7.  Remove Grade" << endl;
        cout << "8.  Edit Grade" << endl;
        cout << "9.  Edit Course" << endl;
        cout << "10. Print All Course Info" << endl;
        cout << "11. Clear Saved Courses" << endl;
        cout << "0. Exit" << endl;
        cout << "\nEnter your choice: ";
}
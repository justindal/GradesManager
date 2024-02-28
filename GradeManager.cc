
#include "GradeManager.h"

GradeManager::GradeManager() {
    db = nullptr;
}

GradeManager::~GradeManager() {
    closeDatabase();
}

bool GradeManager::openDatabase() {
    int rc = sqlite3_open("database.sqlite", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    } else {
        char *errMsg = nullptr;
        std::string sql;

        // Create Course table
        sql = "CREATE TABLE IF NOT EXISTS Course("  \
              "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
              "COURSENAME      TEXT    NOT NULL," \
              "NUMGRADES       INT     NOT NULL," \
              "PROF            TEXT    NOT NULL," \
              "TERM            TEXT    NOT NULL," \
              "MARK            REAL    NOT NULL);";

        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        // Create Grade table
        sql = "CREATE TABLE IF NOT EXISTS Grade("  \
              "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
              "COURSE_ID       INT     NOT NULL," \
              "MARK            TEXT    NOT NULL," \
              "NAME            TEXT    NOT NULL," \
              "TYPE            TEXT    NOT NULL," \
              "WEIGHT          REAL    NOT NULL," \
              "LETTERGRADE     TEXT    NOT NULL," \
              "PERCENTAGEMARK  REAL    NOT NULL," \
              "FOREIGN KEY(COURSE_ID) REFERENCES Course(ID));";

        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        std::cout << "Opened database successfully" << std::endl;
        return true;
    }
}

void GradeManager::closeDatabase() const
{
    if (db) {
        sqlite3_close(db);
    }
}

bool GradeManager::executeSQL(const std::string& sql) const {
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

std::vector<Course*> GradeManager::getCourses() const {
    return courses;
}

void GradeManager::setCourses(const std::vector<Course*>& courses) {
    GradeManager::courses = courses;
}

void GradeManager::addCourse(Course* course) {
    courses.push_back(course);
    std::string sql = "INSERT INTO Course (COURSENAME, NUMGRADES, PROF, TERM, MARK) VALUES ('" +
                     course->getCourseName() + "', " +
                     std::to_string(course->getNumGrades()) + ", '" +
                     course->getProf() + "', '" +
                     course->getTerm() + "', " +
                     std::to_string(course->getMark()) + ");";
    executeSQL(sql);
}
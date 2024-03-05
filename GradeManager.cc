
#include "GradeManager.h"

GradeManager::GradeManager() {
    static int count = 0;
    db = QSqlDatabase::addDatabase("QSQLITE", QString("Connection%1").arg(count++));
    openDatabase();
    initializeDatabase();
}

GradeManager::~GradeManager() {
    for (auto const course : courses) {
        delete course;
    }
    closeDatabase();
}

bool GradeManager::openDatabase() {
    db.setDatabaseName("database.db");
    if (!db.open()) {
        std::cerr << "Error opening database: " << db.lastError().text().toStdString() << std::endl;
        return false;
    }
    cout << "Database opened successfully" << endl;
    return true;
}

bool GradeManager::initializeDatabase() const {
    const QString createCourseTable = "CREATE TABLE IF NOT EXISTS Course (ID INTEGER PRIMARY KEY AUTOINCREMENT, COURSENAME TEXT, NUMGRADES INTEGER, PROF TEXT, TERM TEXT, MARK REAL);";
    const QString createGradeTable = "CREATE TABLE IF NOT EXISTS Grade (ID INTEGER PRIMARY KEY AUTOINCREMENT, COURSEID INTEGER, NAME TEXT, WEIGHT REAL, MARK REAL);";
    QSqlQuery query(db);

    if (!query.exec(createCourseTable)) {
        std::cerr << "Error creating Course table: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }

    if (!query.exec(createGradeTable)) {
        std::cerr << "Error creating Grade table: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }

    cout << "Database initialized successfully" << endl;

    return true;
}

void GradeManager::closeDatabase()
{
    db.close();
    cout << "Database closed successfully" << endl;
}

bool GradeManager::executeSQL(const std::string& sql) const {
    QSqlQuery query(db);
    if (!query.exec(QString::fromStdString(sql))) {
        std::cerr << "SQL error: " << query.lastError().text().toStdString() << std::endl;
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
    const std::string sql = "INSERT INTO Course (COURSENAME, NUMGRADES, PROF, TERM, MARK) VALUES ('" +
                     course->getCourseName() + "', " +
                     std::to_string(course->getNumGrades()) + ", '" +
                     course->getProf() + "', '" +
                     course->getTerm() + "', " +
                     std::to_string(course->getMark()) + ");";
    executeSQL(sql);
}
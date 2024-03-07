
#include "GradeManager.h"

GradeManager::GradeManager() {
    static int count = 0;
    db = QSqlDatabase::addDatabase("QSQLITE", QString("Connection%1").arg(count++));
    openDatabase();
    initializeDatabase();
    readCoursesFromDatabase();
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
    const QString createCourseTable = "CREATE TABLE IF NOT EXISTS Course ("
                                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "COURSENAME TEXT, "
                                  "COURSECODE TEXT, "
                                  "NUMGRADES INTEGER, "
                                  "PROF TEXT, "
                                  "TERM TEXT, "
                                  "CREDITWORTH REAL, "
                                  "MARK REAL);";

    const QString createGradeTable = "CREATE TABLE IF NOT EXISTS Grade ("
                                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                      "COURSEID INTEGER, "
                                      "NAME TEXT, "
                                      "WEIGHT REAL, "
                                      "MARK REAL, "
                                      "FOREIGN KEY(COURSEID) REFERENCES Course(ID));";
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
    QSqlDatabase::removeDatabase(db.connectionName());
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
    const std::string sql = "INSERT INTO Course (COURSENAME, COURSECODE, NUMGRADES, PROF, TERM, CREDITWORTH, MARK) VALUES ('"
                            + course->getCourseName() + "', '"
                            + course->getCourseCode() + "', "
                            + std::to_string(course->getNumGrades()) + ", '"
                            + course->getProf() + "', '"
                            + course->getTerm() + "', "
                            + std::to_string(course->getCreditWorth()) + ", "
                            + std::to_string(course->getMark()) + ");";
    if (!executeSQL(sql)) {
        std::cerr << "Error adding course to database" << std::endl;
    }
}

void GradeManager::readCoursesFromDatabase() {
    const std::string sql = "SELECT * FROM Course;";
    QSqlQuery query(db);
    if (!query.exec(QString::fromStdString(sql))) {
        std::cerr << "Error reading courses from database: " << query.lastError().text().toStdString() << std::endl;
        return;
    }
    while (query.next()) {

        const std::string courseName = query.value(1).toString().toStdString();
        const std::string courseCode = query.value(2).toString().toStdString();
        const int numGrades = query.value(3).toInt();
        const std::string prof = query.value(4).toString().toStdString();
        const std::string term = query.value(5).toString().toStdString();
        const std::string creditWorth = query.value(6).toString().toStdString();
        const float mark = query.value(7).toFloat();
        auto *course = new Course(courseName, courseCode, prof, term, numGrades, mark, std::stof(creditWorth));

        courses.push_back(course);
    }
}

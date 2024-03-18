
#include "GradeManager.h"

GradeManager::GradeManager() {
    static int count = 0;
    db = QSqlDatabase::addDatabase("QSQLITE", QString("Connection%1").arg(count++));
    openDatabase();
    initializeDatabase();
    readCoursesFromDatabase();
}

GradeManager::~GradeManager() {
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
                                      "TYPE TEXT, "
                                      "WEIGHT REAL, "
                                      "MARK TEXT, "
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

    // Read grades from database
    for (auto& course : courses) {
        const std::string sql = "SELECT * FROM Grade WHERE COURSEID = " + std::to_string(getCourseId(course->getCourseName())) + ";";
        QSqlQuery query(db);
        if (!query.exec(QString::fromStdString(sql))) {
            std::cerr << "Error reading grades from database: " << query.lastError().text().toStdString() << std::endl;
            return;
        }
        while (query.next()) {
            const string gradeName = query.value(2).toString().toStdString();
            const string gradeType = query.value(3).toString().toStdString();
            const float gradeWeight = query.value(4).toFloat();
            const string gradeMark = query.value(5).toString().toStdString();
            auto *grade = new Grade(gradeMark, gradeName, gradeType, gradeWeight);
            course->addGrade(grade);
        }
    }
}

Course* GradeManager::removeCourse(const std::string& courseName) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if ((*it)->getCourseName() == courseName) {
            Course* course = *it;
            courses.erase(it);
            const std::string sql = "DELETE FROM Course WHERE COURSENAME = '" + courseName + "';";
            if (!executeSQL(sql)) {
                std::cerr << "Error removing course from database" << std::endl;
            }
            return course;
        }
    }
    return nullptr;
}

void GradeManager::updateCourseInDatabase(const string& originalCourseName, Course* course) const {
    // First, get the courseID for the given originalCourseName
    const string selectSql = "SELECT ID FROM Course WHERE COURSENAME = '" + originalCourseName + "';";
    QSqlQuery query(db);
    if (!query.exec(QString::fromStdString(selectSql))) {
        std::cerr << "SQL error: " << query.lastError().text().toStdString() << std::endl;
        return;
    }
    if (query.next()) {
        const int courseId = query.value(0).toInt();

        // Then, update the course details using the courseID
        std::string updateSql = "UPDATE Course SET "
                                "COURSENAME = '" + course->getCourseName() + "', "
                                "COURSECODE = '" + course->getCourseCode() + "', "
                                "PROF = '" + course->getProf() + "', "
                                "TERM = '" + course->getTerm() + "', "
                                "CREDITWORTH = " + std::to_string(course->getCreditWorth()) + ", "
                                "MARK = " + std::to_string(course->getMark()) +
                                " WHERE ID = " + std::to_string(courseId) + ";";
        if (!executeSQL(updateSql)) {
            std::cerr << "Error updating course in database" << std::endl;
        }
    } else {
        std::cerr << "Course not found in database" << std::endl;
    }
}

void GradeManager::addGradeToDatabase(Course* course, Grade* grade) {
    const std::string sql = "INSERT INTO Grade (COURSEID, NAME, MARK, TYPE, WEIGHT) VALUES ("
                            + std::to_string(getCourseId(course->getCourseName())) + ", '"
                            + grade->getName() + "', '"
                            + grade->getMark() + "', '"
                            + grade->getType() + "', "
                            + std::to_string(grade->getWeight()) + ");";
    if (!executeSQL(sql)) {
        std::cerr << "Error adding grade to database" << std::endl;
    }
}

int GradeManager::getCourseId(const string& courseName) const {
    const std::string sql = "SELECT ID FROM Course WHERE COURSENAME = '" + courseName + "';";
    QSqlQuery query(db);
    if (query.exec(QString::fromStdString(sql)) && query.next()) {
        return query.value(0).toInt();
    } else {
        std::cerr << "Error getting course ID from database" << std::endl;
        return -1;
    }
}
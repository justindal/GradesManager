cmake_minimum_required(VERSION 3.28)
project(GradesManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(GradesManager main.cpp
        Course.cc
        Course.h
        Grade.cc
        Grade.h
        GradeManager.cc
        GradeManager.h
        GradeManagerGUI.cc
        GradeManagerGUI.h
        GradeManagerGUI.ui
        AddCourseDialog.cc
        AddCourseDialog.h)
target_link_libraries(GradesManager
        Qt::Core
        Qt::Gui
        Qt::Widgets
        sqlite3
)


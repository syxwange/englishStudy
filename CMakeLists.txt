cmake_minimum_required(VERSION 3.5)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Qt/6.2.1/mingw81_64")
find_package(Qt6  COMPONENTS Widgets  Qml  Sql REQUIRED)

FILE(GLOB SRC_FILES "*.cpp" ) 
FILE(GLOB INCLUDE_FILES "*.h") 
FILE(GLOB UI_FILES "widget/*.ui" "widget/*.cpp" "widget/*.h") 
FILE(GLOB DB_FILES "database/*.cpp" "database/*.h") 

message(("${UI_FILES}"))

set(PROJECT_SOURCES   ${SRC_FILES}   ${INCLUDE_FILES} ${UI_FILES} ${DB_FILES})

#include_directories("C:/Users/syxwa/miniconda3/include")
qt_add_executable(untitled     MANUAL_FINALIZATION    ${PROJECT_SOURCES}  )
target_link_libraries(untitled PRIVATE Qt6::Widgets  Qt6::Qml Qt6::Sql)

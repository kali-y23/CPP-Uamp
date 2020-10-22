cmake_minimum_required(VERSION 3.16.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(TARGET uamp)

find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

set(SOURCES main.cpp src/mainwindow.cpp src/qplayer.cpp src/qsuperbutton.cpp
            src/mediator.cpp src/myDb.cpp)
set(UI Forms/mainwindow.ui)

qt5_add_resources(SOURCES resources/resources.qrc)

add_executable(${TARGET} ${SOURCES} ${HEADERS})

add_subdirectory(src)
include_directories(./src)

target_link_libraries(${TARGET} Qt5::Core Qt5::Widgets Qt5::Sql)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)

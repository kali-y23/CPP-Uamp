cmake_minimum_required(VERSION 3.16.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(TARGET uamp)

find_library(TAGLIB taglib)

include_directories(../3dparty/taglib/taglib/)
include_directories(../3dparty/taglib/taglib/mpeg/)
include_directories(../3dparty/taglib/taglib/mpeg/id3v2/)
include_directories(../3dparty/taglib/taglib/frames/)
include_directories(../3dparty/taglib/taglib/toolkit)
include_directories(../build/3dparty/taglib/)
include_directories(../cmake-build-debug/3dparty/taglib/)

find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

set(SOURCES main.cpp src/mainwindow.cpp src/qplayer.cpp src/qsuperbutton.cpp
            src/mediator.cpp src/myDb.cpp src/component.cpp src/login.cpp
            src/registration.cpp src/general.cpp src/qsidebar.cpp src/user.cpp
            src/mymodel.cpp src/tags.cpp src/mytable.cpp src/mytreeview.cpp
            src/libraryManager.cpp src/queue.cpp src/queuewidget.cpp src/userManager.cpp
            src/playlist.cpp src/myitem.cpp src/mylist.cpp src/listmodel.cpp
            src/albumcover.cpp)

qt5_add_resources(SOURCES resources/resources.qrc)

add_executable(${TARGET} ${SOURCES})

add_subdirectory(src)
include_directories(./src)
include_directories(${CMAKE_SOURCE_DIR}/3dparty/BASS)

target_link_libraries(${TARGET} tag Qt5::Core Qt5::Widgets Qt5::Sql ${CMAKE_SOURCE_DIR}/3dparty/BASS/libbass.dylib)
# target_compile_definitions (${TARGET} PRIVATE -D_UNICODE -DUNICODE)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)

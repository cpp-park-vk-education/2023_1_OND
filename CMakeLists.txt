cmake_minimum_required(VERSION 3.1.0)

project(client VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Multimedia)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5PrintSupport_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
    ${Qt5Multimedia_INCLUDE_DIRS}  
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(client_start 
    main.cpp
    UI/img/img.qrc
)



add_subdirectory( ${PROJECT_SOURCE_DIR}/Logic )
add_subdirectory( ${PROJECT_SOURCE_DIR}/UI )
include_directories( ${PROJECT_SOURCE_DIR}/Logic/include )
include_directories(${PROJECT_SOURCE_DIR}/UI)


target_link_libraries(client_start Qt5::Widgets client_logic client_ui)
#target_include_directories(client_start PRIVATE img/)


qt5_use_modules(client_start Widgets Multimedia)
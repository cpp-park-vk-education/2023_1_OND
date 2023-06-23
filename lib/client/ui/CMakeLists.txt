cmake_minimum_required(VERSION 3.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5PrintSupport_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
    ${Qt5Multimedia_INCLUDE_DIRS} 
)

include_directories(.)
include_directories( ../Logic/include)


add_library(client_ui
    guestmainwindow.cpp
    guestmainwindow.ui
    guestmainwindow.h
    authwindow.cpp
    authwindow.ui
    authwindow.h
    regwindow.cpp
    regwindow.ui
    regwindow.h
    devwindow.cpp
    devwindow.ui
    devwindow.h
    #img/img.qrc
    )


target_link_libraries(client_ui Qt5::Widgets client_logic)

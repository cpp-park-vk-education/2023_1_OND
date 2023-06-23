cmake_minimum_required(VERSION 3.1.0)

#project(logic VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)
#qt5_use_modules(${PROJECT_NAME} Widgets Multimedia)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5PrintSupport_INCLUDE_DIRS}
    ${Qt5Sql_INCLUDE_DIRS}
    ${Qt5Multimedia_INCLUDE_DIRS}  #the directories 
)

include_directories( include )
#include_directories( ../UI)

add_library(client_logic
    
    src/audio.cpp
    src/clienttcp.cpp
    src/controller.cpp
    src/iclienttcp.cpp
    src/playerrunner.cpp
    src/questionmodel.cpp
    src/recorderrunner.cpp)


#qt5_use_modules(${PROJECT_NAME} Widgets Multimedia)


target_link_libraries(client_logic Qt5::Widgets)






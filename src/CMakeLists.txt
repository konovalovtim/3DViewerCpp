cmake_minimum_required(VERSION 3.5)

project(3DViewer_v1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

set(PROJECT_SOURCES
        mainwindow.h
        main.cpp
        mainwindow.cpp
        mainwindow.ui
        glview.cpp
        glview.h
        options.cpp
        options.h
        options.ui
        backend/moving/centralize_object_t.c
        backend/moving/moving_object_t.c
        backend/moving/normalization_object_t.c
        backend/moving/rotation_object_t.c
        backend/moving/zoom_object_t.c
        backend/parsing/init_object_t.c
        backend/parsing/parsing_edges.c
        backend/parsing/parsing_object_t.c
        backend/parsing/parsing_vertexes.c
        backend/parsing/remove_object_t.c
        backend/3d_viewer.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GLWidget
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})
else()
    if(ANDROID)
        add_library(GLWidget SHARED
            ${PROJECT_SOURCES})
    else()
        add_executable(GLWidget
            ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(GLWidget PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GLWidget PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(GLWidget PRIVATE Qt6::Gui)

set_target_properties(GLWidget PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE)

install(TARGETS GLWidget
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GLWidget)
endif()



# backend/moving/centralize_object_t.c
#         backend/moving/moving_object_t.c
#         backend/moving/normalization_object_t.c
#         backend/moving/rotation_object_t.c
#         backend/moving/zoom_object_t.c
#         backend/parsing/init_object_t.c
#         backend/parsing/parsing_edges.c
#         backend/parsing/parsing_object_t.c
#         backend/parsing/parsing_vertexes_t.c
#         backend/parsing/remove_object_t.c
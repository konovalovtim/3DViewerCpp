cmake_minimum_required(VERSION 3.5)

project(3DViewer_v1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 Qt4 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

set(PROJECT_SOURCES
        backend/moving/moving_object_t.c
        backend/moving/rotation_object_t.c
        backend/moving/zoom_object_t.c
        backend/moving/centralize_object_t.c
        backend/moving/normalization_object_t.c
        backend/parsing/init_object_t.c
        backend/parsing/parsing_edges.c
        backend/parsing/parsing_object_t.c
        backend/parsing/parsing_vertexes.c
        backend/parsing/remove_object_t.c
        options.cpp
        backend/3d_viewer.h
        backend/3d_viewer.h
        glview.cpp
        glview.h
        options.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        options.ui
        )

        if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(3DViewer_v1
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET 3DViewer_v1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    else()
        if(ANDROID)
            add_library(3DViewer_v1 SHARED
                ${PROJECT_SOURCES}
            )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(3DViewer_v1
                ${PROJECT_SOURCES}
            )
        endif()
    endif()
    
    target_link_libraries(3DViewer_v1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    
    set_target_properties(3DViewer_v1 PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(3DViewer_v1)
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
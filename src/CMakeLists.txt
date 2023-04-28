cmake_minimum_required(VERSION 3.22)

project(3DViewer VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)

add_subdirectory(GIFCreation)

add_executable(3DViewer
        main.cc

        model/affine_object.cc
        model/container_object.cc
        model/parsing_object.cc
        model/normalization.cc
        model/singleton.cc
        model/model.h
        model/part_object.h

        controller/controller.cc
        controller/controller.h
        controller/options_t.cc
        controller/options_t.h

        view/OpenGLWidget/gl_override.cc
        view/OpenGLWidget/gl_override.h
        view/options.cc
        view/options.h
        view/options.ui
        view/view.ui

        icon/icons.qrc)

target_link_libraries(3DViewer PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets GIFLIB)

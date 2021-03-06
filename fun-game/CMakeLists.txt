cmake_minimum_required(VERSION 3.5)

project(fun-game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        view.h
        view.cpp

        gui/text.h
        gui/text.cpp
        gui/button.h
        gui/button.cpp
        gui/shell.h
        gui/shell.cpp
        gui/msg_queue.h
        gui/msg_queue.cpp
        gui/power_bar.h
        gui/power_bar.cpp

        chat/chat.h
        chat/chat.cpp

        net/udp_client.h
        net/udp_client.cpp
        net/protocol.h

        game/game.cpp
        game/game.h
        game/unit.cpp
        game/unit.h
        game/angle_indicator.cpp
        game/angle_indicator.h
        game/fly_object.cpp
        game/fly_object.h
        game/bg_objects.cpp
        game/bg_objects.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(fun-game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET fun-game APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(fun-game SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(fun-game
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(fun-game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(fun-game PRIVATE Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(fun-game PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fun-game)
endif()

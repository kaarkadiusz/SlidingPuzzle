cmake_minimum_required(VERSION 3.5)

project(SlidingPuzzle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SlidingPuzzle
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Classes/Game/game.h Classes/Game/game.cpp
        Classes/Board/board.h Classes/Board/board.cpp
        Classes/Block/block.h Classes/Block/block.cpp
        Classes/PromptDialog/promptdialog.h Classes/PromptDialog/promptdialog.cpp Classes/PromptDialog/promptdialog.ui

        Classes/QBlock/qblock.h Classes/QBlock/qblock.cpp
        Classes/QBoard/qboard.h Classes/QBoard/qboard.cpp
        Classes/QGame/qgame.h Classes/QGame/qgame.cpp
        Classes/BoardGenerator/boardgenerator.h Classes/BoardGenerator/boardgenerator.cpp

        enums.h
        Classes/AStar/astar.h Classes/AStar/astar.cpp
        Classes/Helpers/helpers.h Classes/Helpers/helpers.cpp
        Classes/Player/player.h Classes/Player/player.cpp
        Classes/BFS/bfs.h Classes/BFS/bfs.cpp
        Bases/algorithmsolvebase.h Bases/algorithmsolvebase.cpp
        Classes/AlgorithmChoiceDialog/algorithmchoicedialog.h Classes/AlgorithmChoiceDialog/algorithmchoicedialog.cpp Classes/AlgorithmChoiceDialog/algorithmchoicedialog.ui









    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SlidingPuzzle APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SlidingPuzzle SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SlidingPuzzle
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SlidingPuzzle PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SlidingPuzzle)
endif()
set_target_properties(SlidingPuzzle PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SlidingPuzzle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SlidingPuzzle)
endif()

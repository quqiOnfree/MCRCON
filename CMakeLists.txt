cmake_minimum_required(VERSION 3.5)

project(MCRCON VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "E:/Qt/6.3.1/msvc2019_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network LinguistTools)

set(TS_FILES MCRCON_zh_CN.ts)

file(GLOB PROJECT_SOURCES
        "${PROJECT_SOURCE_DIR}/AddServerDialog/*.h"
        "${PROJECT_SOURCE_DIR}/AddServerDialog/*.cpp"
        "${PROJECT_SOURCE_DIR}/AddServerDialog/*.ui"

        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.cpp"
        "${PROJECT_SOURCE_DIR}/include/*.ui"

        "${PROJECT_SOURCE_DIR}/MainWindow/*.h"
        "${PROJECT_SOURCE_DIR}/MainWindow/*.cpp"
        "${PROJECT_SOURCE_DIR}/MainWindow/*.ui"

        "${PROJECT_SOURCE_DIR}/ServerManagerDialog/*.h"
        "${PROJECT_SOURCE_DIR}/ServerManagerDialog/*.cpp"
        "${PROJECT_SOURCE_DIR}/ServerManagerDialog/*.ui"

        "${PROJECT_SOURCE_DIR}/LocalServerManager/*.h"
        "${PROJECT_SOURCE_DIR}/LocalServerManager/*.cpp"
        "${PROJECT_SOURCE_DIR}/LocalServerManager/*.ui"

        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.ui"

        ${TS_FILES}
)

if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2 /Ot /GL /Gy")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif(MSVC)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MCRCON
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MCRCON APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(MCRCON SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MCRCON
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(MCRCON PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

set_target_properties(MCRCON PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MCRCON)
endif()

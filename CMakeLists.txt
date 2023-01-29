cmake_minimum_required(VERSION 3.8)

project(MCRCON VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Qt6库路径
set(CMAKE_PREFIX_PATH "E:/Qt/6.3.1/msvc2019_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network LinguistTools)

set(TS_FILES MCRCON_zh_CN.ts)

#Python库路径（一定是"/"或者可以是"\\"而不是"\"）
set(PYTHON_PATH "C:/Program Files (x86)/Microsoft Visual Studio/Shared/Python39_64")
set(PYTHON_NAME "python39")
set(PYTHON_LIBRARY "${PYTHON_PATH}/include")
set(PYTHON_LIBS "${PYTHON_PATH}/libs")
include_directories(${PYTHON_LIBRARY})

file(GLOB PROJECT_SOURCES
        "${PROJECT_SOURCE_DIR}/AddServerDialog/*.h"
        "${PROJECT_SOURCE_DIR}/AddServerDialog/*.cpp"
        "${PROJECT_SOURCE_DIR}/AddServerDialog/*.ui"

        "${PROJECT_SOURCE_DIR}/Definition/*.h"
        "${PROJECT_SOURCE_DIR}/Definition/*.cpp"
        "${PROJECT_SOURCE_DIR}/Definition/*.ui"

        "${PROJECT_SOURCE_DIR}/Logger/*.h"
        "${PROJECT_SOURCE_DIR}/Logger/*.cpp"

        "${PROJECT_SOURCE_DIR}/MainWindow/*.h"
        "${PROJECT_SOURCE_DIR}/MainWindow/*.cpp"
        "${PROJECT_SOURCE_DIR}/MainWindow/*.ui"

        "${PROJECT_SOURCE_DIR}/ServerManagerDialog/*.h"
        "${PROJECT_SOURCE_DIR}/ServerManagerDialog/*.cpp"
        "${PROJECT_SOURCE_DIR}/ServerManagerDialog/*.ui"

        "${PROJECT_SOURCE_DIR}/LocalServerManager/*.h"
        "${PROJECT_SOURCE_DIR}/LocalServerManager/*.cpp"
        "${PROJECT_SOURCE_DIR}/LocalServerManager/*.ui"

        "${PROJECT_SOURCE_DIR}/Json/*.h"
        "${PROJECT_SOURCE_DIR}/Json/*.cpp"

        "${PROJECT_SOURCE_DIR}/PythonModule/*.h"
        "${PROJECT_SOURCE_DIR}/PythonModule/*.cpp"

        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.ui"

        #Python库
        "${PYTHON_LIBRARY}/*.h"
        "${PYTHON_LIBRARY}/*.c"

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

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
target_link_libraries(MCRCON PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network

    #Python Libs
    ${PYTHON_LIBS}/${PYTHON_NAME}_d.lib
)
else()
target_link_libraries(MCRCON PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network

    #Python Libs
    ${PYTHON_LIBS}/${PYTHON_NAME}.lib
)
endif()

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

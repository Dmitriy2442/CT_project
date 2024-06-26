cmake_minimum_required(VERSION 3.5)

project(CT_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Подключение SQL
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS MultimediaWidgets)

# Добавление всех заголовочных файлов из директории headers
file(GLOB HEADER_FILES "headers/*.h")

# Добавление всех исходных файлов из директории sources
file(GLOB SOURCE_FILES "sources/*.cpp")

# Добавление всех .ui файлов из директории ui
file(GLOB UI_FILES "ui/*.ui")

# Добавление всех компонент из директории components
file(GLOB COMPONENTS_FILES "components/*.h" "components/*.cpp")

# Добавление всех компонент из директории game
file(GLOB GAME_FILES "game/*.h" "game/*.cpp")

set(PROJECT_SOURCES
        main.cpp

        ${HEADER_FILES}
        ${SOURCE_FILES}
        ${UI_FILES}
        ${COMPONENTS_FILES}
        ${GAME_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CT_project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        resourses.qrc
    )

# Перенос актуального файла базы данных в build-папку
set(SOURCE_DB "${CMAKE_SOURCE_DIR}/gamedata.db")
set(DEST_DB "${CMAKE_BINARY_DIR}/gamedata.db")
add_custom_command(
    OUTPUT ${DEST_DB}
    COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_DB} ${DEST_DB}
    DEPENDS ${SOURCE_DB}
    COMMENT "Copying gamedata.db to build directory"
)
add_custom_target(CopyDB ALL
    DEPENDS ${DEST_DB}
)


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CT_project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CT_project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CT_project
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CT_project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CT_project PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(CT_project PRIVATE Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

include_directories(./)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CT_project)
endif()
set_target_properties(CT_project PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CT_project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CT_project)
endif()

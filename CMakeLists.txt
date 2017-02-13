# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.0)

# Add folder where are supportive functions
set(CMAKE_AUTOMOC ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

# Include qt basic functions
include(QtCommon)

# Include qt current directories in order to use promoted objects
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/app)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/cores)

# Basic info about project
project(SSAT VERSION 1.0)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

file(GLOB APP_GUI_FILES "modules/app/*.ui")
file(GLOB APP_SOURCE_FILES "modules/app/*.cpp")
file(GLOB CORE_SOURCE_FILES "modules/core/*.cpp")
file(GLOB CORE_INCLUDE_FILES "modules/core/*.h")
file(GLOB CMT_SOURCE_FILES "modules/tracker/*.cpp")
file(GLOB CMT_INCLUDE_FILES "modules/tracker/*.h")

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES ssat.qrc)

find_package(OpenCV 3.0.0 REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV COMPONENTS opencv_core opencv_imgproc opencv_highgui REQUIRED)
find_path(OpenCV_INCLUDE_DIR "opencv/cv.h" PATHS "${OpenCV_DIR}" PATH_SUFFIXES "include" DOC "")

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# source_group("UI Files" FILES ${UI_FILES})
add_library(${PROJECT_NAME}_CORE ${CORE_SOURCE_FILES} ${CORE_INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME}_CORE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME}_CORE PUBLIC modules/core/)

add_library(${PROJECT_NAME}_CMT ${CMT_SOURCE_FILES} ${CMT_INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME}_CMT ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME}_CMT PUBLIC modules/tracker/)

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${APP_GUI_FILES} ${APP_SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_CORE)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_CMT)
target_link_libraries(${PROJECT_NAME} pthread)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIR})

qt5_use_modules(${PROJECT_NAME} Widgets)

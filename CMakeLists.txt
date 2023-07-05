cmake_minimum_required(VERSION 3.0.0)
project(BS_Downgrader VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSON_INC_PATH})

add_executable(BS_Downgrader
    Main.ui
    DepotDownloader.ui
    MainUI.cpp
    main.cpp
    util.cpp
    DepotDownloaderWrapper.cpp
)

target_link_libraries(BS_Downgrader Qt5::Widgets ${CURL_LIBRARIES}  ${JSONCPP_LIBRARIES})
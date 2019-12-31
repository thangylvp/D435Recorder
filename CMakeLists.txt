cmake_minimum_required(VERSION 2.6.0)
project(D435_RECORDER)

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

find_package(ZLIB REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package( realsense2 REQUIRED )

INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
include_directories( ${realsense2_INCLUDE_DIR} )
include_directories( ${OpenCV_INCLUDE_DIRS} )

aux_source_directory(. DIR_SRCS)

add_executable(RGBDCapture ${DIR_SRCS})

target_link_libraries(RGBDCapture
                      ${ZLIB_LIBRARY}
                      ${OpenCV_LIBS}
        		      ${Boost_SYSTEM_LIBRARIES}
                      ${Boost_FILESYSTEM_LIBRARIES}
                      ${realsense2_LIBRARY}  
                      )





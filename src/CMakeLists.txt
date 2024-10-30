cmake_minimum_required(VERSION 3.10)

project(HandwritingRecognitionAPI VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(handwriting_recognition_api
    src/main.cpp
    src/api_handler.cpp
    src/handwriting_recognizer.cpp
)

target_link_libraries(handwriting_recognition_api ${OpenCV_LIBS} ${Boost_LIBRARIES})

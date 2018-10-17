cmake_minimum_required(VERSION 3.3.1)

project(Projekt)

find_package(OpenCV	3.2.0	REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
)

add_executable(Projekt
	main.cpp
	FindContours.h
	FindContours.cpp
)

target_link_libraries(Projekt
	${OpenCV_LIBS}
)

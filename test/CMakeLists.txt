cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(PlatformPath_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(PlatformPath_test
		PlatformPath_test.cpp
	)
	
target_link_libraries(PlatformPath_test
	PlatformPath
	)
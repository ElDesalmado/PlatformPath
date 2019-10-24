cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(PlatformPath
	LANGUAGES CXX
	VERSION 1.0.0
	)

set(PlatformPath_VERSION_MAJOR 1)
set(PlatformPath_VERSION_MINOR 0)
set(PlatformPath_VERSION "${PlatformPath_VERSION_MAJOR}.${PlatformPath_VERSION_MINOR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(
	${PROJECT_SOURCE_DIR}/config/IPlatformPath_version.h.in
	${PROJECT_BINARY_DIR}/include/IPlatformPath_version.h
	)

add_library(PlatformPath_OBJ
	OBJECT
		include/IPlatformPath.h
		${PROJECT_BINARY_DIR}/include/IPlatformPath_version.h
		src/PlatformPath.cpp
	)
	
target_include_directories(PlatformPath_OBJ
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_BINARY_DIR}/include
	)
	
option(BUILD_SHARED OFF)
message(STATUS "BUILD_SHARED " ${BUILD_SHARED})

if(NOT BUILD_SHARED)
add_library(PlatformPath
	STATIC
		$<TARGET_OBJECTS:PlatformPath_OBJ>
	)
else()
add_library(PlatformPath
	SHARED
		$<TARGET_OBJECTS:PlatformPath_OBJ>
	)
	
target_compile_definitions(PlatformPath_OBJ
	PUBLIC
		PLATFORM_PATH_SHARED
	PRIVATE
		PLATFORM_PATH_BUILD
	)
endif()

target_include_directories(PlatformPath
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
	)
	
set_target_properties(PlatformPath
	PROPERTIES
		DEBUG_POSTFIX "_d"
	)

add_subdirectory(test)	

# build a CPackdriven installer package
#include(InstallRequiredSystemLibraries)
#set(CPACK_PACKAGE_VERSION_MAJOR ${PlatformPath_VERSION_MAJOR})
#set(CPACK_PACKAGE_VERSION_MINOR ${PlatformPath_VERSION_MINOR})
#include(CPack)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/)

set(SYSCONFIG_INSTALL_DIR etc/PlatformPath/)

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_SOURCE_DIR}/config/PlatformPathConfig.cmake.in
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX} # change?
	PATH_VARS 
		INCLUDE_INSTALL_DIR 
		LIB_INSTALL_DIR
	)
write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PlatformPath_VERSION}.1
	COMPATIBILITY SameMajorVersion
	)

message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")

install(FILES
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION	${CMAKE_INSTALL_PREFIX}
	)

install(TARGETS
		PlatformPath
		PlatformPath_test
	EXPORT 
		PlatformPath
	ARCHIVE
		DESTINATION ${LIB_INSTALL_DIR}
		COMPONENT lib
	LIBRARY
		DESTINATION ${LIB_INSTALL_DIR}
		COMPONENT lib
	RUNTIME
		DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
		COMPONENT bin
	)
install(FILES
		include/IPlatformPath.h
		
		${PROJECT_BINARY_DIR}/config/IPlatformPath_version.h
	DESTINATION 
		${INCLUDE_INSTALL_DIR}
	)
	
	
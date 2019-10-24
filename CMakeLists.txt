cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(PlatformPath
	LANGUAGES CXX
	VERSION 1.0.0
	)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(
	${PROJECT_SOURCE_DIR}/config/IPlatformPath_version.h.in
	${PROJECT_BINARY_DIR}/include/PlatformPath/IPlatformPath_version.h
	)

add_library(PlatformPath
		${PROJECT_SOURCE_DIR}/src/PlatformPath.cpp
	)

option(BUILD_SHARED_LIBS "Build as a shared library?" OFF)
message(STATUS "BUILD_SHARED " ${BUILD_SHARED})

include(GenerateExportHeader)

generate_export_header(PlatformPath
	EXPORT_MACRO_NAME PlPath_API
	EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/PlatformPath/api_def.h
	)

target_include_directories(PlatformPath
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
	)
	
set_target_properties(PlatformPath
	PROPERTIES
		DEBUG_POSTFIX "_d"
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
		LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
		ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
	)

add_subdirectory(test)	

include(GNUInstallDirs)
message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")

install(TARGETS
		PlatformPath
	EXPORT 
		PlatformPathConfig
	ARCHIVE
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
install(DIRECTORY 
		${PROJECT_SOURCE_DIR}/include/PlatformPath
		${PROJECT_BINARY_DIR}/include/PlatformPath
	DESTINATION 
		${CMAKE_INSTALL_INCLUDEDIR}
	)
install(EXPORT PlatformPathConfig
	DESTINATION
		${CMAKE_INSTALL_PREFIX}/cmake
	)


include(CMakePackageConfigHelpers)
#configure_package_config_file(${PROJECT_SOURCE_DIR}/config/PlatformPathConfig.cmake.in
#		"${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
#	INSTALL_DESTINATION 
#		${CMAKE_INSTALL_PREFIX}/cmake # change?
#	)
write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PlatformPath_VERSION}
	COMPATIBILITY SameMajorVersion
	)

install(DIRECTORY
		${PROJECT_BINARY_DIR}/cmake
	DESTINATION	
		${CMAKE_INSTALL_PREFIX}
	)
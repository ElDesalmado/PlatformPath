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

add_library(${PROJECT_NAME}
		src/PlatformPath.cpp
	)

option(BUILD_SHARED_LIBS "Build as a shared library?" OFF)
message(STATUS "BUILD_SHARED " ${BUILD_SHARED})

include(GenerateExportHeader)

generate_export_header(${PROJECT_NAME}
	EXPORT_MACRO_NAME PlPath_API
	EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/PlatformPath/api_def.h
	)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
	INTERFACE
		$<INSTALL_INTERFACE:include>
	)
	
set_target_properties(${PROJECT_NAME}
	PROPERTIES
		DEBUG_POSTFIX "_d"
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
		LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
		ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
	)

add_subdirectory(test)	

# installation

set(config_install_dir ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
set(version_config ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
set(project_config ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake)
set(targets_export_name ${PROJECT_NAME}Targets)


include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
message(STATUS "${PROJECT_NAME} will be installed to ${CMAKE_INSTALL_PREFIX}")

configure_package_config_file(
		${PROJECT_SOURCE_DIR}/config/${PROJECT_NAME}Config.cmake.in
		${project_config}
	INSTALL_DESTINATION 
		${config_install_dir}
	)
	
write_basic_package_version_file(
		${version_config}
	VERSION 
		${PlatformPath_VERSION}
	COMPATIBILITY 
		SameMajorVersion
	)

install(TARGETS
		${PROJECT_NAME}
	EXPORT 
		${targets_export_name}
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
install(EXPORT 
		${targets_export_name}
	DESTINATION
		${config_install_dir}
	)

install(FILES
		${project_config}
		${version_config}
	DESTINATION	
		${config_install_dir}
	)
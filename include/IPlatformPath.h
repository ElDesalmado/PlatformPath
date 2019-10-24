#pragma once

#include "IPlatformPath_version.h"

#ifndef PLATFORM_PATH_SHARED
#define PATH_API
#else
	#ifndef PLATFORM_PATH_BUILD
	#define PATH_API __declspec(dllimport)
	#else
	#define PATH_API __declspec(dllexport)
	#endif // !DLL_BUILD
#endif // !PLATFORM_PATH_SHARED

#include <string>

struct PATH_API IPlatformPath
{
	static std::unique_ptr<IPlatformPath> Create();
	static std::string ModulePathName();
	//static std::string FullPath(const std::string& relative);

	virtual std::string GetModulePathName() const = 0;
	virtual std::string GetModulePath() const = 0;
	virtual std::string GetRelativePath(const std::string& relativePath) const = 0;

	virtual ~IPlatformPath() = default;

};
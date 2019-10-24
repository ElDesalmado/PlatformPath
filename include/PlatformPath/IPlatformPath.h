#pragma once

#include "PlatformPath/IPlatformPath_version.h"
#include "PlatformPath/api_def.h"

#include <string>

struct PlPath_API IPlatformPath
{
	static std::unique_ptr<IPlatformPath> Create();
	static std::string ModulePathName();
	//static std::string FullPath(const std::string& relative);

	virtual std::string GetModulePathName() const = 0;
	virtual std::string GetModulePath() const = 0;
	virtual std::string GetFullPath(const std::string& relativePath) const = 0;

	virtual ~IPlatformPath() = default;

};
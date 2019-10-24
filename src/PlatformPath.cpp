#include "IPlatformPath.h"

#include <Windows.h>


std::string IPlatformPath::ModulePathName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(nullptr, buffer, MAX_PATH);
	return std::string(buffer);
}

class PlatformPath : public IPlatformPath
{
	std::string modulePathName_;
	std::string modulePath_;

public: 
	PlatformPath()
		: modulePathName_(IPlatformPath::ModulePathName()),
		modulePath_(GetPath())
	{}

	// Inherited via IPlatformPath
	std::string GetModulePathName() const override;
	std::string GetModulePath() const override;
	std::string GetRelativePath(const std::string & relativePath) const override;

private:

	std::string GetPath() const
	{
		std::string::size_type slashPos = modulePathName_.find_last_of("\\/");
		return modulePathName_.substr(0, slashPos + 1);
	}


};

// Inherited via IPlatformPath

std::string PlatformPath::GetModulePathName() const
{
	return modulePathName_;
}

std::string PlatformPath::GetModulePath() const
{
	return modulePath_;
}

std::string PlatformPath::GetRelativePath(const std::string & relativePath) const
{
	return std::string(modulePath_ + relativePath);
}

// factory
std::unique_ptr<IPlatformPath> IPlatformPath::Create()
{
	return std::make_unique<PlatformPath>();
}

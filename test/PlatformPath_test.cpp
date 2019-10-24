#include <iostream>
#include "IPlatformPath.h"

//std::string module_path = MODULE_PATH;

int main()
{
	auto path = IPlatformPath::Create();
	std::cout << path->GetModulePath();
	return 0;
}
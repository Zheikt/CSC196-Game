#include "FileIO.h"

namespace Enginuity 
{
	std::string Enginuity::getFilePath()
	{
		return std::filesystem::current_path().string();
	}
}

#include"Options.h"

void Options::setValue(std::string key, std::string value)
{
	storedOptions[key] = value;
}

std::string Options::getValue(std::string key)
{
	if (storedOptions.find(key) != storedOptions.end())
	{
		return storedOptions[key];
	}
	return "";
}

void Options::parseFile(std::ifstream& inStream)
{
	storedOptions.clear();
	std::string key, value;
	while (inStream >> key >> value)
	{
		storedOptions[key] = value;
	}
}

void Options::save(std::ofstream& outStream)
{
	for (auto const& x : storedOptions)
	{
		outStream << x.first << ' ' << x.second << std::endl;
	}
}
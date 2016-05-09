#ifndef OPTIONS_H
#define OPTIONS_H

#include <fstream>
#include <map>
#include <string>

class Options
{
private:
	Options() {};
	Options(const Options&);
	Options& operator=(const Options&);
	std::map<std::string, std::string> storedOptions;
public:
	static Options& get()
	{
		static Options instance;
		return instance;
	}
	void parseFile(std::ifstream& inStream);
	std::string getValue(std::string key);
	void setValue(std::string key, std::string value);
	void save(std::ofstream& inStream);
};

#endif
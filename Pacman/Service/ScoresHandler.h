#ifndef SCORES_HANDLER_H
#define SCORES_HANDLER_H

#include<fstream>
#include<vector>
#include<string>

class ScoresHandler
{
private:
	ScoresHandler() {};
	ScoresHandler(const ScoresHandler&);
	ScoresHandler& operator=(const ScoresHandler&);
	std::vector<std::pair<std::string, int>> scores;
public:
	static ScoresHandler& get()
	{
		static ScoresHandler instance;
		return instance;
	}
	void parseFile(std::ifstream& inStream);
	std::vector<std::pair<std::string, int>> getScores();
	int recordNewScore(std::string name, int score);
	int checkPosition(int score);
	void save(std::ofstream& inStream);
};

#endif
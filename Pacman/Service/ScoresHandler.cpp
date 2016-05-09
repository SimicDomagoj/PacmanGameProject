#include"ScoresHandler.h"

std::vector<std::pair<std::string, int>> ScoresHandler::getScores()
{
	return scores;
}

void ScoresHandler::parseFile(std::ifstream& inStream)
{
	scores.clear();
	std::string name;
	int score;
	while (inStream >> name >> score)
	{
		scores.push_back(std::make_pair(name, score));
	}
}

void ScoresHandler::save(std::ofstream& outStream)
{
	for (std::pair<std::string, int> pair : scores)
	{
		outStream << pair.first << ' ' << pair.second << std::endl;
	}
}


int ScoresHandler::recordNewScore(std::string name, int score)
{
	for (unsigned int i = 0; i < scores.size(); ++i)
	{
		if (score > scores[i].second)
		{
			scores.insert(scores.begin() + i, std::make_pair(name, score));
			scores.pop_back();
			return i + 1;
		}
	}
	return 0;
}
int ScoresHandler::checkPosition(int score)
{
	for (unsigned int i = 0; i < scores.size(); ++i)
	{
		if (score > scores[i].second)
		{
			return i + 1;
		}
	}
	return 0;
}
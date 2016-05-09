#include"PacmanMap.h"
#include"../Service/CollisionService.h"
#include<sstream>
#include<fstream>

PacmanMap::PacmanMap(std::string file)
{
	height = 0;
	std::vector<int> tempMap;
	std::ifstream load;
	load.open(file);
	std::string loadString;
	if (load.is_open())
	{
		getline(load, loadString);
		while (loadString != "pos")
		{
			height++;
			std::stringstream ss(loadString);
			std::string item;
			while (std::getline(ss, item, ' '))
			{
				tempMap.push_back(stoi(item));
			}
			getline(load, loadString);
		}
		std::getline(load, loadString);
		SDL_Rect r;
		while (loadString != "d")
		{
			std::stringstream ss(loadString);
			ss >> r.x >> r.y >> r.w >> r.h;
			startPositions.push_back(r);
			std::getline(load, loadString);
		}
		std::getline(load, loadString);
		while (loadString != "u")
		{
			std::stringstream ss(loadString);
			ss >> r.x >> r.y >> r.w >> r.h;
			dots.push_back(r);
			std::getline(load, loadString);
		}
		while (std::getline(load, loadString))
		{
			std::stringstream ss(loadString);
			ss >> r.x >> r.y >> r.w >> r.h;
			pUps.push_back(r);
		}
		width = tempMap.size() / height;
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			field f;
			f.area = SDL_Rect{ 180 + i * 40, 20 + j * 40 , 40, 40};
			f.color = SDL_Color{ 0, 0, 0 };
			switch (tempMap[j * width + i])
			{
				case 0: f.type = FieldType::CLEAR_PATH; break;
				case 1: f.type = FieldType::WALL; f.color = SDL_Color{ 0, 51, 83 }; break;
				case 2: f.type = FieldType::CROSSROAD; break;
				case 3: f.type = FieldType::PACMAN_ONLY_CROSSROAD; break;
				case 4: f.type = FieldType::CORNER; break;
				case 5: f.type = FieldType::CAGE; break;
				case 6: f.type = FieldType::CAGE_ENTRANCE; break;
				default: break;
			}
			fields.push_back(f);
			if (f.type == FieldType::CAGE)
			{
				field b;
				b.area = f.area;
				b.area.h = 3;
				b.color = SDL_Color{ 0, 51, 83 };
				b.type = FieldType::WALL;
				boundaries.push_back(b);
				b.area.y += 37;
				boundaries.push_back(b);
				b.area = f.area;
				b.area.y += 3;
				b.area.w = 3;
				b.area.h = 34;
				if (tempMap[j * width + i + 1] != 6)
				{
					b.area.x += 37;
				}
				boundaries.push_back(b);
			}
			else if (f.type == FieldType::CAGE_ENTRANCE)
			{
				field b;
				b.area = f.area;
				b.area.h = 2;
				b.color = SDL_Color{ 9, 204, 4 };
				b.type = FieldType::DOOR;
				boundaries.push_back(b);
				b.area.h = 3;
				b.area.y += 37;
				b.type = FieldType::WALL;
				b.color = SDL_Color{ 0, 51, 83 };
				boundaries.push_back(b);
			}
		}
	}
	field b;
	b.area = SDL_Rect{180, 18, 600, 2};
	b.color = SDL_Color{ 0, 51, 83 };
	b.type = FieldType::WALL;
	boundaries.push_back(b);
	b.area = SDL_Rect{ 180, 700, 600, 2 };
	boundaries.push_back(b);
	b.area = SDL_Rect{ 178, 18, 2, 282 };
	boundaries.push_back(b);
	b.area = SDL_Rect{ 178, 340, 2, 362 };
	boundaries.push_back(b);
	b.area = SDL_Rect{ 780, 18, 2, 282 };
	boundaries.push_back(b);
	b.area = SDL_Rect{ 780, 340, 2, 362 };
	boundaries.push_back(b);
}

PacmanMap::~PacmanMap()
{

}

FieldType PacmanMap::getAtXY(int x, int y)
{
	return fields[y * width + x].type;
}

void PacmanMap::render(std::shared_ptr<SDL_Renderer> renderer)
{
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		SDL_SetRenderDrawColor(renderer.get(), fields[i].color.r, fields[i].color.g, fields[i].color.b, 255);
		SDL_RenderFillRect(renderer.get(), &fields[i].area);
	}
	for (unsigned int i = 0; i < boundaries.size(); i++)
	{
		SDL_SetRenderDrawColor(renderer.get(), boundaries[i].color.r, boundaries[i].color.g, boundaries[i].color.b, 255);
		SDL_RenderFillRect(renderer.get(), &boundaries[i].area);
	}
}

SDL_Rect PacmanMap::getPacmanStartPos()
{
	return startPositions[0];
}
SDL_Rect PacmanMap::getGhostStartPos(eGhost ghost)
{
	return startPositions[1 + static_cast<int>(ghost)];
}
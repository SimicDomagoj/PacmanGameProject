#ifndef SUBJECT
#define SUBJECT
#include"IObserver.h"
#include<memory>
#include<vector>
#include<algorithm>

class Subject
{
	std::vector<std::shared_ptr<IObserver>> list;
public:
	void attach(std::shared_ptr<IObserver> observer) { list.push_back(observer); }
	void detach(std::shared_ptr<IObserver> observer) { list.erase(std::remove(list.begin(), list.end(), observer), list.end()); }
	void notify()
	{
		for (std::vector<std::shared_ptr<IObserver>>::iterator it = std::begin(list); it != std::end(list); ++it)
		{
			it->get()->update();
		}
	};
};

#endif
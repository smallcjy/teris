#pragma once
#include<vector>
class GameAttribute
{
public:
	int windowWidth;
	int windowHeigh;
	int terisWidth;
	int terisHeight;
	int terisBottom;
	std::vector<int> gameWindoworigin;
	std::vector<int> gameTerisorigin;
public:
	GameAttribute();
};


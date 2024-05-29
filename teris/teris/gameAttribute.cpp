#include "gameAttribute.h"
GameAttribute::GameAttribute() {
	this->windowWidth = 654*2;
	this->windowHeigh = 355*2;
	this->terisWidth = 110*2;
	this->terisHeight = 220*2;
	this->terisBottom = 538;
	std::vector<int> Origin = { 120*2, 60*2 };
	std::vector<int> terisOrigin = {265*2, 60*2};//x y
	this->gameWindoworigin = Origin;
	this->gameTerisorigin = terisOrigin;
}
#pragma once
class Pos
{
public:
	int x;
	int y;
	Pos() {};
	Pos(int x,int y);
	//¿½±´¹¹Ôì
	Pos(Pos& pos) {
		this->x = pos.x;
		this->y = pos.y;
	}
};


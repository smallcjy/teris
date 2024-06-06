#pragma once
#include"Pos.h"
const int BlockWidth = 22;

enum blockType {
	ti,		//T型
	yi,		//一型
	qi,		//七型
	fang,	//方型
	z		//Z型
};

class TerisShape
{
public:
	Pos blockPos[4];
	int nowshape = 0;
	int type = 999;
public:
	TerisShape() {};
	void craftLeftMove();
	void craftRightMove();
	void craftDown();
	bool leftSideCheck();
	bool rightSideCheck();
	virtual void spin(int s) = 0;
};

class TShape : public TerisShape {
public:
	TShape(){}
	TShape(Pos p1) {
		this->type = ti;
		blockPos[0] = p1;
		Pos p2(p1.x + BlockWidth, p1.y);
		Pos p3(p2.x + BlockWidth, p1.y);
		Pos p4(p2.x, p2.y + BlockWidth);
		blockPos[1] = p2;
		blockPos[2] = p3;
		blockPos[3] = p4;
	}
	TShape(Pos p1, Pos p2, Pos p3, Pos p4) {
		this->type = ti;
		this->blockPos[0] = p1;
		this->blockPos[1] = p2;
		this->blockPos[2] = p3;
		this->blockPos[3] = p4;
}
	virtual void spin(int s) override;
};


class YShape : public TerisShape {
public:
	YShape(Pos p1) {
		this->type = yi;
		blockPos[0] = p1;
		Pos p2(p1.x + BlockWidth, p1.y);
		Pos p3(p2.x + BlockWidth, p1.y);
		Pos p4(p3.x + BlockWidth, p1.y);
		blockPos[1] = p2;
		blockPos[2] = p3;
		blockPos[3] = p4;
	}
	YShape(Pos p1, Pos p2, Pos p3, Pos p4) {
		this->type = ti;
		this->blockPos[0] = p1;
		this->blockPos[1] = p2;
		this->blockPos[2] = p3;
		this->blockPos[3] = p4;
	}
	virtual void spin(int s) override;
};


class QShape : public TerisShape {
public:
	QShape(Pos p1) {
		this->type = qi;
		blockPos[0] = p1;
		Pos p2(p1.x, p1.y + BlockWidth);
		Pos p3(p2.x + BlockWidth, p1.y);
		Pos p4(p3.x + BlockWidth, p1.y);
		blockPos[1] = p2;
		blockPos[2] = p3;
		blockPos[3] = p4;
	}
	QShape(Pos p1, Pos p2, Pos p3, Pos p4) {
		this->type = ti;
		this->blockPos[0] = p1;
		this->blockPos[1] = p2;
		this->blockPos[2] = p3;
		this->blockPos[3] = p4;
	}
	virtual void spin(int s) override;
};

//■■
//■■
class FShape : public TerisShape {
public:
	FShape(Pos p1) {
		this->type = fang;
		blockPos[0] = p1;
		Pos p2(p1.x + BlockWidth, p1.y);
		Pos p3(p1.x, p1.y + BlockWidth);
		Pos p4(p1.x + BlockWidth, p1.y + BlockWidth);
		blockPos[1] = p2;
		blockPos[2] = p3;
		blockPos[3] = p4;
	}
	FShape(Pos p1, Pos p2, Pos p3, Pos p4) {
		this->type = ti;
		this->blockPos[0] = p1;
		this->blockPos[1] = p2;
		this->blockPos[2] = p3;
		this->blockPos[3] = p4;
	}
	virtual void spin(int s)  override;
};

class ZShape : public TerisShape {
public:
	ZShape(Pos p1) {
		this->type = z;
		blockPos[0] = p1;
		Pos p2(p1.x, p1.y + BlockWidth);
		Pos p3(p2.x + BlockWidth, p1.y + BlockWidth);
		Pos p4(p3.x, p3.y + BlockWidth);
		blockPos[1] = p2;
		blockPos[2] = p3;
		blockPos[3] = p4;
	}
	ZShape(Pos p1, Pos p2, Pos p3, Pos p4) {
		this->type = ti;
		this->blockPos[0] = p1;
		this->blockPos[1] = p2;
		this->blockPos[2] = p3;
		this->blockPos[3] = p4;
	}
	virtual void spin(int s) override;
};

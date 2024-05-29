#include "Shape.h"

void FShape::spin(int s) {
	return;
}

void QShape::spin(int s) {
	//根据传进来的int来选择旋转后的形状,逆时针旋转
	switch (s) {
	case 0: {
		this->blockPos[0].x = this->blockPos[2].x;
		this->blockPos[0].y = this->blockPos[2].y - BlockWidth;
		this->blockPos[1].x = this->blockPos[2].x;
		this->blockPos[1].y = this->blockPos[2].y + BlockWidth;
		this->blockPos[3].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y;
		break;
	}
	case 1:{
		this, blockPos[0].x = this->blockPos[2].x - BlockWidth;
		this->blockPos[0].y = this->blockPos[2].y;
		this->blockPos[1].x = this->blockPos[2].x + BlockWidth;
		this->blockPos[1].y = this->blockPos[2].y;
		this->blockPos[3].x = this->blockPos[1].x;
		this->blockPos[3].y = this->blockPos[1].y - BlockWidth;
		break;
	}
	case 2: {
		this->blockPos[0].x = this->blockPos[2].x - BlockWidth;
		this->blockPos[0].y = this->blockPos[2].y - BlockWidth;
		this->blockPos[1].x = this->blockPos[2].x;
		this->blockPos[1].y = this->blockPos[2].y - BlockWidth;
		this->blockPos[3].x = this->blockPos[2].x;
		this->blockPos[3].y = this->blockPos[2].y + BlockWidth;
		break;
	}
	case 3: {
		this->blockPos[0].x = this->blockPos[2].x - BlockWidth;
		this->blockPos[0].y = this->blockPos[2].y;
		this->blockPos[1].x = this->blockPos[2].x + BlockWidth;
		this->blockPos[1].y = this->blockPos[2].y;
		this->blockPos[3].x = this->blockPos[2].x - BlockWidth;
		this->blockPos[3].y = this->blockPos[2].y + BlockWidth;
		break;
	}
	}

	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x < 530) {
			craftRightMove();
		}
		else if (this->blockPos[i].x > 750 - BlockWidth) {
			craftLeftMove();
		}
	}
	
	return;
}

void TShape::spin(int s) {
	switch (s) {
	case 0: {
		this->blockPos[0].x = this->blockPos[1].x;
		this->blockPos[0].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[2].x = this->blockPos[1].x;
		this->blockPos[2].y = this->blockPos[1].y + BlockWidth;
		this->blockPos[3].x = this->blockPos[3].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y;
		break;
	}
	case 1: {
		this->blockPos[0].x = this->blockPos[1].x - BlockWidth;
		this->blockPos[0].y = this->blockPos[1].y;
		this->blockPos[2].x = this->blockPos[1].x;
		this->blockPos[2].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[3].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y;
		break;
	}
	case 2: {
		this->blockPos[0].x = this->blockPos[1].x;
		this->blockPos[0].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[2].x = this->blockPos[1].x - BlockWidth;
		this->blockPos[2].y = this->blockPos[1].y;
		this->blockPos[3].x = this->blockPos[1].x;
		this->blockPos[3].y = this->blockPos[1].y + BlockWidth;
		break;
	}
	case 3: {
		this->blockPos[0].x = this->blockPos[1].x-BlockWidth;
		this->blockPos[0].y = this->blockPos[1].y;
		this->blockPos[2].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[2].y = this->blockPos[1].y;
		this->blockPos[3].x = this->blockPos[1].x;
		this->blockPos[3].y = this->blockPos[1].y + BlockWidth;
		break;
	}
		  
	}
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x < 530) {
			craftRightMove();
		}
		else if (this->blockPos[i].x > 750 - BlockWidth) {
			craftLeftMove();
		}
	}
	return;
}

void YShape::spin(int s) {
	switch (s) {
	case 0: {
		this->blockPos[0].x = this->blockPos[3].x;
		this->blockPos[0].y = this->blockPos[3].y - 3 * BlockWidth;
		this->blockPos[1].x = this->blockPos[3].x;
		this->blockPos[1].y = this->blockPos[3].y - 2 * BlockWidth;
		this->blockPos[2].x = this->blockPos[3].x;
		this->blockPos[2].y = this->blockPos[3].y - BlockWidth;
		break;
	}
	case 1: {
		this->blockPos[0].x = this->blockPos[3].x - 3 * BlockWidth;
		this->blockPos[0].y = this->blockPos[3].y;
		this->blockPos[1].x = this->blockPos[3].x - 2 * BlockWidth;
		this->blockPos[1].y = this->blockPos[3].y;
		this->blockPos[2].x = this->blockPos[3].x - BlockWidth;
		this->blockPos[2].y = this->blockPos[3].y;

		break;
	}
	case 2: {
		this->blockPos[0].x = this->blockPos[3].x;
		this->blockPos[0].y = this->blockPos[3].y - 3 * BlockWidth;
		this->blockPos[1].x = this->blockPos[3].x;
		this->blockPos[1].y = this->blockPos[3].y - 2 * BlockWidth;
		this->blockPos[2].x = this->blockPos[3].x;
		this->blockPos[2].y = this->blockPos[3].y - BlockWidth;
		break;
	}
	case 3: {
		this->blockPos[0].x = this->blockPos[3].x - 3 * BlockWidth;
		this->blockPos[0].y = this->blockPos[3].y;
		this->blockPos[1].x = this->blockPos[3].x - 2 * BlockWidth;
		this->blockPos[1].y = this->blockPos[3].y;
		this->blockPos[2].x = this->blockPos[3].x - BlockWidth;
		this->blockPos[2].y = this->blockPos[3].y;
		break;
	}
	}
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x < 530) {
			craftRightMove();
		}
		else if (this->blockPos[i].x > 750 - BlockWidth) {
			craftLeftMove();
		}
	}
}


void ZShape::spin(int s) {
	switch (s) {
	case 0: {
		this->blockPos[0].x = this->blockPos[1].x - BlockWidth;
		this->blockPos[0].y = this->blockPos[1].y;
		this->blockPos[2].x = this->blockPos[1].x;
		this->blockPos[2].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[3].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y - BlockWidth;
		break;
	}
	case 1: {
		this->blockPos[0].x = this->blockPos[1].x;
		this->blockPos[0].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[2].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[2].y = this->blockPos[1].y;
		this->blockPos[3].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y + BlockWidth;
		break;
	}
	case 2: {
		this->blockPos[0].x = this->blockPos[1].x - BlockWidth;
		this->blockPos[0].y = this->blockPos[1].y;
		this->blockPos[2].x = this->blockPos[1].x;
		this->blockPos[2].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[3].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y - BlockWidth;
		break;
	}
	case 3: {
		this->blockPos[0].x = this->blockPos[1].x;
		this->blockPos[0].y = this->blockPos[1].y - BlockWidth;
		this->blockPos[2].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[2].y = this->blockPos[1].y;
		this->blockPos[3].x = this->blockPos[1].x + BlockWidth;
		this->blockPos[3].y = this->blockPos[1].y + BlockWidth;
		break;
	}
	}
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x < 530) {
			craftRightMove();
		}
		else if (this->blockPos[i].x > 750 - BlockWidth) {
			craftLeftMove();
		}
	}
	return;
}


void TerisShape::craftLeftMove() {
	//判断是否会触碰到左右边界
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x - BlockWidth< 530) {
			return;
		}
	}

	for (int i = 0; i < 4; i++) {
		this->blockPos[i].x -= BlockWidth;
	}
}

void TerisShape::craftRightMove() {
	//判断是否会触碰到左右边界
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x + BlockWidth > 750-22) {
			return;
		}
	}
	for (int i = 0; i < 4; i++) {
		this->blockPos[i].x += BlockWidth;
	}
}

void TerisShape::craftDown() {
	for (int i = 0; i < 4; i++) {
		this->blockPos[i].y += 2;
	}
}

bool TerisShape::leftSideCheck() {
	bool result = false;
	//检测四个方块中是否有方块在左右边界上或超过边界

	//检测左边界
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x <= 530) {
			result = true;
		}
	}
	return result;
}

bool TerisShape::rightSideCheck() {
	bool result = false;
	//检测四个方块中是否有方块在左右边界上或超过边界

	//检测右边界
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x >= 750) {
			result = true;
		}
	}
	return result;
}
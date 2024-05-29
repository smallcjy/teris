#include "Shape.h"

void FShape::spin(int s) {
	return;
}

void QShape::spin(int s) {
	//���ݴ�������int��ѡ����ת�����״,��ʱ����ת
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
	//�ж��Ƿ�ᴥ�������ұ߽�
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
	//�ж��Ƿ�ᴥ�������ұ߽�
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
	//����ĸ��������Ƿ��з��������ұ߽��ϻ򳬹��߽�

	//�����߽�
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x <= 530) {
			result = true;
		}
	}
	return result;
}

bool TerisShape::rightSideCheck() {
	bool result = false;
	//����ĸ��������Ƿ��з��������ұ߽��ϻ򳬹��߽�

	//����ұ߽�
	for (int i = 0; i < 4; i++) {
		if (this->blockPos[i].x >= 750) {
			result = true;
		}
	}
	return result;
}
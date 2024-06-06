#include "game.h"
//������Ϸ��ʼ����
GameAttribute game::gA;
//teris��ͼ��״̬
int game::map_width = gA.terisWidth / 10;
int game::map_height = gA.terisHeight / 20;
vector<vector<int>> game::map;
//��ʱ��
DWORD game::timePre = GetTickCount();
DWORD game::timeNow = GetTickCount();
//��Ϸ״̬
int game::game_state = game::gameState::gameMenu;
//�����Ϣ
MOUSEMSG game::msg;
//����λ�ú�x���ֵĿ���λ��
int game::shapePosX;
vector<int> game::shapePosXs;
//����Ŀ��
const int blockWidth = 22;

int game::nowType;
int game::nextType;
TerisShape* game::nowShape;
TerisShape* game::nextShape;

bool game::isLocated = 0;
bool game::isQuickDown = 0;

int game::winScore = 0;

int game::spinShape[4] = { 0,1,2,3 };


void gameWindow::gameWindowInit() {
	initgraph(wedith, length, NULL);
	//���ñ���ͼƬ
	IMAGE backgound;
	loadimage(&backgound, "D:\\E\\computerlearning\\C++\\C++ʵѵ\\teris\\backgroundpicture.jpg",wedith,length ,true);
	putimage(0, 0, &backgound);
	//����teris��Ϸ����
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	setfillcolor(BLACK);
	line(263*2, 60*2, 263*2, 280*2);
	line(377*2, 60*2, 377*2, 280*2);
	//���ƿ�ʼ��Ϸͼ��
	fillrectangle(826, 177, 985, 232);
	settextstyle(35,0 ,NULL);
	outtextxy(840, 190, "GameStart");
	//������ͣ��Ϸͼ��
	fillrectangle(826, 267, 985, 312);
	settextstyle(35, 0, NULL);
	outtextxy(865, 273, "Pause");
	//���Ƽ�����Ϸͼ��
	fillrectangle(826, 357, 985, 402);
	settextstyle(35, 0, NULL);
	outtextxy(850, 363, "Continue");
	//���ƽ�����Ϸͼ��
	fillrectangle(826, 447, 985, 492);
	settextstyle(35, 0, NULL);
	outtextxy(873, 453, "EXIT");
	//���Ʊ�����Ϸͼ��
	fillrectangle(826, 527, 985, 572);
	settextstyle(35, 0, NULL);
	outtextxy(873, 533, "SAVE");
	//Ԥ����һ������ͼ��Ĵ���
	rectangle(300, 150, 450, 300);
	//����scoreͼ��
	rectangle(300, 330, 450, 480);
	fillrectangle(300, 330, 450, 380);
	settextstyle(35, 0, NULL);
	outtextxy(327, 341, "SCORE");
	settextcolor(BLACK);
	setbkcolor(WHITE);
	settextstyle(60, 0, NULL);
	outtextxy(360, 400, '0');

	////test
	//game::drawGameOver();

}

void game::gameMenuDraw() {
	gameWindow gw(654*2, 355*2);
	gw.gameWindowInit();
}


void game::gameInit() {
	//��ͼ��ʼ��
	mapInit();
	//game::gameMapDraw();
	//scores��ʼ��
	xScoreInit();
	//��������
	winScore = 0;
	game::updateScoreDraw();
	//������ɵ�һ�������λ�ú���״
	int index = 0;
	index = rand() % 6;
	shapePosX = shapePosXs[index];
	//������һ�����������
	Pos px(game::gA.gameTerisorigin[0] + shapePosX, gA.gameTerisorigin[1]);
	nowType = rand() % 5;
	//������һ������
	switch (nowType) {
	case 0:
		nowShape = new TShape(px);
		break;
	case 1:
		nowShape = new YShape(px);
		break;
	case 2:
		nowShape = new QShape(px);
		break;
	case 3:
		nowShape = new FShape(px);
		break;
	case 4:
		nowShape = new ZShape(px);
		break;
	default:
		break;
	}
	//����һ����һ���������״
	game::gamePreGainNextBlock();
}

void game::continueGameInit() {
	//scores��ʼ��
	xScoreInit();
	//��ʼ����״ָ��
	nowShape = new TShape();
	nextShape = new TShape();
	readMap();
	readGameStates();
	game_state = game::gameState::gamePlaying;
}

void game::gamePreGainNextBlock() {
	//������ɵ�һ�������λ�ú���״
	int index = 0;
	index = rand() % 6;
	shapePosX = shapePosXs[index];
	//������һ�����������
	Pos px(shapePosX + gA.gameTerisorigin[0], gA.gameTerisorigin[1]);
	nextType = rand() % 5;
	//������һ������
	switch (nextType) {
	case 0:
		nextShape = new TShape(px);
		break;
	case 1:
		nextShape = new YShape(px);
		break;
	case 2:
		nextShape = new QShape(px);
		break;
	case 3:
		nextShape = new FShape(px);
		break;
	case 4:
		nextShape = new ZShape(px);
		break;
	default:
		break;
	}
	//������һ��������ʾ
	game::drawNextBlock();
}

void game::gameStateSelect() {
	if (MouseHit()) {
		mouseAction();
	}
	switch (game_state) {
	case game::gameState::gameMenu: {
		break;
	}
	case game::gameState::gameStartNewGame: {
		//��Ϸ��ʼǰ�Ȳ鿴������û�д浵���������ʾ����Ƿ������һ�̼�����
		if (!game::checkLocalFile()) {
			game::drawTellContinue();
			FlushBatchDraw();
			while (1) {
				msg = GetMouseMsg();
				//�ж��Ƿ������һ����Ϸ
				if (msg.x >= 558 && msg.x <= 622 && msg.y >= 489 && msg.y <= 524 && msg.uMsg == WM_LBUTTONDOWN) {
					game_state = game::gameState::gameStartOldGame;
					break;
				}
				if (msg.x >= 669 && msg.x <= 735 && msg.y >= 489 && msg.y <= 524 && msg.uMsg == WM_LBUTTONDOWN) {
					break;
				}
			}
		}

		if (game_state == game::gameState::gameStartOldGame) break;

		game::gameInit();
		//����Ϸ��״̬����Ϊplaying
		game::game_state = game::gameState::gamePlaying;
		break;

	}
	case game::gameState::gameStartOldGame: {
		game::continueGameInit();
		break;
	}
	case game::gameState::gamePlaying: {
		game::gameplay();

		break;
	}
	case game::gameState::gameOver: {
		//������Ϸ����ͼ����ʾ���
		game::drawGameOver();

		//�ȴ���һ������
		if (MouseHit()) {
			mouseAction();
		}
		break;
	}
	case game::gameState::gamePause: {
		//�ȴ���һ������
		mouseAction();
		break;
	}
	case game::gameState::gameSave: {
		saveMap();
		saveGameState();
		//�ȴ���һ������
		mouseAction();
	}
	default:
		break;
	}
}

void game::mouseAction() {
	msg = GetMouseMsg();
	//�ж��Ƿ�����ʼ��Ϸ��ť
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 117 && msg.y <= 232 && msg.uMsg == WM_LBUTTONDOWN) {
		game_state = game::gameState::gameStartNewGame;
	}
	//�ж��Ƿ���������Ϸ��ť
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 447 && msg.y <= 492 && msg.uMsg == WM_LBUTTONDOWN) {
		//�˳�����
		closegraph();
	}
	//�ж��Ƿ�����ͣ
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 267 && msg.y <= 312 && msg.uMsg == WM_LBUTTONDOWN) {
		game_state = game::gameState::gamePause;
		Sleep(30);
	}
	//�ж��Ƿ�������
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 357 && msg.y <= 402 && msg.uMsg == WM_LBUTTONDOWN) {
		game_state = game::gameState::gamePlaying;
		Sleep(30);
	}
	//�ж��Ƿ���������Ϸ��ť
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 527 && msg.y <= 572 && msg.uMsg == WM_LBUTTONDOWN) {
		//�˳�����
		game_state = game::gameState::gameSave;
	}
}

void game::mapInit() {
	for (int i = 0; i < 20; i++) {
		vector<int> line;
		map.push_back(line);
		for (int j = 0; j < 10; j++) {
			map[i].push_back(0);
		}
	}
}

void game::xScoreInit() {
	if (game::shapePosXs.size() == 0) {
		for (int i = 0; i < 6; i++) {
			game::shapePosXs.push_back(blockWidth * i);
		}
	}
}

//��Ϸ����
void game::gameplay() {
	game::gameplaying();
	
}

void game::gameplaying() {
	//�ж���һ֡�Ƿ��з���Ҫ��������
	if (isQuickDown || isLocated) {
		//Ҫ������һ��������
		game::gamePreGainNextBlock();
		isQuickDown = 0;
		isLocated = 0;
	}
	//���Ƶ�ͼ
	game::gameMapDraw();

	//�����Ϸ�Ƿ����
	if (game::checkGameOver()) {
		game::game_state = game::gameState::gameOver;
		return;
	}

	//�˴�Ӧ���ڻ��Ʒ���֮ǰ�жϷ�ֹ�Ѿ���Ϸ�����˻����Ƶ���һ������

	//���Ʒ���
	for (int i = 0; i < 4; i++) {
		game::drawCraft(nowShape->blockPos[i]);
	}

	//����Ԥ����״
	drawPreShape();

	//����Ƿ��еײ���ײ������о�û��Ҫ�ƶ���ת��
	if (game::craftCheckAndMoveDown()) {
		return;
	}

	//����Ƿ��п����½����ź�,����о�û��Ҫ�ƶ���ת��
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		quickDown();
		//˯��һ�·����ظ�����
		Sleep(100);
		return;
	}

	//����Ƿ����ƶ����ź�
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (!twoSideCrash()) {
			nowShape->craftLeftMove();
		}
		//˯��һ�·����ظ�����
		Sleep(100);
		
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (!twoSideCrash()) {
			nowShape->craftRightMove();
		}
		//˯��һ�·����ظ�����
		Sleep(100);
	}
	//����Ƿ�����ת���ź�
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		nowShape->spin(spinShape[nowShape->nowshape]);
		nowShape->nowshape++;
		if (nowShape->nowshape == 4) nowShape->nowshape = 0;
		//˯��һ�·����ظ�����
		Sleep(100);
	}



	//�ж�������
	RemoveCol();
}

//���Ʒ���
void game::drawCraft(Pos p) {
	//��Ϸ��ͼ����ķ��鲻�ܻ�
	if (p.y < 120)return;
	setfillcolor(BLACK);
	solidrectangle(p.x, p.y, p.x + blockWidth, p.y + blockWidth);
}

void game::drawPreCraft(Pos p) {
	//��Ϸ��ͼ����ķ��鲻�ܻ�
	if (p.y < 120)return;
	rectangle(p.x, p.y, p.x + blockWidth, p.y + blockWidth);
}

//���Ƶ�ͼ
void game::gameMapDraw() {
	setbkcolor(WHITE);
	//�������ڻ滭
	clearrectangle(528, 120, 752, 565);
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != 0) {
				//�����õ������
				Pos p(gA.gameTerisorigin[0] + j * blockWidth, gA.gameTerisorigin[1] + i* blockWidth);
				game::drawCraft(p);
			}
		}
	}
}

//���������Ƿ������Ϸ����
void game::drawTellContinue() {
	setbkcolor(WHITE);
	//�������ڻ滭
	clearrectangle(528, 120, 752, 565);
	//��������
	settextstyle(30, 0, NULL);
	outtextxy(540, 195, "You has archive");
	outtextxy(546, 300, "continue or not");
	settextstyle(40, 0, NULL);
	outtextxy(558, 489, "Yes");
	outtextxy(669, 489, "Not");


}

void game::Pos2Map(Pos p) {
	int i = (p.y - game::gA.gameTerisorigin[1]) / 22;
	int j = (p.x - game::gA.gameTerisorigin[0]) / 22;
	if (i > 19 || j > 9) return;
	game::map[i][j] = 1;
}

bool game::hasCraft(Pos p) {
	int i = (p.y - game::gA.gameTerisorigin[1]) / 22;
	int j = (p.x - game::gA.gameTerisorigin[0]) / 22;
	//������Ϸ��Χ��Ĭ��Ϊ�з���
	if (i > 19 || j > 9 || i < 0 || j < 0) return false;
	if (map[i][j] == 1)return true;
	return false;
}

bool game::twoSideCrash() {
	for (int i = 0; i < 4; i++) {
		Pos pLeft(nowShape->blockPos[i].x - blockWidth, nowShape->blockPos[i].y);
		Pos pRight(nowShape->blockPos[i].x + blockWidth, nowShape->blockPos[i].y);
		if (game::hasCraft(pLeft) || game::hasCraft(pRight)) {
			return true;
		}
	}
	return false;
}

bool game::craftCheckAndMoveDown() {
	//���ж��Ƿ������ײ��߽�
	for (int i = 0; i < 4; i++) {
		if (nowShape->blockPos[i].y == gA.terisBottom) {
			//��ײ���ײ��߽�
			isLocated = 1;
			//��ס����,update map
			for (int i = 0; i < 4; i++) {
				Pos2Map(nowShape->blockPos[i]);
			}
			//�л���ǰ����
			nowShape = nextShape;
			return true;
		}
		//���жϷ�����Χ�Ƿ��з��飬�����з��鲻����ײ�����½�
		//���ɸõ������Pos
		Pos pDown(nowShape->blockPos[i].x, nowShape->blockPos[i].y + blockWidth);
		if (hasCraft(pDown)) {
			isLocated = 1;
			//��ס����,update map
			for (int i = 0; i < 4; i++) {
				Pos2Map(nowShape->blockPos[i]);
			}
			//�л���ǰ����
			nowShape = nextShape;
			return true;
		}
	}
	nowShape->craftDown();
	Sleep(25);
	return false;
}

bool game::simCraftCheckAndMoveDown(TerisShape *simShape) {
	//���ж��Ƿ������ײ��߽�
	for (int i = 0; i < 4; i++) {
		if (simShape->blockPos[i].y == gA.terisBottom) {
			//��ײ���ײ��߽�
			return true;
		}
		//���жϷ�����Χ�Ƿ��з��飬�����з��鲻����ײ�����½�
		//���ɸõ������Pos
		Pos pDown(simShape->blockPos[i].x, simShape->blockPos[i].y + blockWidth);
		if (hasCraft(pDown)) {
			return true;
		}
	}
	simShape->craftDown();
	return false;
}

void game::RemoveCol() {
	vector<int> canRemove;
	vector<vector<int>> newMap;
	for (int i = 0; i < 20; i++) {
		vector<int> col;
		newMap.push_back(col);
		for (int j = 0; j < 10; j++) {
			newMap[i].push_back(0);
		}
	}
	for (int i = 0; i < 20; i++) {
		bool result = 1;
		for (int j = 0; j < 10; j++) {
			if (game::map[i][j] == 0)result = 0;
		}
		canRemove.push_back(result);
	}
	//�ж��Ƿ���Ҫ������
	bool result = 1;
	for (int i = 0; i < canRemove.size(); i++) {
		if (canRemove[i] == 1) result = 0;
	}
	if (result == 1) return;

	//ִ�����У��½�һ��map�������ǰ��Ϊ0������map��������������ʣ���в�0��
	//���������
	int col = 19;
	for (int i = canRemove.size()-1; i >= 0; i--) {
		if (canRemove[i] == 0) {

			for (int j = 0; j < 10; j++) {
				newMap[col][j] = map[i][j];
			}
			col--;
		}
	}
	for (int i = col; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			newMap[col][j] = 0;
		}
	}
	game::map = newMap;

	//�ӷ֣�����һ�м�10�֡�
	for (int i = 0; i < canRemove.size(); i++) {
		if (canRemove[i] == 1)game::winScore += 10;
	}

	//���·�����ʾ
	game::updateScoreDraw();
}

bool game::checkGameOver() {
	bool result = false;
	for (int i = 0; i < 10; i++) {
		if (map[0][i] == 1) {
			result = true;
		}
	}
	return result;
}

void game::drawNextBlock() {
	int preDrawBlockWidth = 30;
	//��֮ǰ�������һ��ͼ��
	setbkcolor(WHITE);
	clearrectangle(302, 152, 448, 298);
	switch (game::nextType) {
	case 0: {
		//ti
		int x = 350;
		int y = 200;
		fillrectangle(x, y, x + preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x-preDrawBlockWidth, y, x, y + preDrawBlockWidth);
		fillrectangle(x+preDrawBlockWidth, y, x + 2*preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x, y+preDrawBlockWidth, x + preDrawBlockWidth, y + 2*preDrawBlockWidth);
		
		break;
	}
	case 1: {
		//yi
		preDrawBlockWidth = 20;
		int x = 355;
		int y = 215;
		fillrectangle(x, y, x + preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x-preDrawBlockWidth, y, x, y + preDrawBlockWidth);
		fillrectangle(x+preDrawBlockWidth, y, x + 2*preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x+2*preDrawBlockWidth, y, x + 3*preDrawBlockWidth, y + preDrawBlockWidth);
		break;
	}
	case 2: {
		//qi
		int x = 330;
		int y = 180;
		fillrectangle(x, y+2*preDrawBlockWidth, x + preDrawBlockWidth, y + 3*preDrawBlockWidth);
		fillrectangle(x, y + preDrawBlockWidth, x + preDrawBlockWidth, y + 2 * preDrawBlockWidth);
		fillrectangle(x + preDrawBlockWidth, y + preDrawBlockWidth, x + 2 * preDrawBlockWidth, y + 2 * preDrawBlockWidth);
		fillrectangle(x + 2 * preDrawBlockWidth, y + preDrawBlockWidth, x + 3 * preDrawBlockWidth, y + 2 * preDrawBlockWidth);
		break;
	}
	case 3: {
		//fang
		int x = 345;
		int y = 195;
		fillrectangle(x, y, x + preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x+preDrawBlockWidth, y, x + 2*preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x, y+preDrawBlockWidth, x + preDrawBlockWidth, y + 2*preDrawBlockWidth);
		fillrectangle(x+preDrawBlockWidth, y+preDrawBlockWidth, x + 2*preDrawBlockWidth, y + 2*preDrawBlockWidth);
		break;
	}case 4: {
		//z
		int x = 330;
		int y = 180;
		fillrectangle(x, y, x + preDrawBlockWidth, y + preDrawBlockWidth);
		fillrectangle(x, y+preDrawBlockWidth, x + preDrawBlockWidth, y + 2*preDrawBlockWidth);
		fillrectangle(x+preDrawBlockWidth, y+preDrawBlockWidth, x + 2*preDrawBlockWidth, y + 2*preDrawBlockWidth);
		fillrectangle(x+preDrawBlockWidth, y+2*preDrawBlockWidth, x + 2*preDrawBlockWidth, y + 3*preDrawBlockWidth);

		break;
	}
	}
}

void game::updateScoreDraw() {
	std::stringstream ss;
	string str_score;
	ss << game::winScore;
	ss >> str_score;
	settextstyle(60, 0, NULL);
	outtextxy(355, 400, str_score.c_str());
}

void game::drawGameOver() {
	setbkcolor(WHITE);
	//�������ڻ滭
	clearrectangle(530, 120, 750, 560);

	//��������
	settextstyle(80, 0, NULL);
	outtextxy(540, 220, "GAME");
	outtextxy(540, 360, "OVER");

}

Pos* game::preCraftPos() {
	//�㷨˼�룺ģ�ⷨ
	//ģ�⵱ǰ������δ����ײʱ��λ��
	//�ȸ��ݸ��ݵ�ǰ��״��������ģ�����
	switch (nowShape->type) {
	case ti: {
		TShape temp(nowShape->blockPos[0],
			nowShape->blockPos[1],
			nowShape->blockPos[2],
			nowShape->blockPos[3]);
		while (!simCraftCheckAndMoveDown(&temp)) {
			continue;
		}

		//ģ�������ʱ��ģ�ⷽ�����Ԥ����ķ���,���ش�ʱ���ĸ������λ������Ԥ���Ϳ����½�
		return temp.blockPos;
		break;
	}
	case yi: {
		YShape temp(nowShape->blockPos[0],
			nowShape->blockPos[1],
			nowShape->blockPos[2],
			nowShape->blockPos[3]);
		while (!simCraftCheckAndMoveDown(&temp)) {
			continue;
		}

		//ģ�������ʱ��ģ�ⷽ�����Ԥ����ķ���,���ش�ʱ���ĸ������λ������Ԥ���Ϳ����½�
		return temp.blockPos;
		break;
	}
	case qi: {
		QShape temp(nowShape->blockPos[0],
			nowShape->blockPos[1],
			nowShape->blockPos[2],
			nowShape->blockPos[3]);
		while (!simCraftCheckAndMoveDown(&temp)) {
			continue;
		}

		//ģ�������ʱ��ģ�ⷽ�����Ԥ����ķ���,���ش�ʱ���ĸ������λ������Ԥ���Ϳ����½�
		return temp.blockPos;
		break;
	}
	case fang: {
		FShape temp(nowShape->blockPos[0],
			nowShape->blockPos[1],
			nowShape->blockPos[2],
			nowShape->blockPos[3]);
		while (!simCraftCheckAndMoveDown(&temp)) {
			continue;
		}

		//ģ�������ʱ��ģ�ⷽ�����Ԥ����ķ���,���ش�ʱ���ĸ������λ������Ԥ���Ϳ����½�
		return temp.blockPos;
		break;
	}
	case z: {
		ZShape temp(nowShape->blockPos[0],
			nowShape->blockPos[1],
			nowShape->blockPos[2],
			nowShape->blockPos[3]);
			while (!simCraftCheckAndMoveDown(&temp)) {
		continue;
	}

	//ģ�������ʱ��ģ�ⷽ�����Ԥ����ķ���,���ش�ʱ���ĸ������λ������Ԥ���Ϳ����½�
	return temp.blockPos;
		break;
	}
	}
}

void game::drawPreShape() {
	Pos* prePos = preCraftPos();
	for (int i = 0; i < 4; i++) {
		drawPreCraft(prePos[i]);
	}
}

void game::quickDown() {
	isQuickDown = 1;
	Pos* prePos = preCraftPos();
	//���µ�ͼ
	for (int i = 0; i < 4; i++) {
		Pos2Map(prePos[i]);
	}
	//���·���
	nowShape = nextShape;
}

void game::saveMap() {
	MapFile mapFile;
	mapFile.deleteContent("map.dat");
	mapFile.writeInFile("map.dat", game::map);
}

void game::saveGameState() {
	//�����оٱ�֤��Ϸ�������еļ�����Ҫ�����״̬
	//gameState
	//nowShape
	//nextShape
	//nowType
	//nextType
	//isLocated
	//isQuicked
	//winScore

	//��˳��д��
	GameStateFile gameStateFile;
	gameStateFile.deleteContent("gameStates.dat");
	gameStateFile.writeInFile("gameStates.dat", game_state, nowShape, nextShape, nowType, nextType, isLocated, isQuickDown, winScore);
	//gameStateFile.readFromFile("gameStates.dat", game_state, *nowShape, *nextShape, nowType, nextType, (int&)isLocated, (int&)isQuickDown, winScore);
}

void game::readMap() {
	MapFile mapFile;
	map.clear();
	mapFile.readFromFile("map.dat", map);


}

void game::readGameStates() {
	GameStateFile gameStatesFile;
	gameStatesFile.readFromFile("gameStates.dat", game_state, nowShape, nextShape, nowType, nextType, (int&)isLocated, (int&)isQuickDown, winScore);
}

bool game::checkLocalFile() {
	MapFile mapFile;
	return mapFile.isEqual("map.dat");

}
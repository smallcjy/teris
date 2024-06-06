#include "game.h"
//设置游戏初始属性
GameAttribute game::gA;
//teris地图的状态
int game::map_width = gA.terisWidth / 10;
int game::map_height = gA.terisHeight / 20;
vector<vector<int>> game::map;
//计时器
DWORD game::timePre = GetTickCount();
DWORD game::timeNow = GetTickCount();
//游戏状态
int game::game_state = game::gameState::gameMenu;
//鼠标信息
MOUSEMSG game::msg;
//核心位置和x出现的可能位置
int game::shapePosX;
vector<int> game::shapePosXs;
//方块的宽度
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
	//设置背景图片
	IMAGE backgound;
	loadimage(&backgound, "D:\\E\\computerlearning\\C++\\C++实训\\teris\\backgroundpicture.jpg",wedith,length ,true);
	putimage(0, 0, &backgound);
	//绘制teris游戏界面
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	setfillcolor(BLACK);
	line(263*2, 60*2, 263*2, 280*2);
	line(377*2, 60*2, 377*2, 280*2);
	//绘制开始游戏图标
	fillrectangle(826, 177, 985, 232);
	settextstyle(35,0 ,NULL);
	outtextxy(840, 190, "GameStart");
	//绘制暂停游戏图标
	fillrectangle(826, 267, 985, 312);
	settextstyle(35, 0, NULL);
	outtextxy(865, 273, "Pause");
	//绘制继续游戏图标
	fillrectangle(826, 357, 985, 402);
	settextstyle(35, 0, NULL);
	outtextxy(850, 363, "Continue");
	//绘制结束游戏图标
	fillrectangle(826, 447, 985, 492);
	settextstyle(35, 0, NULL);
	outtextxy(873, 453, "EXIT");
	//绘制保存游戏图标
	fillrectangle(826, 527, 985, 572);
	settextstyle(35, 0, NULL);
	outtextxy(873, 533, "SAVE");
	//预览下一个方块图标的窗口
	rectangle(300, 150, 450, 300);
	//绘制score图标
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
	//地图初始化
	mapInit();
	//game::gameMapDraw();
	//scores初始化
	xScoreInit();
	//分数清零
	winScore = 0;
	game::updateScoreDraw();
	//随机生成第一个方块的位置和形状
	int index = 0;
	index = rand() % 6;
	shapePosX = shapePosXs[index];
	//创建第一个方块的坐标
	Pos px(game::gA.gameTerisorigin[0] + shapePosX, gA.gameTerisorigin[1]);
	nowType = rand() % 5;
	//创建第一个方块
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
	//生成一下下一个方块的形状
	game::gamePreGainNextBlock();
}

void game::continueGameInit() {
	//scores初始化
	xScoreInit();
	//初始化形状指针
	nowShape = new TShape();
	nextShape = new TShape();
	readMap();
	readGameStates();
	game_state = game::gameState::gamePlaying;
}

void game::gamePreGainNextBlock() {
	//随机生成第一个方块的位置和形状
	int index = 0;
	index = rand() % 6;
	shapePosX = shapePosXs[index];
	//创建第一个方块的坐标
	Pos px(shapePosX + gA.gameTerisorigin[0], gA.gameTerisorigin[1]);
	nextType = rand() % 5;
	//创建第一个方块
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
	//绘制下一个方块提示
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
		//游戏开始前先查看本地有没有存档，如果有提示玩家是否接着上一盘继续！
		if (!game::checkLocalFile()) {
			game::drawTellContinue();
			FlushBatchDraw();
			while (1) {
				msg = GetMouseMsg();
				//判断是否继续上一盘游戏
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
		//把游戏的状态设置为playing
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
		//绘制游戏结束图案提示玩家
		game::drawGameOver();

		//等待下一步操作
		if (MouseHit()) {
			mouseAction();
		}
		break;
	}
	case game::gameState::gamePause: {
		//等待下一步操作
		mouseAction();
		break;
	}
	case game::gameState::gameSave: {
		saveMap();
		saveGameState();
		//等待下一步操作
		mouseAction();
	}
	default:
		break;
	}
}

void game::mouseAction() {
	msg = GetMouseMsg();
	//判断是否点击开始游戏按钮
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 117 && msg.y <= 232 && msg.uMsg == WM_LBUTTONDOWN) {
		game_state = game::gameState::gameStartNewGame;
	}
	//判断是否点击结束游戏按钮
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 447 && msg.y <= 492 && msg.uMsg == WM_LBUTTONDOWN) {
		//退出窗口
		closegraph();
	}
	//判断是否点击暂停
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 267 && msg.y <= 312 && msg.uMsg == WM_LBUTTONDOWN) {
		game_state = game::gameState::gamePause;
		Sleep(30);
	}
	//判断是否点击继续
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 357 && msg.y <= 402 && msg.uMsg == WM_LBUTTONDOWN) {
		game_state = game::gameState::gamePlaying;
		Sleep(30);
	}
	//判断是否点击保存游戏按钮
	if (msg.x >= 826 && msg.x <= 985 && msg.y >= 527 && msg.y <= 572 && msg.uMsg == WM_LBUTTONDOWN) {
		//退出窗口
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

//游戏运行
void game::gameplay() {
	game::gameplaying();
	
}

void game::gameplaying() {
	//判断上一帧是否有方块要快速下落
	if (isQuickDown || isLocated) {
		//要生成下一个方块了
		game::gamePreGainNextBlock();
		isQuickDown = 0;
		isLocated = 0;
	}
	//绘制地图
	game::gameMapDraw();

	//检测游戏是否结束
	if (game::checkGameOver()) {
		game::game_state = game::gameState::gameOver;
		return;
	}

	//此处应该在绘制方块之前判断防止已经游戏结束了还绘制的下一个方块

	//绘制方块
	for (int i = 0; i < 4; i++) {
		game::drawCraft(nowShape->blockPos[i]);
	}

	//绘制预览形状
	drawPreShape();

	//检测是否有底部碰撞，如果有就没必要移动旋转了
	if (game::craftCheckAndMoveDown()) {
		return;
	}

	//检测是否有快速下降的信号,如果有就没必要移动旋转了
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		quickDown();
		//睡眠一下放置重复按键
		Sleep(100);
		return;
	}

	//检测是否有移动的信号
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (!twoSideCrash()) {
			nowShape->craftLeftMove();
		}
		//睡眠一下放置重复按键
		Sleep(100);
		
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (!twoSideCrash()) {
			nowShape->craftRightMove();
		}
		//睡眠一下放置重复按键
		Sleep(100);
	}
	//检测是否有旋转的信号
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		nowShape->spin(spinShape[nowShape->nowshape]);
		nowShape->nowshape++;
		if (nowShape->nowshape == 4) nowShape->nowshape = 0;
		//睡眠一下放置重复按键
		Sleep(100);
	}



	//判断消除行
	RemoveCol();
}

//绘制方块
void game::drawCraft(Pos p) {
	//游戏地图以外的方块不能画
	if (p.y < 120)return;
	setfillcolor(BLACK);
	solidrectangle(p.x, p.y, p.x + blockWidth, p.y + blockWidth);
}

void game::drawPreCraft(Pos p) {
	//游戏地图以外的方块不能画
	if (p.y < 120)return;
	rectangle(p.x, p.y, p.x + blockWidth, p.y + blockWidth);
}

//绘制地图
void game::gameMapDraw() {
	setbkcolor(WHITE);
	//先清屏在绘画
	clearrectangle(528, 120, 752, 565);
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != 0) {
				//创建该点的坐标
				Pos p(gA.gameTerisorigin[0] + j * blockWidth, gA.gameTerisorigin[1] + i* blockWidth);
				game::drawCraft(p);
			}
		}
	}
}

//绘制提醒是否继续游戏界面
void game::drawTellContinue() {
	setbkcolor(WHITE);
	//先清屏在绘画
	clearrectangle(528, 120, 752, 565);
	//绘制文字
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
	//超出游戏范围，默认为有方块
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
	//先判断是否触碰到底部边界
	for (int i = 0; i < 4; i++) {
		if (nowShape->blockPos[i].y == gA.terisBottom) {
			//碰撞到底部边界
			isLocated = 1;
			//锁住方块,update map
			for (int i = 0; i < 4; i++) {
				Pos2Map(nowShape->blockPos[i]);
			}
			//切换当前方块
			nowShape = nextShape;
			return true;
		}
		//在判断方块周围是否有方块，两边有方块不算碰撞可以下降
		//生成该点的四周Pos
		Pos pDown(nowShape->blockPos[i].x, nowShape->blockPos[i].y + blockWidth);
		if (hasCraft(pDown)) {
			isLocated = 1;
			//锁住方块,update map
			for (int i = 0; i < 4; i++) {
				Pos2Map(nowShape->blockPos[i]);
			}
			//切换当前方块
			nowShape = nextShape;
			return true;
		}
	}
	nowShape->craftDown();
	Sleep(25);
	return false;
}

bool game::simCraftCheckAndMoveDown(TerisShape *simShape) {
	//先判断是否触碰到底部边界
	for (int i = 0; i < 4; i++) {
		if (simShape->blockPos[i].y == gA.terisBottom) {
			//碰撞到底部边界
			return true;
		}
		//在判断方块周围是否有方块，两边有方块不算碰撞可以下降
		//生成该点的四周Pos
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
	//判断是否需要消除行
	bool result = 1;
	for (int i = 0; i < canRemove.size(); i++) {
		if (canRemove[i] == 1) result = 0;
	}
	if (result == 1) return;

	//执行消行，新建一个map，如果当前列为0，放入map，否则跳过，在剩余行补0；
	//从下往上填补
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

	//加分，消除一行加10分。
	for (int i = 0; i < canRemove.size(); i++) {
		if (canRemove[i] == 1)game::winScore += 10;
	}

	//更新分数显示
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
	//画之前先清空上一个图标
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
	//先清屏在绘画
	clearrectangle(530, 120, 750, 560);

	//绘制文字
	settextstyle(80, 0, NULL);
	outtextxy(540, 220, "GAME");
	outtextxy(540, 360, "OVER");

}

Pos* game::preCraftPos() {
	//算法思想：模拟法
	//模拟当前方块在未来碰撞时的位置
	//先根据根据当前形状创建用来模拟对象
	switch (nowShape->type) {
	case ti: {
		TShape temp(nowShape->blockPos[0],
			nowShape->blockPos[1],
			nowShape->blockPos[2],
			nowShape->blockPos[3]);
		while (!simCraftCheckAndMoveDown(&temp)) {
			continue;
		}

		//模拟结束此时的模拟方块就是预览后的方块,返回此时的四个方块的位置用于预览和快速下降
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

		//模拟结束此时的模拟方块就是预览后的方块,返回此时的四个方块的位置用于预览和快速下降
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

		//模拟结束此时的模拟方块就是预览后的方块,返回此时的四个方块的位置用于预览和快速下降
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

		//模拟结束此时的模拟方块就是预览后的方块,返回此时的四个方块的位置用于预览和快速下降
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

	//模拟结束此时的模拟方块就是预览后的方块,返回此时的四个方块的位置用于预览和快速下降
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
	//更新地图
	for (int i = 0; i < 4; i++) {
		Pos2Map(prePos[i]);
	}
	//更新方块
	nowShape = nextShape;
}

void game::saveMap() {
	MapFile mapFile;
	mapFile.deleteContent("map.dat");
	mapFile.writeInFile("map.dat", game::map);
}

void game::saveGameState() {
	//下面列举保证游戏正常运行的几个需要储存的状态
	//gameState
	//nowShape
	//nextShape
	//nowType
	//nextType
	//isLocated
	//isQuicked
	//winScore

	//按顺序写入
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
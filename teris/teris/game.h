#pragma once
#include"seviceHeadFileSet.h"


namespace game {

	//游戏运行状态
	namespace gameState {
		const int gameMenu = 0;
		const int gameStartLoadMap = 1;
		const int gameStartNewGame = 2;
		const int gamePlaying = 3;
		const int gamePause = 4;
		const int gameOver = 5;
		const int gameExit = 6;
		const int gameSave = 7;
		const int gameHelp = 8;
		const int gameStartOldGame = 9;
	};

	extern GameAttribute gA;

	//俄罗斯方块地图的地方,注意不是实际长宽，而是以方块数的形式
	extern int map_width;
	extern int map_height;
	extern vector<vector<int>> map;

	//计时器
	extern DWORD timePre;
	extern DWORD timeNow;

	//gameState
	extern int game_state;

	//鼠标信息
	extern MOUSEMSG msg;

	//方块信息
	extern TerisShape* nowShape;
	extern TerisShape* nextShape;

	//方块核心位置(以左上角为核心位置)
	extern int shapePosX;
	extern vector<int> shapePosXs;

	//方块类型
	extern int nowType;
	extern int nextType;

	//方块是否固定
	extern bool isLocated;
	//是否快速下降
	extern bool isQuickDown;

	//游戏行数消除积分
	extern int winScore;

	//形状信息
	extern int spinShape[4];

	//游戏初始页面
	void gameMenuDraw();

	//游戏初始化
	void  gameInit();

	//根据state选择游戏状态
	void gameStateSelect();

	//鼠标动作
	void mouseAction();

	//游戏地图初始化
	void mapInit();

	//x_score初始化
	void xScoreInit();

	//游戏进行
	void gameplay();

	//游戏运行
	void gameplaying();

	//预生成下一个方块的形状；
	void gamePreGainNextBlock();

	//绘制方块
	void drawCraft(Pos p);

	//绘制预览方块
	void drawPreCraft(Pos p);

	//绘制地图
	void gameMapDraw();

	//碰撞检测
	bool craftCheckAndMoveDown();

	//碰撞检测模拟 
	bool simCraftCheckAndMoveDown(TerisShape* simShape);

	//将Pos对应的Map设置为1
	void Pos2Map(Pos p);

	//判断某Pos上是否有方块
	bool hasCraft(Pos p);

	//判断左右有没有方块
	bool twoSideCrash();

	//判断能否消行并执行消行,顺便加分
	void RemoveCol();

	//检测游戏是否结束
	bool checkGameOver();

	//绘制下一个形状
	void drawNextBlock();

	//更新显示分数模块
	void updateScoreDraw();

	//绘制结束画面
	void drawGameOver();

	//计算当前方块底部预览位置算法
	Pos* preCraftPos();

	//绘制预览形状
	void drawPreShape();

	//实现快速下降
	void quickDown();

	//把当前游戏地图储存进文件
	void saveMap();

	//把当前游戏的状态储存进文件
	void saveGameState();

	//读取游戏地图文件
	void readMap();

	//读取游戏状态文件
	void readGameStates();

	//绘制提醒继续游戏界面
	void drawTellContinue();

	//检测是否有本地文件
	bool checkLocalFile();

	//继续游戏初始化
	void continueGameInit();
}

class gameWindow
{
private: 
	int wedith;
	int length;
public:
	gameWindow() {};
	gameWindow(int w, int l) : wedith(w), length(l){}
	//建立窗口
	void gameWindowInit();
};




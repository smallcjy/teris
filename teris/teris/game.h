#pragma once
#include"seviceHeadFileSet.h"


namespace game {

	//��Ϸ����״̬
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

	//����˹�����ͼ�ĵط�,ע�ⲻ��ʵ�ʳ��������Է���������ʽ
	extern int map_width;
	extern int map_height;
	extern vector<vector<int>> map;

	//��ʱ��
	extern DWORD timePre;
	extern DWORD timeNow;

	//gameState
	extern int game_state;

	//�����Ϣ
	extern MOUSEMSG msg;

	//������Ϣ
	extern TerisShape* nowShape;
	extern TerisShape* nextShape;

	//�������λ��(�����Ͻ�Ϊ����λ��)
	extern int shapePosX;
	extern vector<int> shapePosXs;

	//��������
	extern int nowType;
	extern int nextType;

	//�����Ƿ�̶�
	extern bool isLocated;
	//�Ƿ�����½�
	extern bool isQuickDown;

	//��Ϸ������������
	extern int winScore;

	//��״��Ϣ
	extern int spinShape[4];

	//��Ϸ��ʼҳ��
	void gameMenuDraw();

	//��Ϸ��ʼ��
	void  gameInit();

	//����stateѡ����Ϸ״̬
	void gameStateSelect();

	//��궯��
	void mouseAction();

	//��Ϸ��ͼ��ʼ��
	void mapInit();

	//x_score��ʼ��
	void xScoreInit();

	//��Ϸ����
	void gameplay();

	//��Ϸ����
	void gameplaying();

	//Ԥ������һ���������״��
	void gamePreGainNextBlock();

	//���Ʒ���
	void drawCraft(Pos p);

	//����Ԥ������
	void drawPreCraft(Pos p);

	//���Ƶ�ͼ
	void gameMapDraw();

	//��ײ���
	bool craftCheckAndMoveDown();

	//��ײ���ģ�� 
	bool simCraftCheckAndMoveDown(TerisShape* simShape);

	//��Pos��Ӧ��Map����Ϊ1
	void Pos2Map(Pos p);

	//�ж�ĳPos���Ƿ��з���
	bool hasCraft(Pos p);

	//�ж�������û�з���
	bool twoSideCrash();

	//�ж��ܷ����в�ִ������,˳��ӷ�
	void RemoveCol();

	//�����Ϸ�Ƿ����
	bool checkGameOver();

	//������һ����״
	void drawNextBlock();

	//������ʾ����ģ��
	void updateScoreDraw();

	//���ƽ�������
	void drawGameOver();

	//���㵱ǰ����ײ�Ԥ��λ���㷨
	Pos* preCraftPos();

	//����Ԥ����״
	void drawPreShape();

	//ʵ�ֿ����½�
	void quickDown();

	//�ѵ�ǰ��Ϸ��ͼ������ļ�
	void saveMap();

	//�ѵ�ǰ��Ϸ��״̬������ļ�
	void saveGameState();

	//��ȡ��Ϸ��ͼ�ļ�
	void readMap();

	//��ȡ��Ϸ״̬�ļ�
	void readGameStates();

	//�������Ѽ�����Ϸ����
	void drawTellContinue();

	//����Ƿ��б����ļ�
	bool checkLocalFile();

	//������Ϸ��ʼ��
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
	//��������
	void gameWindowInit();
};




#pragma once
#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include"Shape.h"

const int mapSize = 800;
const int charSize = 100;

using std::fstream;
using std::string;
using std::vector;


class MapFile {
private:
	fstream file;
public:
	MapFile() {}

	//�鿴�ļ���С
	bool isEqual(string path) {
		file.open(path, std::ios::binary | std::ios::out | std::ios::in);
		if (!file.is_open()) {
			std::cout << "can not open file!";
			exit(0);
		}

		// ��λ���ļ�ĩβ
		file.seekg(0, std::ios::end);

		// ��ȡ�ļ�ָ��λ�ã����ļ���С
		int fileSize = file.tellg();
		file.close();
		if (fileSize == 0) return true;
		else return false;


	}

	//��ȡ�ļ�
	void readFromFile(string path, vector<vector<int>>& map) {
		file.open(path, std::ios::binary | std::ios::out | std::ios::in);
		if (!file.is_open()) {
			std::cout << "can not open file!";
			exit(0);
		}
		for (int i = 0; i < 20; i++) {
			vector<int> innerVector(10);
			file.read(reinterpret_cast<char*>(innerVector.data()), 10 * sizeof(int));
			map.push_back(innerVector);
		}
		file.close();
	}

	//д���ļ�
	void writeInFile(string path, vector<vector<int>> map) {
		file.open(path, std::ios::binary | std::ios::out | std::ios::in);
		if (!file.is_open()) {
			std::cout << "can not open file!";
			exit(0);
		}
		for (int i = 0; i < 20; i++) {
			vector<int> innervector = map[i];
			file.write(reinterpret_cast<char*>(innervector.data()), 10 * sizeof(int));
		}
		file.close();
	}

	//����ļ�����
	void deleteContent(string path) {
		file.open(path, std::ios::out | std::ios::trunc);
		file.close();
	}
};


class GameStateFile {
private:
	fstream file;
public:
	GameStateFile(){}

	//�鿴�ļ���С
	bool isEqual(string path) {
		file.open(path, std::ios::binary);
		if (!file.is_open()) {
			return true;
		}

		// ��λ���ļ�ĩβ
		file.seekg(0, std::ios::end);

		// ��ȡ�ļ�ָ��λ�ã����ļ���С
		int fileSize = file.tellg();
		file.close();
		if (fileSize == 0) return true;
		else return false;


	}
	
	//��ȡ�ļ�
	void readFromFile(string path, int &gameState, TerisShape* nowShape, TerisShape* nextShape, int &nowType, int &nextType, int &isLocated, int &isQuicked, int &winScore) {
		file.open(path, std::ios::binary | std::ios::out | std::ios::in);
		if (!file.is_open()) {
			std::cout << "can not open file!";
			exit(0);
		}
		file.read(reinterpret_cast<char*>(&gameState), sizeof(int));
		file.read(reinterpret_cast<char*>(&(*nowShape)), sizeof(TerisShape));
		file.read(reinterpret_cast<char*>(&(*nextShape)), sizeof(TerisShape));
		file.read(reinterpret_cast<char*>(&nowType), sizeof(int));
		file.read(reinterpret_cast<char*>(&nextType), sizeof(int));
		file.read(reinterpret_cast<char*>(&isLocated), sizeof(int));
		file.read(reinterpret_cast<char*>(&isQuicked), sizeof(int));
		file.read(reinterpret_cast<char*>(&winScore), sizeof(int));

		file.close();
	}

	//д���ļ�
	void writeInFile(string path, int gameState, TerisShape* nowShape, TerisShape* nextShape, int nowType, int nextType, int isLocated, int isQuicked, int winScore) {
		file.open(path, std::ios::binary | std::ios::out | std::ios::in);
		if (!file.is_open()) {
			std::cout << "can not open file!";
			exit(0);
		}
		file.write(reinterpret_cast<char*>(&gameState), sizeof(int));
		file.write(reinterpret_cast<char*>(&(*nowShape)), sizeof(TerisShape));
		file.write(reinterpret_cast<char*>(&(*nextShape)), sizeof(TerisShape));
		file.write(reinterpret_cast<char*>(&nowType), sizeof(int));
		file.write(reinterpret_cast<char*>(&nextType), sizeof(int));
		file.write(reinterpret_cast<char*>(&isLocated), sizeof(int));
		file.write(reinterpret_cast<char*>(&isQuicked), sizeof(int));
		file.write(reinterpret_cast<char*>(&winScore), sizeof(int));
		file.close();
	}
	//����ļ�����
	void deleteContent(string path) {
		file.open(path, std::ios::out | std::ios::trunc);
		file.close();
	}
};





#ifndef HEAD_H
#define HEAD_H

#include <Windows.h>
#include <conio.h>
#include <graphics.h>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//����ṹ��
struct BlockPos {
  int num;
  int x;
  int y;
};

//�ƶ�ָ��
enum class MoveDir { UP = 1, DOWN, LEFT, RIGHT };

//��������
void DrowScore(int _score, int _left);

//���ƻ�ӭ����
void DrowWelcome();

//��ʼ����Ϸ����
void DrowInit();

//���Ʒ���ͼ��
void CreateBlockImage(IMAGE* img, LPCTSTR num, COLORREF imgColor, int fontSize);

//���ط���
void LoadBlocks();

//��������
void DrowMap();

//�����������
bool CreateBlock();

//�ж�x�Ƿ���2��n�η�
bool if2n(int x);

//�����ƶ�
void BlockMove(MoveDir md);

//���̲���
MoveDir KeyInput();

//�ж���Ϸ״̬
bool IfOver();

//��ȡ�����ļ�
int BestScoreR();

//д������ļ�
void BestScoreW();

//��⵱ǰ�����Ƿ�Ϊ��߷���
bool IfBest();

//��Ϸ��ʼ��
void GameInit();

//��ʼ��Ϸ
void GameStart();

//���ƽ���ҳ��
void DrowEnd();

#endif  // !HEAD_H

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

//方块结构体
struct BlockPos {
  int num;
  int x;
  int y;
};

//移动指令
enum class MoveDir { UP = 1, DOWN, LEFT, RIGHT };

//分数绘制
void DrowScore(int _score, int _left);

//绘制欢迎界面
void DrowWelcome();

//初始化游戏界面
void DrowInit();

//绘制方块图像
void CreateBlockImage(IMAGE* img, LPCTSTR num, COLORREF imgColor, int fontSize);

//加载方块
void LoadBlocks();

//绘制网格
void DrowMap();

//随机创建方块
bool CreateBlock();

//判断x是否是2的n次方
bool if2n(int x);

//方块移动
void BlockMove(MoveDir md);

//键盘操作
MoveDir KeyInput();

//判断游戏状态
bool IfOver();

//读取分数文件
int BestScoreR();

//写入分数文件
void BestScoreW();

//检测当前分数是否为最高分数
bool IfBest();

//游戏初始化
void GameInit();

//开始游戏
void GameStart();

//绘制结束页面
void DrowEnd();

#endif  // !HEAD_H

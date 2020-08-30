/*
Project Name：2048_game
Development Tools：Visual Studio 2019
Project Type：Windows Consoal Application
Author：rogepi
Date：2020-06-03
*/

#include "head.h"

int const ROW = 4;  //行
int const COL = 4;  //列

BlockPos blocks[ROW][COL];  //用二维数组存储方块

std::map<int, IMAGE> image;  //用关联容器存储方块图像

int score = 0;            //游戏分数
int best = 0;             //最高分数
std::vector<int> scores;  //用顺序容器存储分数

//绘制欢迎界面
void DrowWelcome() {
  initgraph(540, 640);
  setbkcolor(RGB(249, 248, 240));
  HWND hWnd = GetHWnd();
  SetWindowText(hWnd, L"2048 By@rogepi");
  cleardevice();

  settextstyle(150, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(RGB(209, 85, 60));
  outtextxy(100, 175, _T("2"));
  settextcolor(RGB(96, 165, 90));
  outtextxy(190, 175, _T("0"));
  settextcolor(RGB(237, 191, 57));
  outtextxy(280, 175, _T("4"));
  settextcolor(RGB(91, 132, 238));
  outtextxy(370, 175, _T("8"));

  setbkmode(TRANSPARENT);
  settextstyle(50, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(RGB(128, 128, 128));
  outtextxy(95, 510, _T("Press enter to start"));

  getchar();
  GameStart();
}

//分数的绘制
void DrowScore(int _score, int _left) {
  if (_left == 270)
    setfillcolor(RGB(96, 165, 90));
  else
    setfillcolor(RGB(237, 191, 57));

  solidroundrect(_left, 60, _left + 100, 100, 1, 1);

  RECT r = {_left, 50, _left + 100, 100};
  TCHAR sval[16];
  wsprintf(sval, TEXT("%i"), _score);
  drawtext(sval, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//初始化游戏界面
void DrowInit() {
  //背景初始化
  cleardevice();

  //绘制2048
  settextstyle(80, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(RGB(209, 85, 60));
  outtextxy(40, 30, _T("2"));
  settextcolor(RGB(96, 165, 90));
  outtextxy(80, 35, _T("0"));
  settextcolor(RGB(237, 191, 57));
  outtextxy(120, 30, _T("4"));
  settextcolor(RGB(91, 132, 238));
  outtextxy(160, 25, _T("8"));

  //绘制score

  setfillcolor(RGB(96, 165, 90));
  solidroundrect(270, 30, 370, 100, 1, 1);
  setbkmode(TRANSPARENT);
  settextstyle(30, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(WHITE);
  outtextxy(290, 32, _T("score"));
  DrowScore(score, 270);

  //绘制best
  setfillcolor(RGB(237, 191, 57));
  solidroundrect(390, 30, 490, 100, 1, 1);
  setbkmode(TRANSPARENT);
  settextstyle(30, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(WHITE);
  outtextxy(415, 32, _T("best"));

  DrowScore(best, 390);

  //绘制网格背景
  setfillcolor(RGB(187, 173, 160));
  solidroundrect(20, 120, 520, 620, 1, 1);

  //绘制方块
  for (int i = 40; i <= 420; i += 120) {
    for (int j = 140; j < 520; j += 120) {
      putimage(i, j, &image[0]);
    }
  }
}

//绘制方块图像
void CreateBlockImage(IMAGE* img, LPCTSTR num, COLORREF imgColor,
                      int fontSize) {
  SetWorkingImage(img);
  setbkmode(TRANSPARENT);
  setbkcolor(0x9eaebb);
  settextstyle(fontSize, 0, _T("微软雅黑"), 0, 0, 1000, false, false, false,
               ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
               ANTIALIASED_QUALITY, DEFAULT_PITCH);
  settextcolor(WHITE);
  setfillcolor(imgColor);

  cleardevice();

  solidroundrect(0, 0, 101, 101, 1, 1);

  RECT r = {0, 0, 100, 100};
  drawtext(num, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//加载方块
void LoadBlocks() {
  IMAGE temp(101, 101);

  CreateBlockImage(&temp, _T(""), RGB(205, 193, 180), 72);
  image[0] = temp;
  CreateBlockImage(&temp, _T("2"), RGB(91, 132, 238), 72);
  image[2] = temp;
  CreateBlockImage(&temp, _T("4"), RGB(209, 85, 60), 72);
  image[4] = temp;
  CreateBlockImage(&temp, _T("8"), RGB(237, 191, 57), 72);
  image[8] = temp;
  CreateBlockImage(&temp, _T("16"), RGB(96, 165, 90), 72);
  image[16] = temp;
  CreateBlockImage(&temp, _T("32"), RGB(232, 78, 155), 72);
  image[32] = temp;
  CreateBlockImage(&temp, _T("64"), RGB(39, 162, 139), 72);
  image[64] = temp;
  CreateBlockImage(&temp, _T("128"), RGB(246, 124, 95), 56);
  image[128] = temp;
  CreateBlockImage(&temp, _T("256"), RGB(43, 91, 173), 56);
  image[256] = temp;
  CreateBlockImage(&temp, _T("512"), RGB(237, 200, 80), 56);
  image[512] = temp;
  CreateBlockImage(&temp, _T("1024"), RGB(183, 148, 115), 40);
  image[1024] = temp;
  CreateBlockImage(&temp, _T("2048"), RGB(151, 111, 67), 40);
  image[2048] = temp;
  SetWorkingImage(NULL);
}

//绘制网格
void DrowMap() {
  for (int i = 40; i <= 420; i += 120) {
    for (int j = 140; j < 520; j += 120) {
      putimage(i, j, &image[blocks[(i - 40) / 120][(j - 140) / 120].num]);
    }
  }
}

//随机创建方块
bool CreateBlock() {
  int _row = 0;
  int _col = 0;
  int times = 0;
  int times_max = ROW * COL;
  int block_c = rand() % 8;

  do {
    _row = rand() % ROW;
    _col = rand() % COL;
    times++;
  } while (blocks[_row][_col].num != 0 && times <= times_max);

  //当方块全满了无法生生成新方块
  if (times >= times_max) {
    return false;
  } else {
    if (block_c == 0) {
      blocks[_row][_col].num = 4;
    } else {
      blocks[_row][_col].num = 2;
    }
  }
  DrowMap();
  return true;
}

//判断x是否是2的n次方
bool if2n(int x) {
  bool flag = false;
  int n;
  for (n = 1; n <= 11; n++) {
    if (x == pow(2, n)) {
      flag = true;
    }
  }
  return flag;
}

//方块移动
void BlockMove(MoveDir md) {
  switch (md) {
    case MoveDir::LEFT:
      for (int j = 0; j <= 3; j++)
        for (int i = 0; i < 3; i++) {
          int count = 0;
          for (int k = 0; k < 4; k++) {
            if (blocks[k][j].num != 0) {
              blocks[count][j] = blocks[k][j];
              if (k != count) blocks[k][j].num = 0;
              count++;
            }
          }

          if (if2n(blocks[i][j].num + blocks[i + 1][j].num) == 1) {
            if (blocks[i][j].num == blocks[i + 1][j].num) {
              blocks[i][j].num = blocks[i][j].num + blocks[i + 1][j].num;
              score += blocks[i][j].num;
            }
            blocks[i + 1][j].num = 0;
          }
        }
      DrowMap();
      break;

    case MoveDir::RIGHT:
      for (int j = 0; j <= 3; j++)
        for (int i = 3; i > 0; i--) {
          int count = 3;
          for (int k = 3; k >= 0; k--) {
            if (blocks[k][j].num != 0) {
              blocks[count][j] = blocks[k][j];
              if (k != count) blocks[k][j].num = 0;
              count--;
            }
          }

          if (if2n(blocks[i][j].num + blocks[i - 1][j].num) == 1) {
            if (blocks[i][j].num == blocks[i - 1][j].num) {
              blocks[i][j].num = blocks[i][j].num + blocks[i - 1][j].num;
              score += blocks[i][j].num;
            }
            blocks[i - 1][j].num = 0;
          }
        }
      DrowMap();
      break;

    case MoveDir::UP:
      for (int i = 0; i <= 3; i++)
        for (int j = 0; j < 3; j++) {
          int count = 0;
          for (int k = 0; k < 4; ++k) {
            if (blocks[i][k].num != 0) {
              blocks[i][count] = blocks[i][k];
              if (k != count) blocks[i][k].num = 0;
              count++;
            }
          }
          if (if2n(blocks[i][j].num + blocks[i][j + 1].num) == 1) {
            if (blocks[i][j].num == blocks[i][j + 1].num) {
              blocks[i][j].num = blocks[i][j].num + blocks[i][j + 1].num;
              score += blocks[i][j].num;
            }
            blocks[i][j + 1].num = 0;
          }
        }
      DrowMap();
      break;

    case MoveDir::DOWN:
      for (int i = 0; i <= 3; i++)
        for (int j = 3; j > 0; j--) {
          int count = 3;
          for (int k = 3; k >= 0; --k) {
            if (blocks[i][k].num != 0) {
              blocks[i][count] = blocks[i][k];
              if (k != count) blocks[i][k].num = 0;
              count--;
            }
          }
          if (if2n(blocks[i][j].num + blocks[i][j - 1].num) == 1) {
            if (blocks[i][j].num == blocks[i][j - 1].num) {
              blocks[i][j].num = blocks[i][j].num + blocks[i][j - 1].num;
              score += blocks[i][j].num;
            }
            blocks[i][j - 1].num = 0;
          }
        }
      DrowMap();
      break;

    default:
      break;
  }
}

//键盘操作
MoveDir KeyInput() {
  while (true) {
    if ((GetAsyncKeyState(VK_UP) & 0x8000) ||
        (GetAsyncKeyState('W') & 0x8000)) {
      return MoveDir::UP;
      break;
    } else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
               (GetAsyncKeyState('S') & 0x8000)) {
      return MoveDir::DOWN;
      break;
    } else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
               (GetAsyncKeyState('A') & 0x8000)) {
      return MoveDir::LEFT;
      break;
    } else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
               (GetAsyncKeyState('D') & 0x8000)) {
      return MoveDir::RIGHT;
      break;
    }
  }
}

//判断游戏状态
bool IfOver() {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (blocks[i][j].num == 2048) {
        return 0;
        break;
      }
    }
  }

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL - 1; j++) {
      if (!blocks[i][j].num || (blocks[i][j].num == blocks[i][j + 1].num)) {
        return 0;
        break;
      }
    }
  }

  for (int j = 0; j < COL; j++) {
    for (int i = 0; i < ROW; i++) {
      if (!blocks[i][j].num || (blocks[i][j].num == blocks[i + 1][j].num)) {
        return 0;
        break;
      }
    }
  }

  return 1;
}

//读取分数文件
int BestScoreR() {
  std::ifstream file("score.bin");
  if (!file.is_open()) {
    file.close();
  } else {
    int n = 0;
    while (!file.eof()) {
      file >> n;
      scores.push_back(n);
    }
    scores.pop_back();
  }
  int max = 0;
  for (auto& n : scores) {
    max = max > n ? max : n;
  }
  return max;
}

//写入分数文件
void BestScoreW() {
  std::ofstream file("score.bin", std::ios::app);
  scores.push_back(score);
  if (file.is_open()) {
    file << score << std::endl;
    file.close();
  }
}

//检测当前分数是否为最高分数
bool IfBest() {
  if (score > best) {
    DrowScore(score, 270);
    DrowScore(score, 390);
    return 1;
  } else {
    DrowScore(score, 270);
  }
  return 0;
}

//游戏初始化
void GameInit() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      blocks[i][j].num = 0;
    }
  }
  score = 0;
  best = BestScoreR();
}

//开始游戏
void GameStart() {
  GameInit();

  srand(unsigned(time(NULL)));

  LoadBlocks();
  DrowInit();
  CreateBlock();
  CreateBlock();

  while (true) {
    BlockMove(KeyInput());
    CreateBlock();
    IfBest();

    if (IfOver()) {
      Sleep(1000);
      BestScoreW();
      DrowEnd();
    }

    Sleep(300);
  }
}

//绘制结束页面
void DrowEnd() {
  cleardevice();
  setbkmode(TRANSPARENT);
  settextcolor(RGB(128, 128, 128));
  settextstyle(50, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  outtextxy(40, 150, _T("game over! your score is"));

  RECT r = {0, 250, 540, 400};
  TCHAR scoreval[16];
  wsprintf(scoreval, TEXT("%i"), score);
  settextstyle(150, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(RGB(209, 85, 60));
  drawtext(scoreval, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

  settextstyle(50, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);

  for (int i = 3; i > 0; i--) {
    setfillcolor(RGB(249, 248, 240));
    solidroundrect(110, 500, 420, 600, 1, 1);
    setfillcolor(RGB(128, 128, 128));
    solidroundrect(300 - i * 20, 550, 300 - i * 20 + 10, 560, 1, 1);
    Sleep(1000);
  }

  cleardevice();

  std::sort(scores.begin(), scores.end(), std::greater<int>());
  std::vector<int>::iterator iter = std::unique(scores.begin(), scores.end());
  scores.erase(iter, scores.end());
  if (scores.size() == 1) {
    scores.push_back(0);
    scores.push_back(0);
  } else if (scores.size() == 2) {
    scores.push_back(0);
  } else {
    std::sort(scores.begin(), scores.end(), std::greater<int>());
  }

  settextcolor(RGB(209, 85, 60));
  settextstyle(100, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  outtextxy(75, 50, _T("score rank"));
  settextstyle(80, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  TCHAR nval[5];
  TCHAR sval[20];
  for (int j = 0; j < 3; j++) {
    if (j == 0) settextcolor(RGB(96, 165, 90));
    if (j == 1) settextcolor(RGB(237, 191, 57));
    if (j == 2) settextcolor(RGB(91, 132, 238));

    wsprintf(nval, TEXT("%i"), j + 1);
    wsprintf(sval, TEXT("%i"), scores[j]);
    outtextxy(130, 180 + j * 80, nval);
    outtextxy(170, 180 + j * 80, _T("."));
    outtextxy(210, 180 + j * 80, sval);
  }
  settextstyle(50, 0, _T("微软雅黑"), 0, 0, 800, 0, 0, 0, 0, 0, 0,
               ANTIALIASED_QUALITY, 0);
  settextcolor(RGB(128, 128, 128));
  outtextxy(75, 510, _T("Press enter to restart"));
  getchar();
  DrowWelcome();
}

//主函数
int main() {
  DrowWelcome();

  return 0;
}

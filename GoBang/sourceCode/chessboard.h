#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <QPaintEvent>
#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <cmath>
#include <stack>
using namespace std;

#define BLACK 1
#define WHITE -1
#define NONE 0
#define SIZE 19

//栈操作不能直接用数组
struct boardStruct
{
   int data[SIZE][SIZE];
};

struct aichessStruct{
    int data[2];
};

class chessboard{
public:
    chessboard();
    void restart();
    int getChess(int x,int y);
    bool getChesses();
    void setChesses(bool b);
    void setChessN(int x, int y);
    void setChess(int x,int y);
    void reverse();
    void drawBoard();
    bool DFS(int x,int y,int count,int id,int dir);
    int winner(int x,int y);
    void AI();
    void calculateScore();

    stack <boardStruct> last;

    std::vector<std::vector<int>> scoreMapVec; // 存储各个点位的评分情况，作为AI下棋依据

    aichessStruct AIChess;

private:
    int board[SIZE][SIZE];
    bool chesses=true;//true下黑棋,false下白棋
};

#endif // CHESSBOARD_H

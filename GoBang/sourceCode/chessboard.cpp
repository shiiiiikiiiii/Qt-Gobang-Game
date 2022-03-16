#include "chessboard.h"

int chessboard::getChess(int x, int y){
    //返回某处的棋子值
    return board[x][y];
}

bool chessboard::getChesses(){
    //返回下一步棋的颜色
    return chesses;
}

void chessboard::setChesses(bool b){
    chesses=b;
}

void chessboard::setChessN(int x, int y){
    //设为无棋子
    board[x][y]=NONE;
}

void chessboard::setChess(int x, int y){
    //如果已经有棋则不能再下棋
    if (getChess(x,y)!=NONE)
        return;
    //按顺序下黑白棋
    else if (chesses)
        board[x][y]=BLACK;
    else
        board[x][y]=WHITE;
    chesses=!chesses;
    //每一步都入栈
    boardStruct tmp;
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++){
            tmp.data[i][j]=board[i][j];
        }
    }
    last.push(tmp);
    //栈最多存五步
    if(last.size()>=10){
        while (last.size()>=5){
                last.pop();
            }
    }
}

void chessboard::reverse(){
    //栈操作悔棋
    boardStruct tmp=last.top();
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++){
            board[i][j]=tmp.data[i][j];
        }
    }
    last.pop();
    //chesses=!chesses;
}

chessboard::chessboard(){
    //构造函数初始化棋盘
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            setChessN(i,j);
        }
    }
}

void chessboard::drawBoard(){
    //控制台打印棋盘
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            cout<<getChess(i,j)<<" ";
        }
        cout<<"\n";
    }
}

void chessboard::restart(){
    //重开,全部棋子初始化
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            setChessN(i,j);
            chesses=true;
        }
    }
    //清空栈
    while (!last.empty()){
            last.pop();
        }
}

bool chessboard::DFS(int x,int y,int count,int id,int dir){
    //方向向量:上,右上,右,右下,下,左下,左,左上
    int dirVector[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

    //DFS
    if(count>=5) return true;//退出条件
    else
        //棋子同种则继续递归
        if(getChess(x,y)==id)
            return DFS(x+dirVector[dir][0],y+dirVector[dir][1],count+1,id,dir);
        else return false;
}

int chessboard::winner(int x,int y){
    //往八个方向DFS
    for(int i=0;i<8;i++){
        if( DFS(x,y,0,getChess(x,y),i) )
            return getChess(x,y);
    }
    return -2;
}

void chessboard::AI()
{
    // 计算评分
    calculateScore();

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    std::vector<std::pair<int, int>> maxPoints;

    for (int row = 1; row < SIZE; row++)
        for (int col = 1; col < SIZE; col++)
        {
            // 前提是这个坐标是空的
            if (board[row][col] == NONE)
            {
                if (scoreMapVec[row][col] > maxScore)          // 找最大的数和坐标
                {
                    maxPoints.clear();
                    maxScore = scoreMapVec[row][col];
                    maxPoints.push_back(std::make_pair(row, col));
                }
                else if (scoreMapVec[row][col] == maxScore)     // 如果有多个最大的数，都存起来
                    maxPoints.push_back(std::make_pair(row, col));
            }
        }

    // 随机落子，如果有多个点的话
    srand((unsigned)time(0));
    int index = rand() % maxPoints.size();

    std::pair<int, int> pointPair = maxPoints.at(index);
    setChess(pointPair.first, pointPair.second);
    AIChess.data[0]=pointPair.first;
    AIChess.data[1]=pointPair.second;
}

// 最关键的计算评分函数
void chessboard::calculateScore()
{
    // 统计玩家或者电脑连成的子
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0; // AI连成子的个数
    int emptyNum = 0; // 各方向空白位的个数
    int playerChess,AIChess;
    if (chesses){
        playerChess=WHITE;
        AIChess=BLACK;
    }
    else {
        playerChess=BLACK;
        AIChess=WHITE;
    }

    // 清空评分数组
    scoreMapVec.clear();
    for (int i = 0; i < SIZE; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < SIZE; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }

    // 计分（此处是完全遍历，其实可以用bfs或者dfs加减枝降低复杂度，通过调整权重值，调整AI智能程度以及攻守风格）
    for (int row = 0; row < SIZE; row++)
        for (int col = 0; col < SIZE; col++)
        {
            // 空白点就算
            if (row > 0 && col > 0 &&
                board[row][col] == NONE)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子

                            // 对玩家子评分（正反两个方向）
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < SIZE &&
                                    col + i * x > 0 && col + i * x < SIZE &&
                                    board[row + i * y][col + i * x] == playerChess) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < SIZE &&
                                         col + i * x > 0 && col + i * x < SIZE &&
                                         board[row + i * y][col + i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < SIZE &&
                                    col - i * x > 0 && col - i * x < SIZE &&
                                    board[row - i * y][col - i * x] == playerChess) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < SIZE &&
                                         col - i * x > 0 && col - i * x < SIZE &&
                                         board[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (personNum == 1)                      // 杀二
                                scoreMapVec[row][col] += 10;
                            else if (personNum == 2)                 // 杀三
                            {
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 40;
                            }
                            else if (personNum == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 110;
                            }
                            else if (personNum == 4)                 // 杀五
                                scoreMapVec[row][col] += 10100;

                            // 进行一次清空
                            emptyNum = 0;

                            // 对AI子评分
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < SIZE &&
                                    col + i * x > 0 && col + i * x < SIZE &&
                                    board[row + i * y][col + i * x] == AIChess) // AI的子
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < SIZE &&
                                         col + i * x > 0 && col + i * x < SIZE &&
                                         board[row +i * y][col + i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < SIZE &&
                                    col - i * x > 0 && col - i * x < SIZE &&
                                    board[row - i * y][col - i * x] == AIChess) // AI的子
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < SIZE &&
                                         col - i * x > 0 && col - i * x < SIZE &&
                                         board[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (botNum == 0)                      // 普通下子
                                scoreMapVec[row][col] += 5;
                            else if (botNum == 1)                 // 活二
                                scoreMapVec[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)                // 死三
                                    scoreMapVec[row][col] += 25;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 50;  // 活三
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)                // 死四
                                    scoreMapVec[row][col] += 55;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 100; // 活四
                            }
                            else if (botNum >= 4)
                                scoreMapVec[row][col] += 10000;   // 活五

                        }
                    }

            }
        }
}

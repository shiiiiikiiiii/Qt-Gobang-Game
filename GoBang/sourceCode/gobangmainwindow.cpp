#include "gobangmainwindow.h"
#include "ui_gobangmainwindow.h"

GobangMainWindow::GobangMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GobangMainWindow)
{
    ui->setupUi(this);
}

GobangMainWindow::~GobangMainWindow()
{
    delete ui;
}

void GobangMainWindow::paintEvent(QPaintEvent *){
      paint=new QPainter;
      paint->begin(this);//主窗口

      paint->setPen(QPen(Qt::darkGreen,2,Qt::SolidLine));//钢笔工具：颜色，线号，实线
      //画SIZE条横线
      for(int i=0;i<SIZE;i++)
        {
          paint->drawLine(XX,YY+WIDTH*i,XX+WIDTH*(SIZE-1),YY+WIDTH*i);//画线函数：x1,y1,x2,y2:画从(x1,y1)到(x2,y2)的线
        }
      //画SIZE条竖线
      for(int i=0;i<SIZE;i++)
        {
          paint->drawLine(XX+WIDTH*i,YY,XX+WIDTH*i,YY+WIDTH*(SIZE-1));
        }

      for(int i=0;i<SIZE;i++){
          for(int j=0;j<SIZE;j++){
              if (utilBoard.getChess(i,j)==BLACK){
      //做一个黑棋子
      paint->setBrush(QBrush(Qt::black,Qt::SolidPattern));//毛刷：颜色，实图案
      paint->drawEllipse(XX/2+WIDTH*i,YY/2+WIDTH*j,WIDTH/2,WIDTH/2);//画椭圆：中心点X,Y,宽度，高度
              }
      else if (utilBoard.getChess(i,j)==WHITE){
      //做一个白棋子
      paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));
      paint->drawEllipse(XX/2+WIDTH*i,YY/2+WIDTH*j,WIDTH/2,WIDTH/2);
              }
          }
      }
          paint->end();
}

void GobangMainWindow::mousePressEvent(QMouseEvent *e){
    QPoint pos=e->pos();
    if (e->button() == Qt::LeftButton){
        int nx=round(pos.x()/WIDTH); int ny=round(pos.y()/WIDTH);
        //由鼠标位置设置棋子
        utilBoard.setChess(nx,ny);
        this->update();
        //若有一方胜利,弹出窗口
        int win=utilBoard.winner(nx,ny);
        if (win==BLACK){
            QDialog * dlg=new QDialog(this);
            dlg->setWindowTitle(QStringLiteral("blackWIN"));
            dlg->exec();
            utilBoard.restart();
            //清除栈
            while (!utilBoard.last.empty()){
                    utilBoard.last.pop();
                }
        }
        if (win==WHITE){
            QDialog * dlg=new QDialog(this);
            dlg->setWindowTitle(QStringLiteral("whiteWIN"));
            dlg->exec();
            utilBoard.restart();
            while (!utilBoard.last.empty()){
                    utilBoard.last.pop();
                }
        }
    }
}
void GobangMainWindow::on_reverseButton_clicked()
{
    utilBoard.reverse();
    this->update();
    utilBoard.setChesses(!utilBoard.getChesses());
}


void GobangMainWindow::on_restartButton_pressed()
{
    utilBoard.restart();
    this->update();
}


void GobangMainWindow::on_pveButton_pressed()
{
    utilBoard.AI();
    this->update();
    int win=utilBoard.winner(utilBoard.AIChess.data[0],utilBoard.AIChess.data[1]);
    if (win==BLACK){
        QDialog * dlg=new QDialog(this);
        dlg->setWindowTitle(QStringLiteral("blackWIN"));
        dlg->exec();
        utilBoard.restart();
        //清除栈
        while (!utilBoard.last.empty()){
                utilBoard.last.pop();
            }
    }
    if (win==WHITE){
        QDialog * dlg=new QDialog(this);
        dlg->setWindowTitle(QStringLiteral("whiteWIN"));
        dlg->exec();
        utilBoard.restart();
        while (!utilBoard.last.empty()){
                utilBoard.last.pop();
            }
    }
}


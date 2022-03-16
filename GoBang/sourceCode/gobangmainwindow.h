#ifndef GOBANGMAINWINDOW_H
#define GOBANGMAINWINDOW_H

#include "chessboard.h"
#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <cmath>
#include <QPainter>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class GobangMainWindow; }
QT_END_NAMESPACE

static chessboard utilBoard;

class GobangMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GobangMainWindow(QWidget *parent = nullptr);
    ~GobangMainWindow();
    const int WIDTH=40;
    const int XX=20;
    const int YY=20;

private slots:
    void on_reverseButton_clicked();

    void on_restartButton_pressed();

    void on_pveButton_pressed();

private:
    Ui::GobangMainWindow *ui;
    void paintEvent(QPaintEvent *);//绘图函数声明
    void mousePressEvent(QMouseEvent *e);
    QPainter *paint;
};
#endif // GOBANGMAINWINDOW_H

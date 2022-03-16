#include "gobangmainwindow.h"
#include <QApplication>

#include "chessboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GobangMainWindow w;
    w.show();
    return a.exec();
}

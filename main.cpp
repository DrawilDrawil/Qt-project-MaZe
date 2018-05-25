#include <QApplication>
#include "Game.h"

Game * game;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->TMenu();
    game->show();
    return a.exec();
}


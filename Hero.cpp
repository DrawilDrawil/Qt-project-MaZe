#include "Hero.h"
#include "Game.h"
#include <QKeyEvent>
#include <QBrush>
#include <QDebug>
#include <windows.h>
#include <QTimer>

extern Game * game;

Hero::Hero(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/fix/images/sprite.png"));
}

void Hero::keyPressEvent(QKeyEvent *event)
{
    int a,b;

    a = x();
    b = y();

    if((event->key() == Qt::Key_Left) && (a - 20 >= 0) && (game->map[b/20][(a-20)/20] != 1))
    {
        setPos(a - 20 , b);
    }
    else if((event->key() == Qt::Key_Right) && (a + 40 <= 800) && (game->map[b/20][(a+20)/20] != 1))
    {
        setPos(a + 20 , b);
    }
    else if((event->key() == Qt::Key_Up) && (b - 20 >= 0) && (game->map[(b-20)/20][a/20] != 1))
    {
        setPos(a , b - 20);
    }
    else if((event->key() == Qt::Key_Down) && (b + 40 <= 600) && (game->map[(b+20)/20][a/20] != 1))
    {
        setPos(a , b + 20);
    }
    if (x() == game->exit[0] && y() == game->exit[1])
    {
        if ((game->level + 1) == 4)
        {
            game->QMenu();
            return;
        }
        game->level++;
        game->start();
        return;
    }
    else if(event->key() == Qt::Key_Escape)
    {
        game->SaveGame();
        emit game->close();
        return;
    }

}

void Hero::GetXY(int &a, int &b)
{
    a = x();
    b = y();
}

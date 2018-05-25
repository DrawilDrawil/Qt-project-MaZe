#include <QGraphicsTextItem>
#include <QBrush>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QKeyEvent>

#include "Game.h"
#include "Button.h"

Game::Game()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);

    level = 0;


    T[0][0] = "C:/Users/IHEB/Downloads/MP/MaZe/map1.txt";
    T[0][1] = ":/images1/images/ground 1.png";
    T[0][2] = ":/images1/images/wall 1.png";

    T[1][0] = "C:/Users/IHEB/Downloads/MP/MaZe/map2.txt";
    T[1][1] = ":/images2/images/ground 2.png";
    T[1][2] = ":/images2/images/wall 2.png";

    T[2][0] = "C:/Users/IHEB/Downloads/MP/MaZe/map3.txt";
    T[2][1] = ":/images3/images/ground 3.png";
    T[2][2] = ":/images3/images/wall 3.png";

    T[3][0] = "C:/Users/IHEB/Downloads/MP/MaZe/map4.txt";
    T[3][1] = ":/images4/images/ground 4.png";
    T[3][2] = ":/images4/images/wall 4.png";
}

void Game::NewGame()
{
    level = 0;
    start();
}

void Game::start()
{
    scene->clear();

    ReadMap(level);
    DrawMap(level);

    hero = new Hero();
    scene->addItem(hero);
    hero->setFlag(QGraphicsItem::ItemIsFocusable);
    hero->setFocus();
    hero->setPos(gate[0],gate[1]);
}

void Game::Resume()
{
    scene->clear();

    int a,b;

    ReadSaved(a,b);
    ReadMap(level);
    DrawMap(level);

    hero = new Hero();
    scene->addItem(hero);
    hero->setFlag(QGraphicsItem::ItemIsFocusable);
    hero->setFocus();
    hero->setPos(a,b);
}

void Game::TMenu()
{
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/fix/images/Bg.png")));

    QGraphicsTextItem * titletext = new QGraphicsTextItem(QString("MaZe 2000"));
    QFont titleFont("comic sans",50);
    titletext->setFont(titleFont);
    titletext->setDefaultTextColor(Qt::white);
    int txPos = this->width()/2 - titletext->boundingRect().width()/2;
    int tyPos = 25;
    titletext->setPos(txPos,tyPos);
    scene->addItem(titletext);

    Button * new_game = new Button(QString("NEW GAME"));
    int nxPos = this->width()/2 - new_game->boundingRect().width()/2;
    int nyPos = 250;
    new_game->setPos(nxPos,nyPos);
    connect(new_game, SIGNAL(clicked()), this, SLOT(NewGame()));
    scene->addItem(new_game);

    Button * load_game = new Button(QString("LOAD GAME"));
    int lxPos = this->width()/2 - load_game->boundingRect().width()/2;
    int lyPos = 320;
    load_game->setPos(lxPos,lyPos);
    connect(load_game, SIGNAL(clicked()), this, SLOT(Resume()));
    scene->addItem(load_game);

    Button * score = new Button(QString("HIGH SCRORE"));
    int sxPos = this->width()/2 - score->boundingRect().width()/2;
    int syPos = 390;
    score->setPos(sxPos,syPos);
    scene->addItem(score);

    Button * exit_game = new Button(QString("EXIT"));
    int qxPos = this->width()/2 - exit_game->boundingRect().width()/2;
    int qyPos = 460;
    exit_game->setPos(qxPos,qyPos);
    connect(exit_game, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(exit_game);
}

void Game::QMenu()
{
    scene->clear();

    setBackgroundBrush(QBrush(QImage(":/fix/images/Bg.png")));

    QGraphicsTextItem * titletext = new QGraphicsTextItem(QString("YOU BEAT THE GAME"));
    QFont titleFont("comic sans",50);
    titletext->setFont(titleFont);
    titletext->setDefaultTextColor(Qt::white);
    int txPos = this->width()/2 - titletext->boundingRect().width()/2;
    int tyPos = 75;
    titletext->setPos(txPos,tyPos);
    scene->addItem(titletext);

    Button * play_again = new Button(QString("PLAY AGAIN"));
    int nxPos = this->width()/2 - play_again->boundingRect().width()/2;
    int nyPos = 250;
    play_again->setPos(nxPos,nyPos);
    connect(play_again, SIGNAL(clicked()), this, SLOT(NewGame()));
    scene->addItem(play_again);

    Button * main_menu = new Button(QString("Main Menu"));
    int mxPos = this->width()/2 - main_menu->boundingRect().width()/2;
    int myPos = 320;
    main_menu->setPos(mxPos,myPos);
    connect(main_menu, SIGNAL(clicked()), this, SLOT(TMenu()));
    scene->addItem(main_menu);

    Button * exit_game = new Button(QString("EXIT"));
    int qxPos = this->width()/2 - exit_game->boundingRect().width()/2;
    int qyPos = 390;
    exit_game->setPos(qxPos,qyPos);
    connect(exit_game, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(exit_game);
}

void Game::ReadMap(int k)
{
    QFile fichier(T[k][0]);
    QString s;
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 41; j++)
            {

                if (fichier.read(1) == "1")
                {
                    map[i][j] = 1;
                }
                else
                {
                    map[i][j] = 0;
                }
            }
        }
        QTextStream out (&fichier);
        out >> gate[0];
        out >> gate[1];
        out >> exit[0];
        out >> exit[1];
        fichier.close();
    }
}

void Game::ReadSaved(int & a, int & b)
{
    QFile fichier("C:/Users/IHEB/Downloads/MP/MaZe/SaveGame.txt");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream out(&fichier);

        out >> level;
        out >> a;
        out >> b;
    }
}

void Game::SaveGame()
{
    int x,y;
    hero->GetXY(x,y);
    QFile fichier("C:/Users/IHEB/Downloads/MP/MaZe/SaveGame.txt");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&fichier);

        out << level;
        out << " ";
        out << x;
        out << " ";
        out << y;
    }
}

void Game::DrawMap(int k)
{
    for (int i = 0; i < 30; i++)
    {
       for (int j = 0; j < 40; j++)
       {
            if (map[i][j] == 1)
            {
                QGraphicsPixmapItem * pix = new QGraphicsPixmapItem;
                pix->setPixmap(QPixmap(T[k][2]));
                pix->setPos(j*20,i*20);
                scene->addItem(pix);
            }
            else
            {
                QGraphicsPixmapItem * pix = new QGraphicsPixmapItem;
                pix->setPixmap(QPixmap(T[k][1]));
                pix->setPos(j*20,i*20);
                scene->addItem(pix);
            }
        }

    }

}


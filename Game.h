#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>

#include "Hero.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    // Methods
    Game();
    void ReadMap(int k);
    void DrawMap(int k);
    void ReadSaved(int &a, int &b);
    void SaveGame();
    void start();


    // Attributes
    QGraphicsScene * scene;
    Hero * hero;
    QString S[5];
    QString T[5][3];

    int map[30][40];
    int gate[2];
    int exit[2];
    int level;

public slots:
    void NewGame();
    void Resume();
    void QMenu();
    void TMenu();
};

#endif // GAME_H

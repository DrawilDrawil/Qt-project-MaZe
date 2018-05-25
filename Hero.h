#ifndef HERO_H
#define HERO_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Hero:public QObject, public QGraphicsPixmapItem
{ Q_OBJECT
public :
    Hero(QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);
    void GetXY(int &a, int &b);
private:
    // QPixmap frames[8];
};

#endif // MYRECT_H

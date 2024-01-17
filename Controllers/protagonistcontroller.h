#ifndef PROTAGONISTCONTROLLER_H
#define PROTAGONISTCONTROLLER_H

//#include "mainwindow.h"
#include "logiccontroller.h"
#include "world.h"
#include "xenemy.h"


class ProtagonistController : public QObject
{
    Q_OBJECT
public:
    ProtagonistController();
    static ProtagonistController * getInstance();
    static void create();
    static void destroy();
    void defeatEnemy(std::shared_ptr<Enemy> tile);
    void defeatPEnemy(std::shared_ptr<PEnemy> tile);
    void defeatXEnemy(std::shared_ptr<XEnemy> enemy);
    const std::shared_ptr<Protagonist> getProtagonist() const {return protagonist;};
    void setProtagonist(std::shared_ptr<Protagonist> p) {protagonist = p;};
    bool isDead(){return dead;};
    void setDead(bool d){dead = d;};
    bool onProtagonist(int x, int y);
    void addVisitedTile(std::shared_ptr<Tile> tile);
    std::unordered_map<int,std::shared_ptr<Tile>>* getVisitedTiles() {return &visitedTiles;}


private:
    static ProtagonistController* instance;
    std::shared_ptr<Protagonist> protagonist;
    std::unordered_map<int,std::shared_ptr<Tile>> visitedTiles;
    bool dead = false;
};

#endif // PROTAGONISTCONTROLLER_H

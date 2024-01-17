#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "world.h"
#include "xenemy.h"

class EnemyController
{
public:
    EnemyController();

    static EnemyController * getInstance();
    static void create();
    static void destroy();
    std::shared_ptr<Enemy> getEnemy(std::shared_ptr<Tile> tile);
    std::shared_ptr<PEnemy> getPEnemy(std::shared_ptr<Tile> tile);
    std::shared_ptr<XEnemy> getXEnemy(std::shared_ptr<Tile> tile);
    bool isPEnemy(std::shared_ptr<Enemy> enemy);
    bool isXEnemy(std::shared_ptr<Enemy> enemy);
    std::unordered_map<int,std::shared_ptr<Enemy>>* getEnemies() {return &enemies;}
    void setEnemies(std::unordered_map<int,std::shared_ptr<Enemy>> enemiesMap) {enemies = enemiesMap;};
    //void deleteEnemy(std::shared_ptr<Tile> tile);
    std::shared_ptr<Enemy> findNearestEnemy(int x, int y);
    bool EnemyOnPath(std::vector<Tile *>* path);
    bool enemyOnTile(int x, int y);

private:
    static EnemyController* instance;
    //std::vector<std::shared_ptr<Enemy>> enemies;
    std::unordered_map<int,std::shared_ptr<Enemy>> enemies;
};


#endif // ENEMYCONTROLLER_H

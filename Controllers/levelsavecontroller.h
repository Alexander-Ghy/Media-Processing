#ifndef LEVELSAVECONTROLLER_H
#define LEVELSAVECONTROLLER_H

#include "world.h"
#include <fstream>
#include <memory>
#include <random>
#include <unordered_map>



class LevelSaveController
{
public:
    LevelSaveController();
    static LevelSaveController * getInstance();
    static void create();
    static void destroy();

    void saveLevel();
    void saveProtagonist();
    void savePEnemies();
    void saveXEnemies();
    void saveEnemies();
    void saveHealthPacks();

    void loadInLevel();
    void addProtagonist(std::string line);
    void addPEnemies(std::string line);
    void addXEnemies(std::string line);
    void addEnemies(std::string line);
    void addHealthPacks(std::string line);

private:
    static LevelSaveController* instance;
    std::ofstream* my_file_output;
    std::ifstream* my_file_input;
    std::uniform_int_distribution<int> uniform_perc = std::uniform_int_distribution<int>(0,100);
    std::unordered_map<int,std::shared_ptr<Enemy>> enemiesMap;
    std::unordered_map<int,std::shared_ptr<Tile>> healthpacks;
    int worldCols;
    int worldRows;
};

#endif // LEVELSAVECONTROLLER_H

#include <iostream>
#include <fstream>

#include "Controllers/protagonistcontroller.h"
#include "Controllers/healthpackcontroller.h"
#include "Controllers/enemycontroller.h"
#include "world.h"

#include "levelsavecontroller.h"

LevelSaveController * LevelSaveController::instance = 0;
LevelSaveController::LevelSaveController()
{

}

LevelSaveController *LevelSaveController::getInstance()
{
    if(!instance) instance = new LevelSaveController();
    return instance;
}

void LevelSaveController::create()
{
    if(instance != 0)
        return;

    instance = new LevelSaveController();
}

void LevelSaveController::destroy()
{
    delete instance;
    instance = 0;
}

void LevelSaveController::saveLevel()
{
    std::ofstream new_file("levelSaved.txt");
    my_file_output = &new_file;
    if (!my_file_output) {
        std::cout << "LevelSaveController saveLevel(): File is created, starting to save the world..."<<std::endl;
        //! TODO save the amount of rows and cols
        saveProtagonist();
        savePEnemies();
        saveXEnemies();
        saveEnemies();
        saveHealthPacks();
        my_file_output->close();
        std::cout << "LevelSaveController: Writing to file ended, world is saved"<<std::endl;
    }
    else {
        std::cout << "LevelSaveController saveLevel(): File created successfully!" << std::endl;
        my_file_output->close();
    }
}

void LevelSaveController::saveProtagonist()
{
    /*
    - protagonist
        - x,y pos
        - health
        - energy
    */
    auto protagonist = ProtagonistController::getInstance()->getProtagonist();
    *my_file_output << protagonist->serialize() << "\n";
    *my_file_output << protagonist->getHealth() << "\n";
    *my_file_output << protagonist->getEnergy();
    *my_file_output << "\n" << "---" << "\n";
}

void LevelSaveController::savePEnemies()
{
    /*
    - Penemies
        - x,y pos ,  defeated , poisonlevel
    */
    auto enemiesMap = EnemyController::getInstance()->getEnemies();
    for (auto& map: *enemiesMap)
    {
        auto enemy = map.second;
        if (EnemyController::getInstance()->isPEnemy(enemy))
        {
            auto Penemy = EnemyController::getInstance()->getPEnemy(enemy);
            *my_file_output << Penemy->serialize() << ",";
            *my_file_output << Penemy->getDefeated() << ",";
            *my_file_output << Penemy->getPoisonLevel();
        }
    }
    *my_file_output << "\n" << "---" << "\n";
}

void LevelSaveController::saveXEnemies()
{
    /*
    - Xenemies
        - x,y pos , defeated
    */
    auto enemiesMap = EnemyController::getInstance()->getEnemies();
    for (auto& map: *enemiesMap)
    {
        auto enemy = map.second;
        if (EnemyController::getInstance()->isXEnemy(enemy))
        {
            auto Xenemy = EnemyController::getInstance()->getXEnemy(enemy);
            *my_file_output << Xenemy->serialize() << ",";
            *my_file_output << Xenemy->getDefeated();
        }
    }
    *my_file_output << "\n" << "---" << "\n";
}

void LevelSaveController::saveEnemies()
{
    /*
    - Enemies
        - x,y pos , defeated
    */
    auto enemiesMap = EnemyController::getInstance()->getEnemies();
    for (auto& map: *enemiesMap)
    {
        auto enemy = map.second;
        if (!EnemyController::getInstance()->isXEnemy(enemy) && !EnemyController::getInstance()->isPEnemy(enemy))
        {
            *my_file_output << enemy->serialize() << ",";
            *my_file_output << enemy->getDefeated();
        }
    }
    *my_file_output << "\n" << "---" << "\n";
}

void LevelSaveController::saveHealthPacks()
{
    /*
    - Healthpacks
        - x,y pos
    */
    auto healpackMap = HealthpackController::getInstance()->getHealthpacks();
    for (auto& map: *healpackMap)
    {
        auto healthpack = map.second;
        *my_file_output << healthpack->serialize();
    }
    *my_file_output << "\n" << "---" << "\n";
}

void LevelSaveController::loadInLevel()
{
    /* ORDER saved in the .txt file:
    - protagonist
        - x,y pos
        - health
        - energy
    - Penemies
        - x,y pos
        - defeated
        - poisonlevel
    - Xenemies
        - x,y pos
        - defeated
    - Enemies
        - x,y pos
        - defeated
    - Healthpacks
        - x,y pos
    */

    std::ifstream new_file("levelSaved.txt");
    my_file_input = &new_file;

    std::string line;

    if (my_file_input->is_open())
    {
        std::cout << "LevelSaveController loadInLevel(): Opened file" << std::endl;
        while (getline(*my_file_input,line))
        {
            std::cout << line << '\n';
            //TODO
            //! TODO save the amount of rows and cols
            //!Alle functies apart oproepen lijn per lijn
            //!nadat klaar met enemy en healthpacks, dan controllers oproepen om zo hun mappen te vervangen
            //! //EnemyController::getInstance()

        }
        my_file_input->close();
    }

    else std::cout << "LevelSaveController loadInLevel(): Unable to open file" << std::endl;
}

void LevelSaveController::addProtagonist(std::string line)
{
    /*
    - protagonist
        - x,y pos , health , energy
    */
    std::string delimiter = ",";
    std::string xValueString = line.substr(0, line.find(delimiter));
    std::string yValueString = line.substr(1, line.find(delimiter));
    std::string healthString = line.substr(2, line.find(delimiter));
    std::string energyString = line.substr(2, line.find(delimiter));
    int xValue = std::stoi(xValueString);
    int yValue = std::stoi(yValueString);
    float health = std::stof(healthString);
    float energy = std::stof(energyString);
    auto protagonist = std::make_shared<Protagonist>();
    protagonist->setPos(xValue, yValue);
    protagonist->setHealth(health);
    protagonist->setEnergy(energy);
    ProtagonistController::getInstance()->setProtagonist(protagonist);
}

void LevelSaveController::addPEnemies(std::string line)
{
    /*
    - Penemies
        - x,y pos , defeated , poisonlevel
    */
    std::string delimiter = ",";
    std::string xValueString = line.substr(0, line.find(delimiter));
    std::string yValueString = line.substr(1, line.find(delimiter));
    std::string defeatedString = line.substr(2, line.find(delimiter));
    std::string poisonLevelString = line.substr(3, line.find(delimiter));
    int xValue = std::stoi(xValueString);
    int yValue = std::stoi(yValueString);
    int defeatedInt = std::stoi(defeatedString);
    bool defeated = (bool) defeatedInt;
    float poisonLevel = std::stof(poisonLevelString);

    std::random_device r;
    std::default_random_engine e1(r());

    auto Penemy = std::make_shared<PEnemy>(xValue, yValue, uniform_perc(e1));
    Penemy->setDefeated(defeated);
    Penemy->setPoisonLevel(poisonLevel);
    std::pair<int,std::shared_ptr<Enemy>> pair;
    pair.first = ((yValue * worldCols) + xValue);
    pair.second = Penemy;
    enemiesMap.insert(pair);
}

void LevelSaveController::addXEnemies(std::string line)
{
    /*
    - Xenemies
        - x,y pos , defeated
    */

}

void LevelSaveController::addEnemies(std::string line)
{
    /*
    - Enemies
        - x,y pos , defeated
    */


}

void LevelSaveController::addHealthPacks(std::string line)
{
    /*
    - Healthpacks
        - x,y pos
    */

}

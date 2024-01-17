#include "protagonistcontroller.h"
#include "Controllers/enemycontroller.h"

#include <Views/textbasedview.h>
#include <iostream>
#include <mainwindow.h>
ProtagonistController * ProtagonistController::instance = 0;
ProtagonistController::ProtagonistController()
{
}

ProtagonistController *ProtagonistController::getInstance()
{
    if(!instance) instance = new ProtagonistController();
    return instance;
}

void ProtagonistController::create()
{
    if(instance != 0)
        return;

    instance = new ProtagonistController();
}

void ProtagonistController::destroy()
{
    delete instance;
    instance = 0;
}

void ProtagonistController::defeatEnemy(std::shared_ptr<Enemy> enemy){
    float health = protagonist->getHealth();
    float strength = enemy->getValue();
    if(health>strength){
            QObject::connect(enemy.get(), &Enemy::dead, LogicController::getInstance()->getMainWindow().get(), &MainWindow::on_enemy_dead);
            emit LogicController::getInstance()->attack();
            auto tileFromMap = WorldController::getInstance()->getTileByXY(enemy->getXPos(),enemy->getYPos());
            tileFromMap->setValue(std::numeric_limits<float>::infinity());
            protagonist->setPos(enemy->getXPos(), enemy->getYPos());
            protagonist->setHealth(health-strength); // emit lose health
            protagonist->setEnergy(100.0f); // emit energy 100
            enemy->setDefeated(true);   // emit enemy dead
            LogicController::getInstance()->getCurrView()->createView();
    }
    else{
        emit LogicController::getInstance()->gameOver(ProtagonistController::getInstance()->getProtagonist()->getXPos(), ProtagonistController::getInstance()->getProtagonist()->getYPos());
        protagonist->setHealth(0);
        protagonist->setEnergy(0.0f);
        std::cout << "Protagonistcntrl: protagonist dies Enemy" << std::endl;
    }
}


void ProtagonistController::defeatPEnemy(std::shared_ptr<PEnemy> enemy){
    float health = protagonist->getHealth();
    float strength = enemy->getValue();
    if(health>strength){
            QObject::connect(enemy.get(), &Enemy::dead, LogicController::getInstance()->getMainWindow().get(), &MainWindow::on_enemy_dead);
            QObject::connect(enemy.get(), &PEnemy::poisonLevelUpdated, LogicController::getInstance()->getCurrView(), &Views::on_poisoned);
            emit LogicController::getInstance()->attack();
            auto tileFromMap = WorldController::getInstance()->getTileByXY(enemy->getXPos(),enemy->getYPos());
            tileFromMap->setValue(std::numeric_limits<float>::infinity());
            protagonist->setPos(enemy->getXPos(), enemy->getYPos());
            protagonist->setHealth(health-strength); // emit lose health
            enemy->poison(); // emit poison
            protagonist->setEnergy(100.0f); // emit energy 100
            enemy->setDefeated(true);
            LogicController::getInstance()->getCurrView()->createView();
    }
    else{
        // emit protagonist dies
        emit LogicController::getInstance()->gameOver(ProtagonistController::getInstance()->getProtagonist()->getXPos(), ProtagonistController::getInstance()->getProtagonist()->getYPos());
        protagonist->setHealth(0);
        protagonist->setEnergy(0.0f);
        std::cout << "Protagonistcntrl: protagonist dies PEnemy" << std::endl;
    }
}

void ProtagonistController::defeatXEnemy(std::shared_ptr<XEnemy> enemy){
    float health = protagonist->getHealth();
    float strength = enemy->getValue();
    if(health>strength){
            QObject::connect(enemy.get(), &Enemy::dead, LogicController::getInstance()->getMainWindow().get(), &MainWindow::on_enemy_dead);
            emit LogicController::getInstance()->attack();
            auto tileFromMap = WorldController::getInstance()->getTileByXY(enemy->getXPos(),enemy->getYPos());
            tileFromMap->setValue(std::numeric_limits<float>::infinity());
            protagonist->setPos(enemy->getXPos(), enemy->getYPos());
            protagonist->setHealth(health-strength); // emit lose health

            protagonist->setEnergy(100.0f); // emit energy 100
            enemy->setDefeated(true);
            LogicController::getInstance()->getCurrView()->createView();
    }
    else{
        // emit protagonist dies
        emit LogicController::getInstance()->gameOver(ProtagonistController::getInstance()->getProtagonist()->getXPos(), ProtagonistController::getInstance()->getProtagonist()->getYPos());
        protagonist->setHealth(0);
        protagonist->setEnergy(0.0f);
        std::cout << "Protagonistcntrl: protagonist dies PEnemy" << std::endl;
    }
}

bool ProtagonistController::onProtagonist(int x, int y)
{
    if((protagonist->getXPos() == x) && (protagonist->getYPos() == y))
    {
        return true;
    } else return false;
}

void ProtagonistController::addVisitedTile(std::shared_ptr<Tile> tile)
{
    auto xPos = tile->getXPos();
    auto yPos = tile->getYPos();
    auto keyValue = (yPos * WorldController::getInstance()->getWorld()->getCols()) + xPos;
    if(visitedTiles.count(keyValue) == 0)
    {
        visitedTiles.emplace(keyValue, tile);
    }
}



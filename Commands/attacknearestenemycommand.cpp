#include "attacknearestenemycommand.h"

#include <Controllers/enemycontroller.h>
#include <Controllers/protagonistcontroller.h>



AttackNearestEnemyCommand::AttackNearestEnemyCommand()
{

}

void AttackNearestEnemyCommand::executeCommand()
{
    auto protagonist = ProtagonistController::getInstance()->getProtagonist();
    Point pointProtagonist = Point();
    pointProtagonist.xPos = protagonist->getXPos();
    pointProtagonist.yPos = protagonist->getYPos();
    auto enemy = EnemyController::getInstance()->findNearestEnemy(pointProtagonist.xPos, pointProtagonist.yPos);
    Point pointEnemy = Point();
    pointEnemy.xPos = enemy->getXPos();
    pointEnemy.yPos = enemy->getYPos();
    auto algorithm = LogicController::getInstance()->getAlgorithm();
    algorithm->setUpNewRun();
    algorithm->Solve(&pointProtagonist, &pointEnemy);
    auto solution = algorithm->getSolution();
    LogicController::getInstance()->FollowPath(&solution);
}

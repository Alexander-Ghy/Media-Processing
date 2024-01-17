#include "logiccontroller.h"
#include "Controllers/worldcontroller.h"
#include "Controllers/enemycontroller.h"
#include "Controllers/healthpackcontroller.h"
#include "Controllers/protagonistcontroller.h"

#include <Views/textbasedview.h>
#include <QObject>
#include <QTime>
#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <algorithm/astarbestpath.h>


LogicController * LogicController::instance = 0;
LogicController::LogicController()
{
    algorithm = std::make_shared<Astar>();
}

LogicController *LogicController::getInstance()
{
    if(!instance) instance = new LogicController();
    return instance;
}

void LogicController::create()
{
    if(instance != 0)
        return;

    instance = new LogicController();
}

void LogicController::destroy()
{
    delete instance;
    instance = 0;
}

void LogicController::createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio)
{
    WorldController::getInstance()->SetUp(filename, nrOfEnemies, nrOfHealthpacks, pRatio);
}

void LogicController::initViews()
{
    TextBasedView::getInstance()->initGrid();
    algorithm->setUpInitial();
}

bool LogicController::checkIfIllegalPosition(int xNew, int yNew)
{
    //std::cout<<"xNew:" << xNew <<std::endl;
    //std::cout<<"yNew:" << yNew <<std::endl;
    auto world = WorldController::getInstance()->getWorld();
    if (xNew > (world->getCols()-1) || yNew > (world->getRows()-1))
            return true;

    auto tile = WorldController::getInstance()->getTileByXY(xNew, yNew);
    //std::cout<<"tile value:" << tile->getValue()<<std::endl;
    if (tile->getValue() == std::numeric_limits<float>::infinity())
        return true;
    return false;
}

void LogicController::moveProtagonist(CommandList::Commandstest cmd)
{
    int y = ProtagonistController::getInstance()->getProtagonist()->getYPos();
    int x = ProtagonistController::getInstance()->getProtagonist()->getXPos();
    switch(cmd)
    {
    case CommandList::Commandstest::up:
        if(y > 0)
        {
            moveToTile(WorldController::getInstance()->getTileByXY(x, y-1));
            std::cout << "up" << std::endl;
        }
        break;
    case CommandList::Commandstest::down:
        if(y < WorldController::getInstance()->getWorld()->getRows()-1)
        {
            moveToTile(WorldController::getInstance()->getTileByXY(x, y+1));
            std::cout << "down" << std::endl;
        }
        break;
    case CommandList::Commandstest::left:
        if(x > 0)
        {
            moveToTile(WorldController::getInstance()->getTileByXY(x-1, y));
            std::cout << "left" << std::endl;
        }
        break;
    case CommandList::Commandstest::right:
        if(x < WorldController::getInstance()->getWorld()->getCols()-1)
        {
            moveToTile(WorldController::getInstance()->getTileByXY(x+1, y));
            std::cout << "right" << std::endl;
        }
        break;
    default:
        break;
    }
}


void LogicController::moveToTile(std::shared_ptr<Tile> tile)
{
    std::shared_ptr<Protagonist> prot = ProtagonistController::getInstance()->getProtagonist();
    int x = prot->getXPos();
    int y = prot->getYPos();

    auto PEnemy = EnemyController::getInstance()->getPEnemy(tile);
    auto XEnemy = EnemyController::getInstance()->getXEnemy(tile);
    auto Enemy = EnemyController::getInstance()->getEnemy(tile);
    auto healthPack = HealthpackController::getInstance()->isHealthpack(tile);

    if(PEnemy != nullptr)
    {
        if(!checkIfIllegalPosition(tile->getXPos(), tile->getYPos()))
        {
            std::cout << "logiccntrl: defeatPEnemy" << std::endl;
            //XEnemiesMove();
            ProtagonistController::getInstance()->defeatPEnemy(PEnemy); // lose of health + enkel als genoeg health
        } else std::cout << "impassable Penemy" << std::endl;
        return;
    }
    else if(XEnemy != nullptr){
        if(!checkIfIllegalPosition(tile->getXPos(), tile->getYPos()))
        {
            std::cout << "logiccntrl: defeatXEnemy" << std::endl;
            //LogicController::getInstance()->XEnemiesMove();
            ProtagonistController::getInstance()->defeatXEnemy(XEnemy); // lose of health + enkel als genoeg health
        } else std::cout << "impassable Xenemy" << std::endl;
        return;
    }

    else if(Enemy != nullptr){
        if(!checkIfIllegalPosition(tile->getXPos(), tile->getYPos()))
        {
            std::cout << "logiccntrl: defeatEnemy" << std::endl;
            //XEnemiesMove();
            ProtagonistController::getInstance()->defeatEnemy(Enemy); // lose of health + enkel als genoeg health
        } else std::cout << "impassable enemy" << std::endl;
        return;
    }

    else if(healthPack)
    {
        emit healthpack();
        std::cout << "logiccntrl: setHealth" << std::endl;
        prot->setHealth(100.0f); // emit increment health
        HealthpackController::getInstance()->deleteHealthPack(tile);
        //XEnemiesMove();
        ProtagonistController::getInstance()->getProtagonist()->setPos(tile->getXPos(), tile->getYPos());
        ProtagonistController::getInstance()->addVisitedTile(tile);
        curr->createView();
        return;
    }
    else
    {
        float energy = prot->getEnergy();
        float next = energy - tile->getValue();
        std::cout << "logiccntrl next: " << next << std::endl;
        if (next > 0){
            ProtagonistController::getInstance()->getProtagonist()->setPos(tile->getXPos(), tile->getYPos());
            ProtagonistController::getInstance()->addVisitedTile(tile);
            prot->setEnergy(next); // emit lose of energy
            //XEnemiesMove();
            curr->createView();
            std::cout << "Logiccntrl: Moved over a normal tile" << std::endl;
            return;
        }
        else{
            prot->setEnergy(0); // emit energy to 0
            emit gameOver(x,y);
            std::cout << "Logiccntrl: Out of energy - protagonist dies" << std::endl;
            return;
        }
    }
}

void LogicController::setMainWindow(const std::shared_ptr<MainWindow> &mw)
{
    mainWindow = mw;
}

const std::shared_ptr<Algorithm> &LogicController::getAlgorithm() const
{
    return algorithm;
}

void LogicController::FollowPath(std::vector<Tile *>* solution)
{
    auto protagonist = ProtagonistController::getInstance()->getProtagonist();
    while (!solution->empty())
    {
        auto tile = solution->back();
        solution->pop_back();
        auto xPosSol = tile->getXPos();
        auto yPosSol = tile->getYPos();
        std::cout << "Follow path position X:" <<xPosSol << " Y:" << yPosSol << std::endl;
        auto xPosProtagonist = ProtagonistController::getInstance()->getProtagonist()->getXPos();
        auto yPosProtagonist = ProtagonistController::getInstance()->getProtagonist()->getYPos();

        //remember: y count goes up from top to bottom
        //          x count goes up from left to right

        //Stop following path if protagonist dies
        if (protagonist->getHealth() == 0 || protagonist->getEnergy() == 0)
            break;

        if ((yPosProtagonist > yPosSol))
        {
            moveProtagonist(CommandList::Commandstest::up);
        }
        if ((yPosProtagonist < yPosSol))
        {
            moveProtagonist(CommandList::Commandstest::down);
        }
        if ((xPosProtagonist >  xPosSol))
        {
            moveProtagonist(CommandList::Commandstest::left);
        }
        if ((xPosProtagonist <  xPosSol))
        {
            moveProtagonist(CommandList::Commandstest::right);
        }
        delay();
    }
}

void LogicController::autoPlay()
{
    std::cout<<"Test get in autoplay function"<<std::endl;
    auto protagonist = ProtagonistController::getInstance()->getProtagonist();
    auto enemiesMap = EnemyController::getInstance()->getEnemies();
    Point pointProtagonist = Point();
    while (!enemiesMap->empty())
    {
        pointProtagonist.xPos = protagonist->getXPos();
        pointProtagonist.yPos = protagonist->getYPos();
        auto enemy = EnemyController::getInstance()->findNearestEnemy(pointProtagonist.xPos, pointProtagonist.yPos);
        auto healthPack = HealthpackController::getInstance()->findNearestHealthPack(pointProtagonist.xPos, pointProtagonist.yPos);
        if (protagonist->getHealth() == 0 || protagonist->getEnergy() == 0)
            break;
        if (enemy->getValue() < protagonist->getHealth() && enemy != std::nullptr_t())
        {
            std::cout<<"\n\tAutoplay: Going to enemy"<<std::endl;
            Point pointEnemy = Point();
            pointEnemy.xPos = enemy->getXPos();
            pointEnemy.yPos = enemy->getYPos();
            algorithm->setUpNewRun();
            algorithm->Solve(&pointProtagonist, &pointEnemy);
            auto solution = algorithm->getSolution();
            FollowPath(&solution);
        }
        else if(healthPack != std::nullptr_t())
        {
            std::cout<<"\n\tAutoplay: Going to healthpack"<<std::endl;
            Point pointHealthPack = Point();
            pointHealthPack.xPos = healthPack->getXPos();
            pointHealthPack.yPos = healthPack->getYPos();
            algorithm->setUpNewRun();
            algorithm->Solve(&pointProtagonist, &pointHealthPack);
            auto solution = algorithm->getSolution();
            if (EnemyController::getInstance()->EnemyOnPath(&solution))
            {
                //!TODO do something better then deleting the healthpack
                std::cout<<"\n\tAutoplay: Enemy on the way to the healthpack"<<std::endl;
                //HealthpackController::getInstance()->deleteHealthPack(healthPack);
            }
            FollowPath(&solution);
        }
        else //if no healthpack is available and we cant defeat the enemy without dying we will attack it and lose the game
        {
            std::cout<<"\n\tAutoplay: going to an enemy and will die"<<std::endl;
            Point pointEnemy = Point();
            pointEnemy.xPos = enemy->getXPos();
            pointEnemy.yPos = enemy->getYPos();
            algorithm->setUpNewRun();
            algorithm->Solve(&pointProtagonist, &pointEnemy);
            auto solution = algorithm->getSolution();
            FollowPath(&solution);
        }
        delay();
    }
    std::cout<<"Autoplay end function"<<std::endl;
}

void LogicController::XEnemiesMove(){
    /*std::shared_ptr<Protagonist> prot = ProtagonistController::getInstance()->getProtagonist();
    int x = prot->getXPos();
    int y = prot->getYPos();

    auto enemies = *EnemyController::getInstance()->getEnemies();
    auto healthPacks = *HealthpackController::getInstance()->getHealthpacks();
    std::srand(std::time(nullptr));
    for(auto map=enemies.begin(); map!=enemies.end();map++) {
        auto enemy = map->second;
        if (EnemyController::getInstance()->isXEnemy(enemy) && !enemy->getDefeated())
        {
            connect(this, &LogicController::XEnemyChange, curr, &Views::on_XEnemy_changed);
            int direction = rand()%4;
            switch(direction){
            case 1:
            {
                if((enemy->getXPos()+1 < WorldController::getInstance()->getWorld()->getCols()))
                {
                    if((enemy->getXPos()+1 != x) && (enemy->getYPos() != y)){
                    auto key = ((enemy->getXPos()+1) * WorldController::getInstance()->getWorld()->getCols()) + enemy->getYPos();
                    if (!enemies.count(key) && !healthPacks.count(key))
                    {
                    emit XEnemyChange(enemy->getXPos(), enemy->getYPos());
                    enemies.at(map->first)->setXPos(enemy->getXPos()+1);

                    //enemy->setXPos(enemy->getXPos()+1);
                    auto node = enemies.extract(map->first);
                    if(!node.empty()){
                    node.key() = key;
                    enemies.insert(std::move(node));}
                    }
                    }
                }
                break;

            }
            case 2:
            {
                if((enemy->getXPos() > 0))
                {
                    if((enemy->getXPos()-1 != x) && (enemy->getYPos() != y))
                    {
                    auto key = ((enemy->getXPos()-1) * WorldController::getInstance()->getWorld()->getCols()) + enemy->getYPos();
                    if (!enemies.count(key) && !healthPacks.count(key))
                    {
                    emit XEnemyChange(enemy->getXPos(), enemy->getYPos());
                        enemies.at(map->first)->setXPos(enemy->getXPos()-1);
                        //enemy->setXPos(enemy->getXPos()-1);
                    auto node = enemies.extract(map->first);
                    if(!node.empty()){
                    node.key() = key;
                    enemies.insert(std::move(node));}
                    }
                    }
                }
                break;

                }
            case 3:
            {
                if((enemy->getYPos()+1 < WorldController::getInstance()->getWorld()->getRows()))
                {
                    if((enemy->getXPos() != x) && (enemy->getYPos()+1 != y))
                    {
                    auto key = ((enemy->getXPos()) * WorldController::getInstance()->getWorld()->getCols()) + (enemy->getYPos()+1);
                    if (!enemies.count(key) && !healthPacks.count(key))
                    {
                    emit XEnemyChange(enemy->getXPos(), enemy->getYPos());
                        enemies.at(map->first)->setYPos(enemy->getYPos()+1);

                   // enemy->setYPos(enemy->getYPos()+1);
                    auto node = enemies.extract(map->first);
                    if(!node.empty()){
                    node.key() = key;
                    enemies.insert(std::move(node));}
                    }
                    }
                }
                break;

                }
            case 4:
            {
                if((enemy->getYPos() > 0))
                {
                    if(((enemy->getXPos() != x) && (enemy->getYPos()-1 != y)))
                    {
                    auto key = ((enemy->getXPos()) * WorldController::getInstance()->getWorld()->getCols()) + (enemy->getYPos()-1);
                    if (!enemies.count(key) && !healthPacks.count(key))
                    {
                    emit XEnemyChange(enemy->getXPos(), enemy->getYPos());
                        enemies.at(map->first)->setYPos(enemy->getYPos()-1);

                    //enemy->setYPos(enemy->getYPos()-1);
                    auto node = enemies.extract(map->first);
                    if(!node.empty()){
                    node.key() = key;
                    enemies.insert(std::move(node));}
                    }
                    }
                }
                break;

                }
            default:
            {
                if((enemy->getXPos()+1 < WorldController::getInstance()->getWorld()->getCols()))
                {
                    if(((enemy->getXPos()+1 != x) && (enemy->getYPos() != y)))
                    {
                    auto key = ((enemy->getXPos()+1) * WorldController::getInstance()->getWorld()->getCols()) + enemy->getYPos();
                    if (!enemies.count(key) && !healthPacks.count(key))
                    {
                    emit XEnemyChange(enemy->getXPos(), enemy->getYPos());
                        enemies.at(map->first)->setXPos(enemy->getXPos()+1);
                   // enemy->setXPos((enemy->getXPos()+1));
                    auto node = enemies.extract(map->first);
                    if(!node.empty()){
                    node.key() = key;
                    enemies.insert(std::move(node));}
                    }
                    }
                }
                break;
            }
        }
    }
    }*/
}

void LogicController::setCurrView(Curr current)
{

    switch(current){

    case text:
            curr = TextBasedView::getInstance();
            break;
    case graphical:
            curr = GraphicsBasedWorld::getInstance();
            break;
    default:
            curr = GraphicsBasedWorld::getInstance();


    }

    connect(this, &LogicController::healthpack, curr, &Views::on_healthpack);
    connect(this, &LogicController::gameOver, curr, &Views::on_game_over);
    connect(this, &LogicController::attack, curr, &Views::on_attack);
    connect(ProtagonistController::getInstance()->getProtagonist().get(), &Protagonist::posChanged, curr, &Views::on_position_changed);
    connect(ProtagonistController::getInstance()->getProtagonist().get(), &Protagonist::energyChanged, mainWindow.get(), &MainWindow::on_energy_changed);
    connect(ProtagonistController::getInstance()->getProtagonist().get(), &Protagonist::healthChanged, mainWindow.get(), &MainWindow::on_health_changed);
    connect(curr, &Views::stopGame, mainWindow.get(), &MainWindow::on_stop_game);
}

void LogicController::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(graphicsDelay*1000);
    while( QTime::currentTime()<dieTime)
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100);
    }
}

void LogicController::changeGraphicsDelay(int factor)
{
    graphicsDelay = (factor*0.1);
}

void LogicController::buttonAstar()
{
    algorithm = std::make_shared<Astar>();
    algorithm->setUpInitial();
}

void LogicController::buttonAstarBest()
{
    algorithm = std::make_shared<AstarBestPath>();
    algorithm->setUpInitial();
}

#include "algorithm/algorithm.h"

#include <Controllers/enemycontroller.h>
#include <Controllers/worldcontroller.h>

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

void Algorithm::setUpInitial()
{
    cleanUp();
    auto world = WorldController::getInstance()->getWorld();
    worldCols = world->getCols();
    worldRows = world->getRows();
    addNodes();
    addEnemies();

    Point nodeUP = Point();
    nodeUP.xPos = 0;
    nodeUP.yPos = 1;
    Point nodeDOWN = Point();
    nodeDOWN.xPos = 0;
    nodeDOWN.yPos = -1;
    Point nodeLEFT = Point();
    nodeLEFT.xPos = -1;
    nodeLEFT.yPos = 0;
    Point nodeRIGHT = Point();
    nodeRIGHT.xPos = 1;
    nodeRIGHT.yPos = 0;

    surroundingNodes.push_back(nodeUP);
    surroundingNodes.push_back(nodeDOWN);
    surroundingNodes.push_back(nodeLEFT);
    surroundingNodes.push_back(nodeRIGHT);
}

void Algorithm::setUpNewRun()
{
    cleanUp();
    auto world = WorldController::getInstance()->getWorld();
    worldCols = world->getCols();
    worldRows = world->getRows();
    addNodes();
    addEnemies();
}

void Algorithm::addNodes()
{
    //alle nodes zitten al in een unordenend map sturctuur opgeslagen hier, dus niet op basis van index nog calculeren
    //ze zitten in tilesmap niet op volgorde van 0 tot de laatste
    auto tilesMap = WorldController::getInstance()->getTilesUnorderedMap();
    for (auto& tileMapInstance: *tilesMap)
    {
        auto tile = tileMapInstance.second;
        auto node = new Node(tile->getXPos(), tile->getYPos(),tile->getValue());
        //int index = (tile->getYPos() * world->getCols()) + tile->getXPos();
        //allNodes[index] = node;
        allNodesAlgorithm.emplace_back(node);
    }
}

void Algorithm::addEnemies()
{
    auto unordenenMap = *EnemyController::getInstance()->getEnemies();
    for(auto mapKeyAndEnemy: unordenenMap)
    {
        auto enemy = mapKeyAndEnemy.second;
        float value = 1.0f;
        if (enemy->getDefeated())
        {
            value = std::numeric_limits<float>::infinity();
        }
        Point pointEnemy = Point();
        pointEnemy.xPos = enemy->getXPos();
        pointEnemy.yPos = enemy->getYPos();
        auto node = getNode(&pointEnemy);
        node->setValue(value);
    }
}

void Algorithm::cleanUp()
{
    //!todo fix this function to free pointers - when trying to do this -> segmentation faults
    /*for (auto& node: allNodes)
    {
        if (node != NULL)
        {
            delete node;
        }
    }*/
    allNodesAlgorithm.clear();
    /*for (auto& node: solution)
    {
        if (node != NULL)
        {
            delete node;
        }
    }*/
    solution.clear();
}

Node *Algorithm::getNode(Point *point)
{
    int index = (point->yPos * worldCols) + point->xPos;
    return allNodesAlgorithm[index];
}

void Algorithm::reconstructPath(Node *end)
{
    std::vector<Tile*> solutionTemp;
    solutionTemp.emplace_back(end);
    //end->setInSolution(true);
    while (end->getParent() != NULL)
    {
        solutionTemp.emplace_back(end);
        //end->setInSolution(true);
        end = end->getParent();
    }
    solutionTemp.push_back(end);
    //end->setInSolution(true);
    solution = solutionTemp;
}

bool Algorithm::checkExit(Node *start, Node *goal)
{
    return (((start->getXPos() == goal->getXPos()) && (start->getYPos() == goal->getYPos())));
}

const std::vector<Tile *> &Algorithm::getSolution() const
{
    return solution;
}

int Algorithm::getWeightUser() const
{
    return weightUser;
}

void Algorithm::setWeightUser(int newWeightUser)
{
    weightUser = (newWeightUser*10);
    //std::cout<<weightUser<<std::endl;
}

const std::vector<Point> &Algorithm::getSurroundingNodes() const
{
    return surroundingNodes;
}

int Algorithm::getWorldCols() const
{
    return worldCols;
}

int Algorithm::getWorldRows() const
{
    return worldRows;
}

const std::vector<Node *> &Algorithm::getAllNodesAlgorithm() const
{
    return allNodesAlgorithm;
}

void Algorithm::setExecutionTime(const std::chrono::duration<long, std::ratio<1, 1000000> >::rep &newExecutionTime)
{
    executionTime = newExecutionTime;
}

bool Algorithm::checkBorders(int surroudingNodeX, int surroudingNodeY)
{
    if (surroudingNodeX < 0 ||  surroudingNodeY < 0 || surroudingNodeX > (getWorldCols()-1) || surroudingNodeY > (getWorldRows()-1))
    {
        return true;
    }
    return false;
}



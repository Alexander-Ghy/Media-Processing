#include <iostream>
#include <queue>
#include "astar.h"
#include "node.h"

Astar::Astar()
    : Algorithm()
{

}

Astar::~Astar()
{

}

void Astar::Solve(Point* start, Point* goal)
{
    cleanUp();
    openList = {};
    surroundingNodesAstar = getSurroundingNodes();

    unsigned int tilesChecked = 0;

    //From here the algorithm starts
    auto startTime = std::chrono::high_resolution_clock::now();

    auto startNode = getNode(start);
    auto goalNode = getNode(goal);

    startNode->setVisited(true);
    float finalCost = calculateTotalCost(startNode, goalNode);
    startNode->setFinalCost(finalCost);
    std::pair<float,Node*> nodePair(finalCost, startNode);
    openList.emplace(nodePair);

    auto potentialPoint = Point();

    while(!openList.empty())
    {
        auto currentNode = openList.top().second;
        openList.pop();

        if (checkExit(currentNode, goalNode))
        {
            //std::cout<<"\nFound a solution\n"<<std::endl;
            reconstructPath(currentNode);
            //solution.emplace_back(currentNode);
            //currentNode->setInSolution(true);
            //solution.emplace_back(startNode);
            //startNode->setInSolution(true);
            break;
        }

        for (int i = 0; i < 4; i++) //check up down left right - not the 4 diagonals
        {
            int surroudingNodeX = currentNode->getXPos() + surroundingNodesAstar[i].xPos;
            int surroudingNodeY = currentNode->getYPos() + surroundingNodesAstar[i].yPos;

            if (checkBorders(surroudingNodeX, surroudingNodeY))
                continue;

            //auto potentialPoint = Point();
            potentialPoint.xPos = surroudingNodeX;
            potentialPoint.yPos = surroudingNodeY;

            auto potentialNode = getNode(&potentialPoint);

            //check if its a wall
            auto potentialNodeValue = potentialNode->getValue();
            if (!(potentialNodeValue <= 1))
            {
                continue;
            }

            if(!potentialNode->getVisited()) //node has not been visited or made yet
            {
                finalCost = calculateTotalCost(potentialNode, goalNode);
                potentialNode->setParent(*currentNode);
                potentialNode->setFinalCost(finalCost);
                potentialNode->setVisited(true);
                tilesChecked++; //amount of Nodes that are made
                std::pair<float,Node*> succesorNodePair(finalCost, potentialNode);
                openList.emplace(succesorNodePair);
            }
            else
            {
                finalCost = calculateTotalCost(potentialNode, goalNode);
                if (finalCost < *potentialNode) //compare new cost with previous cost
                {
                    potentialNode->setParent(*currentNode);
                    potentialNode->setFinalCost(finalCost);
                    tilesChecked++; //amount of Nodes that are made
                    std::pair<float,Node*> succesorNodePair(finalCost, potentialNode);
                    openList.emplace(succesorNodePair);
                }
                else
                {
                    continue;
                }
            }
        }
        currentNode->setVisited(true);
        //printSolution();
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    setExecutionTime(duration.count());
    //std::cout <<"Time of execution algorithm:" << std::endl;
    //std::cout <<"\tmicroseconds: " << duration.count() << std::endl;
    //std::cout <<"\tseconds: " << (float) duration.count()/1000000 << std::endl;
    //std::cout << "The amount of tiles that have been looked at: " << tilesChecked << std::endl;
    //std::cout << "The amount of steps for the goal: " << getSolution().size() << std::endl;
    //delete startNode;
}

inline float Astar::calculateTotalCost(Node* start, Node* goal)
{
    float cost;
    float distanceCost = (float) sqrt(pow(goal->getXPos() - start->getXPos(), 2) + pow(goal->getYPos() - start->getYPos(), 2));
    float parentCost = start->getFinalCost();
    cost = distanceCost + (parentCost + ((1-start->getValue())*getWeightUser()));
    return cost;
}

/*
//function only prints all tiles, not a path yet
void Astar::printTiles() const
{
    for (auto& tile : allNodes)
    {
        if (tile->getXPos() == (getWorldCols()-1))
        {
            //last element of a line
            if (tile->getValue() == 1)
                std::cout << "0" << std::endl;
            else
                std::cout << "X" << std::endl;
        }
        else
        {
            if (tile->getValue() == INFINITY)
                std::cout << "X";
            else
                std::cout << "0";
        }
    }
    std::cout<<std::endl;
}

void Astar::printSolution()
{
    const std::string red("\033[0;31m"); //gebruikt
    const std::string green("\033[1;32m"); //gebruikt
    const std::string yellow("\033[1;33m"); //Gebruikt
    const std::string cyan("\033[0;36m"); //gebruikt
    const std::string magenta("\033[0;35m"); // https://gist.github.com/vratiu/9780109 //gebruikt
    const std::string reset("\033[0m"); // https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
    const std::string bmagnta("\u001b[35;1m");

    // 0.4 0.6 0.

    auto point = new Point();
    for (auto& tile : allNodes)
    {
        point->xPos = tile->getXPos();
        point->yPos = tile->getYPos();
        auto node = getNode(point);
        if (tile->getXPos() == (getWorldCols()-1))   //last element of a line
        {
            //std::cout<< tile->getXPos() << " " << tile->getYPos()<< std::endl;
            if (node->getVisited())
            {
                if (node->getInSolution())
                {
                    std::cout << bmagnta << "S" << std::endl;
                }
                else if (tile->getValue() == INFINITY)
                    std::cout << yellow << "X" << std::endl;
                else
                    std::cout << yellow << "1" << std::endl;
            }
            else
            {
                if (tile->getValue() == INFINITY)
                    std::cout << red << "X" << std::endl;
                else if (tile->getValue() == 0.8f)
                    std::cout << magenta << "0" << std::endl;
                else if (tile->getValue() == 0.6f)
                    std::cout << cyan << "0" << std::endl;
                else if (tile->getValue() == 0.4f)
                    std::cout << reset << "0" << std::endl;
                else
                    std::cout << green << "0" << std::endl;
            }
        }
        else
        {
            if (node->getVisited())
            {
                if (node->getInSolution())
                {
                    std::cout << bmagnta << "S";
                }
                else if (tile->getValue() == INFINITY)
                    std::cout << yellow << "X";
                else
                    std::cout << yellow << "1";
            }
            else
            {
                if (tile->getValue() == INFINITY)
                    std::cout << red << "X";
                else if (tile->getValue() == 0.8f)
                    std::cout << magenta << "0";
                else if (tile->getValue() == 0.6f)
                    std::cout << cyan << "0";
                else if (tile->getValue() == 0.4f)
                    std::cout << reset << "0";
                else
                    std::cout << green << "0";
            }
        }
    }
    std::cout<< reset << std::endl;
    delete point;
}
*/

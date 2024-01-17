#include <iostream>
#include <ostream>
#include "node.h"

Node::Node(int xPosition, int yPosition, float tileWeight)
    : Tile(xPosition, yPosition, tileWeight)
{

}

Node::Node(const Node &other)
    : Node(other.getXPos(), other.getXPos(), other.getValue())
{
    std::cout << "Copy constructor of Node was called" << std::endl;
}

float Node::getGivenCost() const
{
    return givenCost;
}

void Node::setGivenCost(float newGivenCost)
{
    givenCost = newGivenCost;
}

/*bool Node::getInSolution() const
{
    return inSolution;
}

void Node::setInSolution(bool newInSolution)
{
    inSolution = newInSolution;
}*/

bool operator<(float finalCost, const Node & node)
{
  return finalCost < node.getFinalCost();
}






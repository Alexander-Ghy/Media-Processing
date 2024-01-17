#ifndef NODE_H
#define NODE_H

#include <memory>
#include "world.h"

class Node : public Tile
{
public:
    Node(int xPosition, int yPosition, float tileWeight);
    ~Node() = default;
    Node(const Node & other);
    void setParent(Node &parent) {parentNode = &parent;};
    Node* getParent() const {return parentNode;};
    void setVisited(bool done) {visited = done;};
    bool getVisited() {return visited;};
    float getFinalCost() const {return finalCost;};
    void setFinalCost(float newFinalCost) {finalCost = newFinalCost;};
    float getGivenCost() const;
    void setGivenCost(float newGivenCost);

    //bool getInSolution() const;
    //void setInSolution(bool newInSolution);

private:
    Node* parentNode = std::nullptr_t();
    bool visited = false;
    //bool inSolution = false;
    float finalCost = 0;
    float givenCost = 0;
};

bool operator<(float vol, const Node& Node);

struct Point {
    int xPos;
    int yPos;
};

#endif // NODE_H

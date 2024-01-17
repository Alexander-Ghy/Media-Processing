#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <queue>
#include "algorithm/node.h"
#include "world.h"

class Algorithm
{
public:
    Algorithm();
    ~Algorithm();

    void setUpInitial();
    void setUpNewRun();
    void addNodes();
    void addEnemies();
    void cleanUp();
    virtual void Solve(Point* , Point* ) {};
    virtual float calculateTotalCost(Node* ,Node* ) {return 0;};
    Node* getNode(Point* point);
    void reconstructPath(Node* end);
    bool checkExit(Node* start, Node* goal);
    const std::vector<Tile *> &getSolution() const;
    int getWeightUser() const;
    void setWeightUser(int newWeightUser);
    const std::chrono::duration<long, std::ratio<1, 1000000> >::rep &getExecutionTime() const {return executionTime;};
    void setExecutionTime(const std::chrono::duration<long, std::ratio<1, 1000000> >::rep &newExecutionTime);
    const std::vector<Point> &getSurroundingNodes() const;
    int getWorldCols() const;
    int getWorldRows() const;
    const std::vector<Node *> &getAllNodesAlgorithm() const;
    bool checkBorders(int surroudingNodeX, int surroudingNodeY);

private:
    std::vector<Node*> allNodesAlgorithm;
    std::vector<Tile*> solution;
    std::vector<Point> surroundingNodes;
    int worldCols;
    int worldRows;
    int weightUser = 0;
    std::chrono::duration<long, std::ratio<1,1000000>>::rep executionTime;
};

#endif // ALGORITHM_H

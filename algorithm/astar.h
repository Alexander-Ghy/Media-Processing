#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <memory>
#include <map>
#include <queue>
#include <utility>
#include "algorithm/algorithm.h"

class Astar: public Algorithm
{
public:
    Astar();
    ~Astar();

    void Solve(Point* start, Point* goal) override;
    inline float calculateTotalCost(Node* start,Node* goal) override;

    //void printTiles() const;
    //void printSolution();

    struct compareCostPair {
        bool operator()(std::pair<float,Node*> pair1, std::pair<float,Node*> pair2)
        {
                   return pair1.first > pair2.first;
        }
    };

private:
    std::vector<Node*> allNodes;
    std::priority_queue<std::pair<float,Node*>,std::vector<std::pair<float,Node*>>,compareCostPair> openList;
    std::vector<Point> surroundingNodesAstar;
};

#endif // DJIKSTRA_H


#ifndef ASTARBESTPATH_H
#define ASTARBESTPATH_H


#include <vector>
#include <memory>
#include <map>
#include <queue>
#include <utility>
#include "algorithm/algorithm.h"

/*
    Difference with other Astar class is that this one will keep in mind the given cost
    And by that give the best path from point A to point B but it is slower in computation beceause of that.
*/


class AstarBestPath: public Algorithm
{
public:
    AstarBestPath();
    ~AstarBestPath();

    void Solve(Point* start, Point* goal) override;
    inline float calculateHeuristicCost(Node* start,Node* goal);

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

#endif // ASTARBESTPATH_H



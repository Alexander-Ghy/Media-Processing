#include "xenemy.h"
#include "world.h"
#include <sstream>

XEnemy::XEnemy(int xPos, int yPos, float strength): Enemy(xPos,yPos,strength)
{

}

std::string XEnemy::serialize()
{
    std::stringstream res;
    res   << Enemy::serialize() << ",";
    return res.str();
}

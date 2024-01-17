#ifndef XENEMY_H
#define XENEMY_H

#include "world.h"
#include <iostream>
#include <QObject>


class XEnemy : public Enemy
{
    Q_OBJECT
public:
    XEnemy(int xPos, int yPos, float strength);
    ~XEnemy() override = default;
    std::string serialize() override;
    void setKey(int k){key = k;};
    int getKey(){return key;};

private:
    int key = 0;
};

#endif // XENEMY_H

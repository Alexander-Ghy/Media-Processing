#include "viewerenemy.h"

ViewerEnemy::ViewerEnemy(int x, int y,double sizeTileFinal): viewers(x,y, sizeTileFinal)
{

    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/enemy.png"), this));
    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/energy_recharge.png"), this));

    images.at(1)->setVisible(false);
    images.at(0)->setScale(sizeTileFinal*7/1450);
    images.at(1)->setScale(sizeTileFinal*7/1000);


}

void ViewerEnemy::dead(){
    images.at(0)->setVisible(false);
    images.at(1)->setVisible(true);
}

#include "viewerhealthpack.h"

ViewerHealthPack::ViewerHealthPack(int x, int y, double sizeTileFinal):viewers(x,y, sizeTileFinal){


        images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/mario_healthpack.png"), this));
        images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/energy_recharge.png"), this));
        images.at(1)->setVisible(false);





images.at(0)->setScale(sizeTileFinal*7/1300);

    }


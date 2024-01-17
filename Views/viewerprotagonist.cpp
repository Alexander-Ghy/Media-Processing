#include "viewerprotagonist.h"

ViewerProtagonist::ViewerProtagonist(int x, int y, double sizeTileFinal): viewers(x,y,sizeTileFinal)
{

    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/mario.png"), this));
    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/mario2.png"), this));
    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/mario_happy.png"), this));
    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/poisonned.png"), this));
    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/attack.png"), this));
    images.push_back(std::make_unique<QGraphicsPixmapItem>(QPixmap(":/sprite_images/skull.png"), this));
    images.at(1)->setVisible(false);
    images.at(2)->setVisible(false);
    images.at(3)->setVisible(false);
    images.at(4)->setVisible(false);
    images.at(5)->setVisible(false);

    images.at(0)->setScale(sizeTileFinal*7/600);
    images.at(1)->setScale(sizeTileFinal*7/2000);
    images.at(2)->setScale(sizeTileFinal*7/1750);
    images.at(3)->setScale(sizeTileFinal*8/900);
    images.at(4)->setScale(sizeTileFinal*7/2200);
    images.at(5)->setScale(sizeTileFinal*8/900);






}

void ViewerProtagonist::die(){

    images.at(0)->setVisible(false);
    images.at(1)->setVisible(false);
    images.at(2)->setVisible(false);
    images.at(3)->setVisible(false);
    images.at(4)->setVisible(false);
    images.at(5)->setVisible(true);
}


void ViewerProtagonist::health(){
    images.at(0)->setVisible(false);
    images.at(1)->setVisible(false);
    images.at(2)->setVisible(true);
    images.at(3)->setVisible(false);
    images.at(4)->setVisible(false);
    images.at(5)->setVisible(false);
    action = true;

}

void ViewerProtagonist::poisoned(){
    images.at(0)->setVisible(false);
    images.at(1)->setVisible(false);
    images.at(2)->setVisible(false);
    images.at(3)->setVisible(true);
    images.at(4)->setVisible(false);
    images.at(5)->setVisible(false);
    action = true;
}

void ViewerProtagonist::moved(){
    if(!action){

        images.at(2)->setVisible(false);
        images.at(3)->setVisible(false);
        images.at(4)->setVisible(false);
        images.at(5)->setVisible(false);

        if(state){
        images.at(0)->setVisible(true);
        images.at(1)->setVisible(false);
        state = false;
        }

        else{
        images.at(0)->setVisible(false);
        images.at(1)->setVisible(true);
        state = true;
        }
    }
    action = false;
}

void ViewerProtagonist::attack(){
    images.at(0)->setVisible(false);
    images.at(1)->setVisible(false);
    images.at(2)->setVisible(false);
    images.at(3)->setVisible(false);
    images.at(4)->setVisible(true);
    images.at(5)->setVisible(false);
    action = true;
}



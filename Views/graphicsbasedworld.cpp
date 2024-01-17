#include "graphicsbasedworld.h"
#include <iostream>
#include <qgraphicsscene.h>
#include "Controllers/protagonistcontroller.h"
#include "Views/viewerprotagonist.h"
#include "viewerenemy.h"
#include "viewerxenemies.h"
#include "Views/viewerpenemies.h"
#include "Views/viewerhealthpack.h"
#include "Controllers/enemycontroller.h"
#include "Controllers/healthpackcontroller.h"
#include "Controllers/worldcontroller.h"
#include "world_images/worldmaps.h"
GraphicsBasedWorld * GraphicsBasedWorld::instance = 0;
GraphicsBasedWorld::GraphicsBasedWorld()
{

}

GraphicsBasedWorld::~GraphicsBasedWorld()
{
    delete view;
}

GraphicsBasedWorld *GraphicsBasedWorld::getInstance()
{
    if(!instance) instance = new GraphicsBasedWorld();
    return instance;
}

void GraphicsBasedWorld::create()
{
    if(instance != 0)
        return;

    instance = new GraphicsBasedWorld();
}

void GraphicsBasedWorld::destroy()
{
    delete instance;
    instance = 0;
}

void GraphicsBasedWorld::setView(QGraphicsView *newView){
    view = newView;
}

void GraphicsBasedWorld::setString(QString string){
    str = string;
}


void GraphicsBasedWorld::createView()
{

    drawTotalScene(view,str);

}


QGraphicsScene *GraphicsBasedWorld::drawWorld(QString string)
{
    scene = new QGraphicsScene();
    image = QImage(string);

    image.convertTo(QImage::Format_RGB888);
    pixmap.convertFromImage(image);
    pixmapItem.setPixmap(pixmap);



    sizeTileWidth = ((double)view->width())/((double)image.width());
    auto sizeTileHeight = ((double)view->height())/((double)image.height());

    if(sizeTileHeight < sizeTileWidth){
        pixmapItem.setScale(sizeTileHeight);
    }
    else{
        pixmapItem.setScale(sizeTileWidth);
    }
    pixmapItem.setZValue(0.1);
    scene->addItem(&pixmapItem);

    return scene;
}


QGraphicsScene *GraphicsBasedWorld::drawProtagonist(QGraphicsScene *scene)
{

    std::shared_ptr<Protagonist> prot = ProtagonistController::getInstance()->getProtagonist();
    auto x = prot->getXPos();
    auto y = prot->getYPos();


    p->setX(x*sizeTileFinal*5.7);
    p->setY(y*sizeTileFinal*5.7);

    p->setZValue(0.5);
    scene->addItem(p);
    view->centerOn(p);
    return scene;
}

void GraphicsBasedWorld::init(){
    p = new ViewerProtagonist(0,0,sizeTileFinal);
}

void GraphicsBasedWorld::moveProtagonist()
{

}

QGraphicsScene *GraphicsBasedWorld::drawHealthPacks(QGraphicsScene *scene)
{
    auto healthpacks = HealthpackController::getInstance()->getHealthpacks();
    for(auto map=healthpacks->begin(); map!=healthpacks->end();map++) {
        auto healthpack = map->second;
        auto x = healthpack->getXPos();
        auto y = healthpack->getYPos();

        ViewerHealthPack* HP = new ViewerHealthPack(x,y,sizeTileFinal);
        HP->setZValue(0.2);
        scene->addItem(HP);

    }
    return scene;
}

QGraphicsScene *GraphicsBasedWorld::drawEnemies(QGraphicsScene *scene)
{
    auto enemies = EnemyController::getInstance()->getEnemies();

    for(auto map=enemies->begin(); map!=enemies->end();map++) {
        auto enemy = map->second;
        auto x = enemy->getXPos();
        auto y = enemy->getYPos();


        if (EnemyController::getInstance()->isXEnemy(enemy)){
            ViewerXEnemies *XE = new ViewerXEnemies(x, y,sizeTileFinal);
            XE->setZValue(0.2);
            scene->addItem(XE);
        }
        else if (EnemyController::getInstance()->isPEnemy(enemy)){
            ViewerPEnemies *PE = new ViewerPEnemies(x, y,sizeTileFinal);
            PE->setZValue(0.2);
            scene->addItem(PE);
        }
        else{
            ViewerEnemy *E = new ViewerEnemy(x,y,sizeTileFinal);
            E->setZValue(0.2);
            scene->addItem(E);
        }
    }
    return scene;

}

bool GraphicsBasedWorld::drawPathfindingTest(QGraphicsView *newView, QString string)
{
    if (string == WORLDMAP)
    {
        std::cout << "There is no pathfinding demo for this map" << std::endl;
        return 1;
    }
    view = newView;
    auto sceneWorld = drawWorld(string);

    Point start = Point();
    Point goal = Point();
    qreal factorVisualisation = 1;
    if(string == WORLDMAP4)
    {
        start.xPos = 0;
        start.yPos = 45;
        goal.xPos = 999;
        goal.yPos = 938;
        factorVisualisation = 3;
    }
    else if (string == MAZE1)
    {
        start.xPos = 0;
        start.yPos = 492;
        goal.xPos = 499;
        goal.yPos = 334;
    }
    else if (string == MAZE2)
    {
        start.xPos = 0;
        start.yPos = 212;
        goal.xPos = 440;
        goal.yPos = 208;
    }
    else if (string == MAZE3)
    {
        start.xPos = 0;
        start.yPos = 22;
        goal.xPos = 1200;
        goal.yPos = 1205;
        factorVisualisation = 3;
    }
    else
    {
        start.xPos = 1;
        start.yPos = 1;
        goal.xPos = 98;
        goal.yPos = 98;
    }

    auto algorithm = LogicController::getInstance()->getAlgorithm();
    algorithm->setUpNewRun();
    algorithm->Solve(&start,&goal);
    auto solution = algorithm->getSolution();

    auto getSizeTileWidth = (double) WorldController::getInstance()->getWorld()->getCols();
    auto getSizeTileHeight = (double) WorldController::getInstance()->getWorld()->getRows();


    if (getSizeTileWidth < getSizeTileHeight)
    {
        sizeTileFinal = (sceneWorld->width() / getSizeTileWidth);
    }
    else
    {
        sizeTileFinal = (sceneWorld->height() / getSizeTileHeight);
    }

    for (auto tile: solution)
    {
        auto xpos = (double) tile->getXPos();
        auto ypos = (double) tile->getYPos();
        auto QgraphicsRectItem = new QGraphicsRectItem();
        QRectF Qrect = QRectF((qreal) xpos*sizeTileFinal,(qreal) ypos*sizeTileFinal,(qreal) sizeTileFinal*factorVisualisation, (qreal) sizeTileFinal*factorVisualisation);
        QColor color = QColor(255,0,0);
        QBrush Qbrushvar = QBrush(color, Qt::SolidPattern);
        QgraphicsRectItem->setBrush(Qbrushvar);
        QgraphicsRectItem->setPen(Qt::NoPen);
        QgraphicsRectItem->setRect(Qrect);
        QgraphicsRectItem->setZValue(10);
        sceneWorld->addItem(QgraphicsRectItem);
    }

    view->setScene(sceneWorld);
    return 0;
}



void GraphicsBasedWorld::drawTotalScene(QGraphicsView *newView, QString stringWorld)
{
    view = newView;
    auto scene1 = drawWorld(stringWorld);
    view->setScene(scene1); //already show the world before adding the enemies
    auto scene2 = drawProtagonist(scene1);
    auto scene3 = drawHealthPacks(scene2);
    auto scene4 = drawEnemies(scene3);
    auto scene5 = visited(scene4);

    view->setScene(scene5);

}

QGraphicsScene * GraphicsBasedWorld::visited(QGraphicsScene *scene){
    auto unordenedMap = *ProtagonistController::getInstance()->getVisitedTiles();
    for(auto map = unordenedMap.begin();map !=unordenedMap.end();map++){
        int x = map->second->getXPos();
        int y = map->second->getYPos();
        if(!(p->getXPos()==x && p->getYPos()==y)){
        auto QgraphicsRectItem = new QGraphicsRectItem();
        QRectF Qrect = QRectF((qreal) x*sizeTileFinal*5.7,(qreal) y*sizeTileFinal*5.7,(qreal) sizeTileFinal*5.7, (qreal) sizeTileFinal*5.7);
        QColor color = QColor(100,200,100);
        QBrush Qbrushvar = QBrush(color, Qt::SolidPattern);
        QgraphicsRectItem->setBrush(Qbrushvar);
        QgraphicsRectItem->setPen(Qt::NoPen);
        QgraphicsRectItem->setRect(Qrect);
        QgraphicsRectItem->setZValue(0.2);
        scene->addItem(QgraphicsRectItem);}
    }
    return scene;
}

void GraphicsBasedWorld::on_position_changed(int x, int y)
{
    if(!ProtagonistController::getInstance()->isDead()){
        p->moved();
    }

}

void GraphicsBasedWorld::on_game_over(int x, int y)
{
    ProtagonistController::getInstance()->setDead(true);
    p->die();
    createView();
}

void GraphicsBasedWorld::on_attack()
{
   p->attack();
}

void GraphicsBasedWorld::on_healthpack()
{
    p->health();

}

void GraphicsBasedWorld::on_poisoned()
{
    p->poisoned();
}

void GraphicsBasedWorld::zoomIn(){

    if(scale<1){
        scale = 1;
    }
    scale += 0.1;
    view->scale(scale,scale);
}

void GraphicsBasedWorld::zoomOut(){

    if(scale>1){
        scale = 1;
    }
    scale -= 0.1;
    view->scale(scale,scale);
}

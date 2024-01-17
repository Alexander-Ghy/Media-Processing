#ifndef GRAPHICSBASEDWORLD_H
#define GRAPHICSBASEDWORLD_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Views/viewerprotagonist.h"
#include "Views/views.h"


class GraphicsBasedWorld: public Views
{
public:
    GraphicsBasedWorld();
    ~GraphicsBasedWorld();

    static GraphicsBasedWorld * getInstance();
    static void create();
    static void destroy();

    void drawTotalScene(QGraphicsView* view, QString stringWorld);
    void createView() override;
    void setView(QGraphicsView* view);
    void setString(QString string);
    QGraphicsScene* drawWorld(QString string);
    QGraphicsScene* drawProtagonist(QGraphicsScene* scene);
    QGraphicsScene* visited(QGraphicsScene* scene);
    void init();
    void moveProtagonist();
    QGraphicsScene* drawHealthPacks(QGraphicsScene* scene );
    QGraphicsScene* drawEnemies(QGraphicsScene* scene);
    QGraphicsScene* drawPEnemies(QGraphicsScene* scene);
    QGraphicsScene* drawXEnemies(QGraphicsScene* scene);

    bool drawPathfindingTest(QGraphicsView* newView, QString string);


    void zoomIn();
    void zoomOut();

public slots:
    void on_position_changed(int x, int y) override;
    void on_game_over(int x, int y) override;
    void on_attack() override;
    void on_healthpack() override;
    void on_poisoned() override;

private:
    static GraphicsBasedWorld* instance;
    QGraphicsView* view;
    QString str;
    QGraphicsScene* scene;
    QPixmap pixmap;
    QGraphicsPixmapItem pixmapItem;
    QGraphicsRectItem QgraphicsRectItem;
    QImage image;
    ViewerProtagonist *p;
    float scale = 1;
    double sizeTileWidth;
    double sizeTileFinal;



};

#endif // GRAPHICSBASEDWORLD_H

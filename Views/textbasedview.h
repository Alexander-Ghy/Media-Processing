#ifndef TEXTBASEDVIEW_H
#define TEXTBASEDVIEW_H

#include <QGraphicsScene>
#include <QObject>
#include "Views/views.h"

class TextBasedView : public Views
{
    Q_OBJECT
public:
    TextBasedView();

    static TextBasedView * getInstance();
    static void create();
    static void destroy();

    QGraphicsScene* getScene() {return scene;};
    void initGrid();
    void createView() override;
    void replaceGridValue(int x, int y, char *s);
    void parseEnemiesToGrid();
    void parseVisitedTilesToGrid();
    void changeProtColor(QString color);
    void setMaze();
    void setInitialized(bool init){initialized = init;};
    bool getInitialized(){return initialized;};


public slots:
    void on_position_changed(int x, int y) override;
    void on_game_over(int x, int y) override;
    void on_attack() override;
    void on_healthpack() override;
    void on_poisoned() override;
    void on_XEnemy_changed(int x, int y) override;

signals:
    void stopGame() override;

private:
    static TextBasedView* instance;
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsTextItem* text;
    QString protColor = "black";
    QString grid;
    QVector <QString> gridVector;
    int gridCols, gridRows, gridBoundary;
    bool initialized = false;
};

#endif // TEXTBASEDVIEW_H

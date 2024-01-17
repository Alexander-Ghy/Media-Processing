#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "world.h"
#include "algorithm/astar.h"
#include "Commands/commandlist.h"

#include <QString>
#include <QObject>

#include <Views/views.h>
//#include "mainwindow.h"

class MainWindow;
class LogicController : public QObject
{
    Q_OBJECT
public:
    LogicController();
    static LogicController * getInstance();
    static void create();
    static void destroy();
    typedef enum {text, graphical}Curr;
    void createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f);
    void initViews();
    bool checkIfIllegalPosition(int xNew, int yNew);
    void moveProtagonist(CommandList::Commandstest cmd);
    void moveToTile(std::shared_ptr<Tile> tile);
    void setMainWindow(const std::shared_ptr<MainWindow> &mw);
    std::shared_ptr<MainWindow> getMainWindow(){return mainWindow;};
    void FollowPath(std::vector<Tile *>* solution);
    void autoPlay();
    void XEnemiesMove();
    void setCurrView(Curr current);
    Views* getCurrView(){return curr;};
    const std::shared_ptr<Algorithm> &getAlgorithm() const;
    void delay();
    void changeGraphicsDelay(int factor);
    void buttonAstar();
    void buttonAstarBest();



signals:
    void gameOver(int x, int y);
    void XEnemyChange(int x, int y);
    void healthpack();
    void attack();

private:
    static LogicController* instance;
    std::shared_ptr<Algorithm> algorithm;    
    std::shared_ptr<MainWindow> mainWindow = nullptr;
    Views* curr;
    double graphicsDelay = 0.1; //Seconds
};

#endif // LOGICCONTROLLER_H

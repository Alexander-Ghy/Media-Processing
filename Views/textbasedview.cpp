#include "textbasedview.h"
#include "Controllers/protagonistcontroller.h"
#include "world.h"

#include <Controllers/enemycontroller.h>
#include <Controllers/healthpackcontroller.h>
#include <Controllers/worldcontroller.h>

#include <QStringBuilder>
#include <QGraphicsTextItem>
#include <QChar>
#include <ui_mainwindow.h>


TextBasedView * TextBasedView::instance = 0;
TextBasedView::TextBasedView() : gridCols(10), gridRows(10), gridBoundary(5)
{

}

TextBasedView *TextBasedView::getInstance()
{
    if(!instance) instance = new TextBasedView();
    return instance;
}
void TextBasedView::create()
{
    if(instance != 0)
        return;

    instance = new TextBasedView();
}

void TextBasedView::destroy()
{
    delete instance;
    instance = 0;
}

void TextBasedView::initGrid()
{
    gridVector.clear();
    grid = "";

    int worldCols = WorldController::getInstance()->getWorld()->getCols();
    int worldRows = WorldController::getInstance()->getWorld()->getRows();
    if(WorldController::getInstance()->getType() == WorldTypes::MAZE)
    {
        gridCols = 30;
        gridRows = 13;
    } else
    {
        gridCols = 13;
        gridRows = 13;
    }
    if(worldCols < gridCols) gridCols = worldCols;
    if(worldRows < gridRows) gridRows = worldRows;
    gridBoundary = std::min(gridRows, gridCols)/2;

    QString gridRow = "+";
    QString gridCol = "|";

    for(int i = 0; i < worldCols; i++)
    {
         gridRow = gridRow % "---+";
    }
    for(int i = 0; i < worldCols; i++)
    {
        gridCol = gridCol % "   |";
    }
    gridRow = gridRow % "\n";
    gridCol = gridCol % "\n";
    for(int i = 0; i < worldRows; i++)
    {
        gridVector.push_back(gridRow);
        gridVector.push_back(gridCol);
    }
    gridVector.push_back(gridRow);

    parseEnemiesToGrid();

    if(WorldController::getInstance()->getType() == WorldTypes::MAZE)
    {
        setMaze();
        protColor = "Fuchsia";
    } else protColor = "black";

    for(auto & hp : *HealthpackController::getInstance()->getHealthpacks())
    {
        if(!ProtagonistController::getInstance()->onProtagonist(hp.second->getXPos(), hp.second->getYPos()))
        {
            replaceGridValue(hp.second->getXPos(), hp.second->getYPos(), (char *) "H");
        } else replaceGridValue(hp.second->getXPos(), hp.second->getYPos(), (char *) "P");
    }
}

void TextBasedView::createView()
{
    std::shared_ptr<Protagonist> prot = ProtagonistController::getInstance()->getProtagonist();
    int x = prot->getXPos();
    int y = prot->getYPos();
    int worldCols = WorldController::getInstance()->getWorld()->getCols();
    int worldRows = WorldController::getInstance()->getWorld()->getRows();

    grid = "";

    parseVisitedTilesToGrid();
    parseEnemiesToGrid();

    int startX = 0;
    int startY = 0;

    if(y >= (gridRows - gridBoundary))
    {
        startY = (y - (gridRows - gridBoundary) + 1)*2;
    }
    if(y > (worldRows - gridBoundary - 1))
    {
        startY = (worldRows - gridRows)*2;
    }
    if(x >= (gridCols - gridBoundary))
    {
        startX = (x - (gridCols - gridBoundary) + 1)*4;
    }
    if(x > (worldCols - gridBoundary - 1))
    {
        startX = (worldCols - gridCols)*4;
    }

    for(int i = startY; i < (startY + (2*gridRows) + 1); i++)
    {
        grid = grid % gridVector[i].mid(startX, (gridCols*4) + 1) % "\n";
    }

    scene->clear();
    text = scene->addText(grid);
    if(!ProtagonistController::getInstance()->isDead())
    {
        changeProtColor(protColor);
    } else
    {
        text->setDefaultTextColor(Qt::gray);
    }
    text->setFont(QFont("Monospace"));
    if(WorldController::getInstance()->getType() == WorldTypes::MAZE)
    {
        protColor = "Fuchsia";
    } else protColor = "black";
}

void TextBasedView::replaceGridValue(int x, int y, char *s)
{
    gridVector[((2*y+1))].replace((2+(4*x)), 1, *s);
}

void TextBasedView::parseEnemiesToGrid()
{
    auto unordenenMap = *EnemyController::getInstance()->getEnemies();

    for(auto mapKeyAndEnemy = unordenenMap.begin(); mapKeyAndEnemy != unordenenMap.end(); mapKeyAndEnemy++)
    {
        char * c;
        int x = mapKeyAndEnemy->second->getXPos();
        int y = mapKeyAndEnemy->second->getYPos();

        if(ProtagonistController::getInstance()->onProtagonist(x, y))
        {
            c = (char *) "P";
        } else if(mapKeyAndEnemy->second->getDefeated())
        {
            c = (char *) "O";
        } else if(EnemyController::getInstance()->isPEnemy(mapKeyAndEnemy->second))
        {
            c = (char *) "I";
        } else if(EnemyController::getInstance()->isXEnemy(mapKeyAndEnemy->second))
        {
            c = (char *) "X";
        } else
        {
            c = (char *) "E";
        }
        replaceGridValue(x, y, (char *) c);
    }
}

void TextBasedView::parseVisitedTilesToGrid()
{
    auto unordenenMap = *ProtagonistController::getInstance()->getVisitedTiles();
    for(auto mapKeyAndTile = unordenenMap.begin(); mapKeyAndTile != unordenenMap.end(); mapKeyAndTile++)
    {
        int x = mapKeyAndTile->second->getXPos();
        int y = mapKeyAndTile->second->getYPos();

        if(!ProtagonistController::getInstance()->onProtagonist(x, y))
        {
            replaceGridValue(x, y, (char *) ".");
        } else replaceGridValue(x, y, (char *) "P");
    }
}

void TextBasedView::changeProtColor(QString color)
{
    grid = grid.replace("/n", "<br>");
    if(!grid.contains("P"))
    {
        replaceGridValue(ProtagonistController::getInstance()->getProtagonist()->getXPos(), ProtagonistController::getInstance()->getProtagonist()->getYPos(), (char*) "P");
    }

    QVector<QString> s = grid.split("| P");
    QString html = "<pre style='color:black'>" + s[0] + "| <a style='color:" + color + "'>P</a>" + s[1] + "</pre>";
    text->setHtml(html);
}

void TextBasedView::setMaze()
{
    for(auto & t : *WorldController::getInstance()->getTilesUnorderedMap())
    {
        if(LogicController::getInstance()->checkIfIllegalPosition(t.second->getXPos(), t.second->getYPos()))
        {
            replaceGridValue(t.second->getXPos(), t.second->getYPos(), (char *) "|||");
        }
    }
}

void TextBasedView::on_position_changed(int x, int y)
{
    if(!ProtagonistController::getInstance()->isDead()){
        replaceGridValue(x, y, (char *) "P");
    }
}

void TextBasedView::on_game_over(int x, int y)
{
    ProtagonistController::getInstance()->setDead(true);
    replaceGridValue(x, y, (char *) "D");
    createView();
    emit stopGame();
}

void TextBasedView::on_attack()
{
    this->protColor = "Fuchsia";
}

void TextBasedView::on_healthpack()
{
    this->protColor = "Lime";
}

void TextBasedView::on_poisoned()
{
    this->protColor = "darkCyan";
}

void TextBasedView::on_XEnemy_changed(int x, int y)
{
    replaceGridValue(x, y, (char *)" ");
}


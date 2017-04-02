#include <QCoreApplication>
#include <iostream>

//My HeaderFiles

#include "gameSystem.h"


using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    gameSystem Game;
    Game.startGame();

    return a.exec();
}


#include <iostream>
#include <QMessageBox>
#include "simulator/module.h"
#include "gamethread.h"

GameThread::GameThread(QObject *parent) :
    QThread(parent)
{
}

void GameThread::run()
{
    try
    {
        std::cout << "Hello world!!!" << std::endl;

        GameSimulator game_sim;

        double time = 0;
        while (1)
        {
            game_sim.Update(time, 1);
            time += 1;
        }
    }
    catch(LocalsException& e)
    {
        QMessageBox::critical(nullptr, "Error", GetErrorDescription(e.GetCode()).c_str());
    }
}

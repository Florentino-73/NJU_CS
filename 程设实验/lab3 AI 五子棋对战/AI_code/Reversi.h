#ifndef Reversi_h
#define Reversi_h

#include <stdio.h>
#include <ctime>
#include "ClientSocket.h"

using namespace std;

class Reversi
{
private:
    ClientSocket client_socket;
    int ownColor;
    int oppositeColor;

    //function 

     // according to chessman position (row , col) , generate one step message in order to send to server
    // 根据棋盘位置，生成一步棋传给服务器
    void generateOneStepMessage(int row, int col);

public:
    pair<int, int> step(int my_color);

    void saveChessBoard(int round);

    void handleMessage(int row, int col, int color);

public:
    Reversi();
    ~Reversi();
    void setOwnColor(int color);

    void authorize(const char* id, const char* pass);

    void gameStart();

    void gameOver();

    void roundStart(int round);

    void oneRound(int round);

    void roundOver(int round);

    int observe();

};

#endif /* Reversi_h */
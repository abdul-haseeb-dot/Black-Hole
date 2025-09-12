#ifndef HOLE_HPP
#define HOLE_HPP

#include "raylib.h"
#include<vector>
using namespace std;

//Global game state variables
extern int currentNumber;
extern int currentPlayer;
extern bool animatingBlackHole;
extern float blackHoleAnimProgress;
extern float animationStartTime;
extern bool waitingForAnimation;
extern int blackRow, blackCol;
extern int sum1, sum2;

struct Hole
{
    int value;
    int player;
    Vector2 position;
    Color playerColor;

    Hole(Vector2 position);
    void drawHole();
    bool isClicked();
    void setValue();
    void setBlackHole();
};

pair<int,int> markBlackHole(vector<vector<Hole>>& holes);
pair<int,int> calculateAdjacentSum(vector<vector<Hole>>& holes, int blackRow, int blackCol);
void updateAnimations();

#endif
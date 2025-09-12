#include "Hole.hpp"
#include "Constants.hpp"
#include<cmath>
#include<cstdio>
using namespace std;

//Global game state variables definitions
int currentNumber=1;
int currentPlayer=1;
bool animatingBlackHole=false;
float blackHoleAnimProgress=0.0f;
float animationStartTime=0.0f;
bool waitingForAnimation=false;
int blackRow=-1, blackCol=-1;
int sum1=0, sum2=0;

Hole::Hole(Vector2 position) : value(0), player(0), position(position) {}

void Hole::drawHole()
{
    DrawRing(position,INNER_RADIUS,OUTER_RADIUS,0,360,360,BLACK);
    Vector2 mouse=GetMousePosition();
    double dx=mouse.x-position.x;
    double dy=mouse.y-position.y;
    double distance=sqrt(dx*dx+dy*dy);
    if(player==-1)
    {
        if(animatingBlackHole && blackHoleAnimProgress<1.0f)
        {
            float fillRadius=INNER_RADIUS*blackHoleAnimProgress;
            DrawCircleV(position,fillRadius,BLACK);
            DrawRing(position,INNER_RADIUS,OUTER_RADIUS,0,360,360,BLACK);
        }
        else
        {
            DrawCircleV(position,OUTER_RADIUS,BLACK);
        }
    }
    else if(player==0 && distance<=OUTER_RADIUS && !waitingForAnimation)
    {
        Color currentPlayerColor=(currentPlayer==1)?PLAYER_1_COLOR:PLAYER_2_COLOR;
        DrawRing(position,OUTER_RADIUS+3,OUTER_RADIUS+6,0,360,360,currentPlayerColor);
    }
    else if(player>0)
    {
        char text[3];
        sprintf(text,"%d",value);
        int textWidth=MeasureText(text,NUMBER_SIZE);
        int posX=position.x-textWidth/2;
        int posY=position.y-NUMBER_SIZE/2;
        DrawText(text,posX,posY,NUMBER_SIZE,playerColor);
    }
}

bool Hole::isClicked()
{
    if(player!=0 || waitingForAnimation) return false;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse=GetMousePosition();
        double dx=mouse.x-position.x;
        double dy=mouse.y-position.y;
        double distance=sqrt(dx*dx+dy*dy);
        if(distance<=OUTER_RADIUS)
            return true;
    }
    return false;
}

void Hole::setValue()
{
    value=currentNumber;
    player=currentPlayer;
    playerColor=(player==1)?PLAYER_1_COLOR:PLAYER_2_COLOR;
}

void Hole::setBlackHole()
{
    player=-1;
    value=-1;
}

pair<int,int> markBlackHole(vector<vector<Hole>>& holes)
{
    for(int row=0;row<holes.size();row++)
    {
        for(int col=0;col<holes[row].size();col++)
        {
            if(holes[row][col].player==0)
            {
                int blackRow=row;
                int blackCol=col;
                holes[row][col].setBlackHole();

                animatingBlackHole=true;
                blackHoleAnimProgress=0.0f;
                animationStartTime=GetTime();

                return {blackRow,blackCol};
            }
        }
    }
    return {-1,-1};
}

pair<int,int> calculateAdjacentSum(vector<vector<Hole>>& holes, int blackRow, int blackCol)
{
    int sum1=0;
    int sum2=0;

    vector<pair<int,int>> adjacentOffSets={{-1,-1},{-1,0},{0,-1},{0,1},{1,0},{1,1}};

    for(const auto& [x,y]:adjacentOffSets)
    {
        int row=blackRow+x;
        int col=blackCol+y;
        if(row>=0 && row<holes.size() && col>=0 && col<holes[row].size())
        {
            Hole adjacentHole=holes[row][col];
            if(adjacentHole.player==1) sum1+=adjacentHole.value;
            else if(adjacentHole.player==2) sum2+=adjacentHole.value;
        }
    }

    return {sum1,sum2};
}

void updateAnimations()
{
    float currentTime=GetTime();
    if(animatingBlackHole)
    {
        float elapsed=currentTime-animationStartTime;
        blackHoleAnimProgress=elapsed/BLACKHOLE_ANIM_DURATION;
        
        if(blackHoleAnimProgress>=1.0f)
        {
            blackHoleAnimProgress=1.0f;
            animatingBlackHole=false;
        }
    }
}
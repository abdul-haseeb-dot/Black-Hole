#include "raylib.h"
#include "Constants.hpp"
#include "Screens.hpp"
#include "Hole.hpp"
#include<vector>
#include<cstdio>
#include<string>
#include<sstream>
using namespace std;

vector<string> SplitLines(const string &str)
{
    vector<string> lines;
    stringstream ss(str);
    string line;
    while(getline(ss, line))
    {
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Black Hole");
    SetTargetFPS(60);

    Screens SCREEN=INSTRUCTIONS;
    bool gameRunning=true;

    //Placing the holes on screen
    vector<vector<Hole>> holes;

    float startX=SCREEN_WIDTH/2.0f;
    float startY=190;
    float gap=70;
    float rowGap=60;

    for(int row=1;row<=6;row++)
    {
        vector<Hole> currentRow;
        float rowWidth=(row-1)*gap;  
        float X=startX-rowWidth/2;

        for(int col=0;col<row;col++)
        {
            currentRow.push_back(Hole(Vector2{X, startY}));
            X+=gap;
        }

        holes.push_back(currentRow);
        startY+=rowGap;
    }


    //Placing heading on screen
    char title[]="BLACK HOLE";
    int titleSize=50;
    int titleX=(SCREEN_WIDTH-MeasureText(title,titleSize))/2;
    int titleY=30;

    //Placing instructions on screen
    string instructions="1. Two players take turns placing numbers in the holes.\n2. Numbers start at 1 and increase after both players have played.\n3. When only one hole is remaining, it becomes the black hole.\n4. The numbers in holes adjacent to black will be summed for each player.\n5. The player with a lower sum wins.";
    auto lines=SplitLines(instructions);
    int fontSize=20;
    int lineSpacing=15;

    //variable declarations before switch
    int x, y;

    while(!WindowShouldClose() && gameRunning)
    {
        updateAnimations();
        
        //Check if animation finished and we need to switch to statistics
        if(waitingForAnimation && !animatingBlackHole)
        {
            SCREEN=STATISTICS;
            waitingForAnimation=false;
        }
        
        BeginDrawing();
        
        switch(SCREEN)
        {
            case INSTRUCTIONS:
                ClearBackground(BLACK);
                DrawText(title,titleX,titleY,titleSize,WHITE);
                x=35;
                y=180;
                DrawText("Instructions:",x,y,30,LIGHTGRAY);
                y+=fontSize+lineSpacing+10;
                for(const auto &line:lines)
                {
                    DrawText(line.c_str(), x, y, fontSize, WHITE);
                    y+=fontSize+lineSpacing;
                }
                DrawText("Click anywhere to continue...",x,y,30,LIGHTGRAY);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    SCREEN=GAME;
                }
                break;
            
            case GAME:
                ClearBackground(GAME_BACKGROUND);
                DrawText(title,titleX,titleY,titleSize,BLACK);

                if(!waitingForAnimation)
                {
                    char playerPrompt[10];
                    sprintf(playerPrompt,"Player %d",currentPlayer);
                    fontSize=40;
                    x=(SCREEN_WIDTH-MeasureText(playerPrompt,fontSize))/2;
                    y=titleY+30+fontSize;
                    DrawText(playerPrompt,x,y,fontSize,(currentPlayer==1)?PLAYER_1_COLOR:PLAYER_2_COLOR);
                }

                for(auto& rowOfHoles:holes)
                {
                    for(auto& hole:rowOfHoles)
                    {
                        hole.drawHole();
                        if(hole.isClicked())
                        {
                            hole.setValue();
                            if(currentPlayer==2) {currentPlayer--; currentNumber++;}
                            else currentPlayer++;
                            if(currentNumber>10)
                            {
                                pair<int, int> blackHole=markBlackHole(holes);
                                blackRow=blackHole.first;
                                blackCol=blackHole.second;
                                pair<int,int> sums=calculateAdjacentSum(holes,blackRow,blackCol);
                                sum1=sums.first;
                                sum2=sums.second;
                                waitingForAnimation=true;
                            }
                        }
                    }
                }
                break;
            
            case STATISTICS:
                ClearBackground(GAME_BACKGROUND);
                sprintf(title, "BLACK HOLE");
                DrawText(title,titleX,titleY,titleSize,BLACK);

                for(auto& rowOfHoles:holes)
                {
                    for(auto& hole:rowOfHoles)
                    {
                        hole.drawHole();
                    }
                }

                char player1[]="PLAYER 1";
                char player2[]="PLAYER 2";

                fontSize=40;
                int player1Width=MeasureText(player1,fontSize);
                int player2Width=MeasureText(player2,fontSize);

                int player1X=40;
                int player2X=SCREEN_WIDTH-player2Width-player1X;

                DrawText(player1,player1X,100,fontSize,PLAYER_1_COLOR);
                DrawText(player2,player2X,100,fontSize,PLAYER_2_COLOR);
                
                char player1Score[3];
                sprintf(player1Score,"%d",sum1);
                char player2Score[3];
                sprintf(player2Score,"%d",sum2);

                fontSize=80;
                int player1ScoreWidth=MeasureText(player1Score,fontSize);
                int player2ScoreWidth=MeasureText(player2Score,fontSize);

                int player1ScoreX=player1X+(player1Width-player1ScoreWidth)/2;
                int player2ScoreX=player2X+(player2Width-player2ScoreWidth)/2;

                DrawText(player1Score,player1ScoreX,160,fontSize,PLAYER_1_COLOR);
                DrawText(player2Score,player2ScoreX,160,fontSize,PLAYER_2_COLOR);

                char winner[10];
                if(sum1==sum2) sprintf(winner,"DRAW");
                else sprintf(winner,"PLAYER %d WINS",sum1<sum2?1:2);
                fontSize=40;
                x=(SCREEN_WIDTH-MeasureText(winner,fontSize))/2;
                y=titleY+30+fontSize;
                DrawText(winner,x,y,fontSize,(sum1==sum2)?GRAY:(sum1<sum2)?PLAYER_1_COLOR:PLAYER_2_COLOR);

                char exit[]="Click Anywhere to Exit";
                fontSize=30;
                x=(SCREEN_WIDTH-MeasureText(exit,fontSize))/2;
                y=SCREEN_HEIGHT-50;
                DrawText(exit,x,y,fontSize,BLACK);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    gameRunning=false;
                break;
        }
        EndDrawing();
    }

    return 0;
}
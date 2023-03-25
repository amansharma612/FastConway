#include "ConwayGame.h"
#include <unistd.h>
#include <cstdlib>


ConwayGame::ConwayGame(int gameSize) {
    for (int i = 0; i < gameSize * gameSize; i++) {
        this->boardPosition.push_back(0);
        this->newPosition.push_back(0);
    }

    this->gameSize = gameSize;
    setInitCondition();
}


void ConwayGame::updatePositions(){
    

    for (int i = 0; i < gameSize * gameSize; i++) {
        int x_pos = i / gameSize;
        int y_pos = i % gameSize;

        int neighLiveCnt = 0;

        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {

                int nx = (gameSize + (x_pos + j)) % gameSize;
                int ny = (gameSize + (y_pos + k)) % gameSize;

                if (nx == x_pos && ny == y_pos) continue;

                if (boardPosition[(nx * gameSize) + ny] == 1) neighLiveCnt++;

            }
        }

        
        if (boardPosition[x_pos * gameSize + y_pos] == 1){
            if (neighLiveCnt < 2) newPosition[x_pos * gameSize + y_pos] = 0;
            else if (neighLiveCnt <= 3) newPosition[x_pos * gameSize + y_pos] = 1;
            else if (neighLiveCnt > 3) newPosition[x_pos * gameSize + y_pos] = 0;
        } else if (neighLiveCnt == 3) {
            newPosition[x_pos * gameSize + y_pos] = 1;
        
        }
        

        
         
    }

    boardPosition = newPosition;
      
    
}


void ConwayGame::setInitCondition(){
    for (int i = 0; i < gameSize * gameSize; i++) {
        int x = i / gameSize;
        int y = i % gameSize;

        boardPosition[x * gameSize + y] = (rand() >> 30) % 2;
    }

}




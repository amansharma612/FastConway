
#include <unistd.h>
#include <chrono>
#include <thread>
#include "ConwayGame.h"

#define GAME_SIZE 256
#define NUM_ITER 100

int main (int argc, char * argv[]){
    srand(atoi(argv[1]));
    ConwayGame game(GAME_SIZE);
    for (int i = 0; i < NUM_ITER; i++)
    {

        game.updatePositions();

    }

    for (int i = 0; i < GAME_SIZE * GAME_SIZE; i++){
        std::cout << game.boardPosition[i];
    }

    return 0;

}
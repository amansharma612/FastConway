#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>



const int pr_cnt = std::thread::hardware_concurrency();
#define GAME_SIZE 256
#define NUM_ITER 100



/* Idea: In have used only one array to store the current and the next state.
         in the first bit I store the current state, and then the next 4 bits 
         containing the number of alive neighbours of that cell.
         to find the next state, I use next 5 bits to calculate the next state and 
         the alive neighbours in the next state.

         For calculating the neighbours, if the current cell is alive then it adds 1 to the bits 
         corresponding to the neighbours in the next state.

         This procedure is further split into 8 threads (8 cores on my CPU), but is adaptable to
         different CPUs.

         No SIMD parellism is used in the code.
*/


void handleBoard(int a1, int a2, std::vector<int>*  boardPosition){
    int x_pos = 0;
    int y_pos = 0;
    for (int i = a1; i < a2; i++) {
            x_pos = i / GAME_SIZE;
            y_pos = i % (GAME_SIZE);

            int neighLiveCnt = 0;
            int nx;
            int ny;
            // for (int j = -1; j <= 1; j++) {
            //     for (int k = -1; k <= 1; k++) {

            //         nx = (GAME_SIZE + (x_pos + j)) & (GAME_SIZE - 1);
            //         ny = (GAME_SIZE + (y_pos + k)) & (GAME_SIZE - 1);

            //         if (nx == x_pos && ny == y_pos) continue;

            //         neighLiveCnt += ((*boardPosition)[(nx * GAME_SIZE) + ny] & 1);

            //     }
            // }

           // if ((*boardPosition)[i] == 0 && neighLiveCnt == 0) continue;
           int neighCnt = ((*boardPosition)[i] >> 1) & 15;
            if ((*boardPosition)[i] & 1 == 1){
                 
                if (neighCnt <= 3 && neighCnt >= 2){ 
                    (*boardPosition)[i] |= 0x20;
                    for (int j = -1; j <= 1; j++) {
                        for (int k = -1; k <= 1; k++) {

                            nx = (GAME_SIZE + (x_pos + j)) & (GAME_SIZE - 1);
                            ny = (GAME_SIZE + (y_pos + k)) & (GAME_SIZE - 1);

                            if (nx == x_pos && ny == y_pos) continue;

                            (*boardPosition)[(nx * GAME_SIZE) + ny] += (1 << 6);

                        }
                    }
                    
                }
            } else if (neighCnt == 3) {
                (*boardPosition)[i] |= 0x20;
                for (int j = -1; j <= 1; j++) {
                        for (int k = -1; k <= 1; k++) {

                            nx = (GAME_SIZE + (x_pos + j)) & (GAME_SIZE - 1);
                            ny = (GAME_SIZE + (y_pos + k)) & (GAME_SIZE - 1);

                            if (nx == x_pos && ny == y_pos) continue;

                            (*boardPosition)[(nx * GAME_SIZE) + ny] += (1 << 6);

                        }
                }
            
            }
                   
         
        }
}

void updateBoard(int a1, int a2, std::vector<int>*  boardPosition){
    for (int i = a1; i < a2; i++){
            (*boardPosition)[i] >>= 5;
    }
}

int main (int argc, char * argv[]){
    srand(atoi(argv[1]));
    std::vector<int> boardPosition;
    //std::vector<int> newPosition;
    
    
    
    for (int i = 0; i < GAME_SIZE * GAME_SIZE; i++) {
        boardPosition.push_back(0);

    }
    
    int nx;
    int ny;

    for (int i = 0; i < GAME_SIZE * GAME_SIZE; i++) {
        boardPosition[i] += ((rand() >> 30) & 1);
        if (boardPosition[i] & 1 == 1) {
            int x_pos = i / GAME_SIZE;
            int y_pos = i % GAME_SIZE;
            for (int j = -1; j <= 1; j++) {
                        for (int k = -1; k <= 1; k++) {

                            nx = (GAME_SIZE + (x_pos + j)) & (GAME_SIZE - 1);
                            ny = (GAME_SIZE + (y_pos + k)) & (GAME_SIZE - 1);

                            if (nx == x_pos && ny == y_pos) continue;

                            boardPosition[(nx * GAME_SIZE) + ny] += 2;

                        }
                    }
        }
    }
    
    
    
    std::vector<std::thread*> threads;
    
    for (int i = 0; i < NUM_ITER; i++)
    {
        for (int i = 0; i < pr_cnt; i++) {
            threads.push_back(new std::thread(handleBoard, i*GAME_SIZE * GAME_SIZE / pr_cnt, (i+1)*GAME_SIZE * GAME_SIZE / pr_cnt, &boardPosition));
            
        }

        for (int i = 0; i < pr_cnt; i++) {
            threads[i]->join();
        }

        threads.clear();

        for (int i = 0; i < pr_cnt; i++) {
            threads.push_back(new std::thread(updateBoard, i*GAME_SIZE * GAME_SIZE / pr_cnt, (i+1)*GAME_SIZE * GAME_SIZE / pr_cnt, &boardPosition));
            
        }

        for (int i = 0; i < pr_cnt; i++) {
            threads[i]->join();
        }

        threads.clear();

    }

    for (int i = 0; i < GAME_SIZE * GAME_SIZE; i++){
        std::cout << (boardPosition[i] & 1);
    }

    return 0;

}